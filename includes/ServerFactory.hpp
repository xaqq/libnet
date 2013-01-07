/*
 * File:   ServerFactory.hpp
 * Author: xaqq
 *
 * Created on December 20, 2012, 8:48 PM
 */

#ifndef SERVERFACTORY_HPP
#define	SERVERFACTORY_HPP

namespace Net
{
class ITcpServer;
class IUdpServer;

class ServerFactory
{
public:

    static ITcpServer *tcpServer();
    static IUdpServer *udpServer();

private:
    ServerFactory();
    ServerFactory(const ServerFactory& orig);
    virtual ~ServerFactory();

};
}
#endif	/* SERVERFACTORY_HPP */

