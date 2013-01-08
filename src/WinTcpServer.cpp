/*
 * File:   WinTcpServer.cpp
 * Author: toutouyoutou
 *
 * Created on December 20, 2012, 8:57 PM
 */

#include <cstring>
#include <stdexcept>

#include "WinTcpServer.hpp"
#include "WinTcpSocket.hpp"

using namespace Net;

WinTcpServer::WinTcpServer()
{
	WSAStartup(MAKEWORD(2,2), &WSAdata);
	_sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);
	u_long i = 1;
	if (_sock == INVALID_SOCKET)
        throw std::runtime_error("Cannot create TcpServer socket");
	ioctlsocket(_sock, FIONBIO, &i);
}

WinTcpServer::WinTcpServer(const WinTcpServer& orig)
{
}

WinTcpServer::~WinTcpServer()
{
	WSACleanup();
}

bool WinTcpServer::start(const std::string& ip, unsigned short port)
{
    if (!bind(ip, port))
        return false;
    if (!listen())
        return false;

    return true;
}

bool WinTcpServer::bind(const std::string &ip, unsigned short port)
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

bool WinTcpServer::listen(int max /* = 10 */)
{
    if (::listen(_sock, max) != 0)
    {
        perror("listen:");
        return false;
    }
    return true;
}

bool WinTcpServer::stop()
{
    closesocket(_sock);
    for (auto it = _clients.begin();
         it != _clients.end();
         ++it)
    {
        _closedConnectionCb((*it));
        closesocket((*it)->sock());
    }
    _clients.clear();

    return true;
}

bool WinTcpServer::run(int timeout /* = 0 */)
{
    struct timeval t;

    fillSets();
    t.tv_usec = timeout * 1000;
    t.tv_sec = 0;
    if (select(0, &_rSet, &_wSet, &_eSet, &t) == -1)
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

bool WinTcpServer::process(std::shared_ptr<WinTcpSocket> s)
{
    if (FD_ISSET(s->sock(), &_wSet) == 1)
        if (!s->writeSome())
            return false;
    if (FD_ISSET(s->sock(), &_rSet) == 1)
    {
        if (s->readSome())
            return s->dataAvailable();
        else
            return false;
    }
    return true;
}

bool WinTcpServer::newConnection()
{
    struct sockaddr_in sclient;
    int sclient_l;
    SOCKET fd;

    sclient_l = sizeof (struct sockaddr_in);
    if ((fd = accept(_sock, (struct sockaddr *) (&sclient),
                      &sclient_l)) != -1)
    {
        std::shared_ptr<WinTcpSocket> sock(new WinTcpSocket());
        bool keep;

        if (_newConnectionCb)
            keep = _newConnectionCb(sock);

        sock->sock(fd);
        if (keep)
            _clients.push_back(sock);
        return true;
    }
    return false;
}

void WinTcpServer::fillSets()
{
    SOCKET fd;

    FD_ZERO(&_wSet);
    FD_ZERO(&_rSet);
    FD_ZERO(&_eSet);
    FD_SET(_sock, &_rSet);
    for (auto it = _clients.begin();
         it != _clients.end();
         ++it)
    {
        fd = (*it)->sock();
        FD_SET(fd, &_rSet);
        if ((*it)->pendingWriteBytes())
            FD_SET(fd, &_wSet);
    }
}
