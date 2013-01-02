/*
 * File:   UnixTcpServer.cpp
 * Author: xaqq
 *
 * Created on December 20, 2012, 8:57 PM
 */

#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "UnixTcpServer.hpp"
#include "UnixTcpSocket.hpp"

using namespace Net;

UnixTcpServer::UnixTcpServer()
{
    _sock = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
}

UnixTcpServer::UnixTcpServer(const UnixTcpServer& orig)
{
}

UnixTcpServer::~UnixTcpServer()
{
}

bool UnixTcpServer::start(const std::string& ip, unsigned short port)
{
    if (!bind(ip, port))
        return false;
    if (!listen())
        return false;

    return true;
}

bool UnixTcpServer::bind(const std::string &ip, unsigned short port)
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

bool UnixTcpServer::listen(int max /* = 10 */)
{
    if (::listen(_sock, max) != 0)
    {
        perror("listen:");
        return false;
    }
    return true;
}

bool UnixTcpServer::stop()
{
    close(_sock);
    for (auto it = _clients.begin();
         it != _clients.end();
         ++it)
    {
        _closedConnectionCb((*it));
        close((*it)->fd());
    }
    _clients.clear();

    return true;
}

bool UnixTcpServer::run(int timeout /* = 0 */)
{
    struct timeval t;

    fillSets();
    t.tv_usec = timeout * 1000;
    t.tv_sec = 0;
    if (select(_maxFd + 1, &_rSet, &_wSet, &_eSet, &t) == -1)
    {
        perror("select()");
        return false;
    }
    for (auto it = _clients.begin();
         it != _clients.end();)
    {
        if (!process((*it)))
        {
            _closedConnectionCb(*it);
            it = _clients.erase(it);
        }
        else
            ++it;
    }

    if (FD_ISSET(_sock, &_rSet))
        while (newConnection());
    return true;
}

bool UnixTcpServer::process(std::shared_ptr<UnixTcpSocket> s)
{
    if (FD_ISSET(s->fd(), &_wSet) == 1)
        if (!s->writeSome())
            return false;
    if (FD_ISSET(s->fd(), &_rSet) == 1)
    {
        if (s->readSome())
            return s->dataAvailable();
        else
            return false;
    }
    return true;
}

bool UnixTcpServer::newConnection()
{
    struct sockaddr_in sclient;
    socklen_t sclient_l;
    int fd;

    sclient_l = sizeof (struct sockaddr_in);
    if ((fd = accept4(_sock, (struct sockaddr *) (&sclient),
                      &sclient_l, SOCK_NONBLOCK)) != -1)
    {
        std::shared_ptr<UnixTcpSocket> sock(new UnixTcpSocket());
        bool keep;

        if (_newConnectionCb)
            keep = _newConnectionCb(sock);

        sock->fd(fd);
        if (keep)
            _clients.push_back(sock);
        return true;
    }
    return false;
}

void UnixTcpServer::fillSets()
{
    int fd;

    FD_ZERO(&_wSet);
    FD_ZERO(&_rSet);
    FD_ZERO(&_eSet);
    _maxFd = 0;
    FD_SET(_sock, &_rSet);
    _maxFd = _sock > _maxFd ? _sock : _maxFd;
    for (auto it = _clients.begin();
         it != _clients.end();
         ++it)
    {
        fd = (*it)->fd();
        FD_SET(fd, &_rSet);
        if ((*it)->pendingWriteBytes())
            FD_SET(fd, &_wSet);
        _maxFd = fd > _maxFd ? fd : _maxFd;
    }
}
