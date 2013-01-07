/*
 * File:   ServerFactory.cpp
 * Author: xaqq
 *
 * Created on December 20, 2012, 8:48 PM
 */

#include "ServerFactory.hpp"

#ifdef _WIN32
#include "WinTcpServer.hpp"
#else
#include "UnixTcpServer.hpp"
#endif

#ifdef _WIN32
#include "WinUdpServer.hpp"
#else
#include "UnixUdpServer.hpp"
#endif

using namespace Net;

ServerFactory::ServerFactory()
{
}

ServerFactory::ServerFactory(const ServerFactory& orig)
{
}

ServerFactory::~ServerFactory()
{
}

ITcpServer *ServerFactory::tcpServer()
{
#ifdef _WIN32
    return new WinTcpServer();
#else
    return new UnixTcpServer();
#endif
    return 0;
}

IUdpServer *ServerFactory::udpServer()
{
#ifdef _WIN32
    return new WinUdpServer();
#else
    return new UnixUdpServer();
#endif
    return 0;
}
