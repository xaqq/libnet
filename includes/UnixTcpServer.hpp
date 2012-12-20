/*
 * File:   UnixTcpServer.hpp
 * Author: xaqq
 *
 * Created on December 20, 2012, 8:57 PM
 */

#ifndef UNIXTCPSERVER_HPP
#define	UNIXTCPSERVER_HPP

#include "ITcpServer.hpp"

namespace Net
{

class UnixTcpServer : public ITcpServer
{
public:
    UnixTcpServer();
    UnixTcpServer(const UnixTcpServer& orig);
    virtual ~UnixTcpServer();


    /**
     * Start the TcpServer server by binding and listening.
     * Call run to begin the processing of network data.
     * @param ip
     * @param port
     * @return
     */
    bool start(const std::string &ip, unsigned short port);
    bool stop();

    /**
     * Process incomming data and new connection using callback.
     */
    bool run();

    void newConnectionCallback(std::function<bool (ITcpSocket *) > c)
    {
        _newConnectionCb = c;
    }

    void connectionClosedCallback(std::function<void (ITcpSocket *)> c)
    {
        _closedConnectionCb = c;
    }

private:
    std::function<bool (ITcpSocket *) > _newConnectionCb;
    std::function<void (ITcpSocket *) > _closedConnectionCb;

};
}
#endif	/* UNIXTCPSERVER_HPP */

