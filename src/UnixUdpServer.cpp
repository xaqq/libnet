/* 
 * File:   UnixUdpServer.cpp
 * Author: xaqq
 * 
 * Created on January 7, 2013, 2:14 PM
 */

#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <stdexcept>
#include <sys/types.h>
#include <sys/socket.h>
#include "UnixUdpServer.hpp"

using namespace Net;

UnixUdpServer::UnixUdpServer()
{
    _sock = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);
    if (_sock == -1)
        throw std::runtime_error("Cannot create UdpServer socket");
}

UnixUdpServer::~UnixUdpServer()
{
}

void UnixUdpServer::registerFunctor(std::pair<std::string, int> origin,
                                    std::function<bool (char *data, int size) > c)
{
    _functors[origin] = c;
}

bool UnixUdpServer::start(const std::string& ip, unsigned short port)
{
    if (!bind(ip, port))
        return false;
    return true;
}

bool UnixUdpServer::stop()
{
    close (_sock);
    return true;
}

bool UnixUdpServer::run()
{
    char buffer[1024 * 1024];
    socklen_t fromlen;
    struct sockaddr_storage addr;
    int ret;
    std::string ip;
    unsigned short port;

    while (1)
    {
        bzero(buffer, sizeof(buffer));
        fromlen = sizeof (struct sockaddr_storage);
        ret = recvfrom(_sock, &buffer, 1024 * 1024, 0,
                       reinterpret_cast<sockaddr *> (&addr), &fromlen);
        if (ret == -1 && errno != EWOULDBLOCK &&
            errno != EAGAIN)
        {
            perror("UdpSocket");
            return false;
        }
        else if (ret == -1)
            return true;

        ip = inet_ntoa(reinterpret_cast<struct sockaddr_in *> (&addr)->sin_addr);
        port = reinterpret_cast<struct sockaddr_in *> (&addr)->sin_port;
        dispatch(ip, port, buffer, ret);
    }
}

bool UnixUdpServer::write(std::pair<std::string, int> target, char* data, int size)
{
    int ret;
    socklen_t tolen;
    struct sockaddr_storage addr;
    
    tolen = sizeof(struct sockaddr_storage);
    reinterpret_cast<struct sockaddr_in *>(&addr)->sin_addr.s_addr = inet_addr(target.first.c_str());
    reinterpret_cast<struct sockaddr_in *>(&addr)->sin_port = target.second;
    reinterpret_cast<struct sockaddr_in *>(&addr)->sin_family = AF_INET;
    ret = ::sendto(_sock, data, size, 0, reinterpret_cast<const struct sockaddr *>(&addr), tolen);
    
    if (ret != size)
        return false;
    return true;
}

void UnixUdpServer::dispatch(const std::string& ip, unsigned short port, char* data, int size)
{
    if (_functors.count(std::make_pair(ip, port)))
    {
        _functors[std::make_pair(ip, port)](data, size);
    }
    else
    {
        _unkownSourceCallback(ip, port, data, size);
    }
}

bool UnixUdpServer::bind(const std::string &ip, unsigned short port)
{
    struct sockaddr_in sa;
    const int i = 1;

    memset(&sa, 0, sizeof (struct sockaddr_in));
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(ip.c_str());
    sa.sin_port = htons(port);

    setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, &i, sizeof (int));
    if (::bind(_sock, (struct sockaddr *) &sa,
               sizeof (struct sockaddr_in)) != 0)
    {
        perror("bind:");
        return (false);
    }
    return (true);
}