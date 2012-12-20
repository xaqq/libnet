/*
 * File:   ServerFactory.cpp
 * Author: xaqq
 *
 * Created on December 20, 2012, 8:48 PM
 */

#include "ServerFactory.hpp"
#include "UnixTcpServer.hpp"

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
