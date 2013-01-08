/* 
 * File:   WinUdpServer.cpp
 * Author: toutouyoutou
 * 
 * Created on January 7, 2013, 2:14 PM
 */

#include <functional>
#include <errno.h>
#include <cstring>
#include <stdexcept>
#include <sys/types.h>
#include <WinSock2.h>
#include "WinUdpServer.hpp"

using namespace Net;

WinUdpServer::WinUdpServer()
{
	WSAStartup(MAKEWORD(2,2), &WSAdata);
    _sock = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, 0);
	u_long i = 1;
    if (_sock == -1)
        throw std::runtime_error("Cannot create UdpServer socket");
	ioctlsocket(_sock, FIONBIO, &i);
}

WinUdpServer::~WinUdpServer()
{
	WSACleanup();
}

void WinUdpServer::registerFunctor(std::pair<std::string, int> origin,
                                    std::function<bool (char *data, int size) > c)
{
    _functors[origin] = c;
}

bool WinUdpServer::start(const std::string& ip, unsigned short port)
{
    if (!bind(ip, port))
        return false;
    return true;
}

bool WinUdpServer::stop()
{
    closesocket(_sock);
    return true;
}

bool WinUdpServer::run()
{
	WSABUF buffer;
    char tbuffer[1024 * 1024];
    int fromlen;
	DWORD nb_read;
    struct sockaddr_storage addr;
    int ret;
    std::string ip;
    unsigned short port;

	buffer.buf = tbuffer;
	buffer.len = 1024 * 1024;
    while (1)
    {
        memset(tbuffer, 0, sizeof(buffer));
        fromlen = sizeof (struct sockaddr_storage);
        ret = WSARecvFrom(_sock, &buffer, 1, &nb_read, 0,
                       reinterpret_cast<sockaddr *> (&addr), &fromlen, NULL, NULL);
		if (ret == -1 && WSAGetLastError() != EWOULDBLOCK)
        {
            perror("UdpSocket");
            return false;
        }
        else if (ret == -1)
            return true;

        ip = inet_ntoa(reinterpret_cast<struct sockaddr_in *> (&addr)->sin_addr);
        port = reinterpret_cast<struct sockaddr_in *> (&addr)->sin_port;
        dispatch(ip, port, tbuffer, ret);
    }
}

bool WinUdpServer::write(std::pair<std::string, int> target, char* data, int size)
{
	WSABUF buffer;
	buffer.buf = data;
	buffer.len = size;
    int ret;
    int tolen;
	DWORD nb_write;
    struct sockaddr_storage addr;
    
    tolen = sizeof(struct sockaddr_storage);
    reinterpret_cast<struct sockaddr_in *>(&addr)->sin_addr.s_addr = inet_addr(target.first.c_str());
    reinterpret_cast<struct sockaddr_in *>(&addr)->sin_port = target.second;
    reinterpret_cast<struct sockaddr_in *>(&addr)->sin_family = AF_INET;
	ret = WSASendTo(_sock, &buffer, 1, &nb_write, 0, reinterpret_cast<const struct sockaddr *>(&addr), tolen, NULL, NULL);
    
    if (nb_write != size)
        return false;
    return true;
}

void WinUdpServer::dispatch(const std::string& ip, unsigned short port, char* data, int size)
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

bool WinUdpServer::bind(const std::string &ip, unsigned short port)
{
    struct sockaddr_in sa;
    const int i = 1;

    memset(&sa, 0, sizeof (struct sockaddr_in));
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(ip.c_str());
    sa.sin_port = htons(port);

    setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, (char *)&i, sizeof (int));
    if (::bind(_sock, (struct sockaddr *) &sa,
               sizeof (struct sockaddr_in)) != 0)
    {
        perror("bind:");
        return (false);
    }
    return (true);
}