/*
 * File:   ITcpServer.hpp
 * Author: xaqq
 *
 * Created on December 20, 2012, 8:51 PM
 */

#ifndef ITCPSERVER_HPP
#define	ITCPSERVER_HPP

#include <functional>
#include <string>
#include <memory>

namespace Net
{
class ITcpSocket;

class ITcpServer
{
public:

    virtual ~ITcpServer()
    {
    }

    /**
     * Start the TcpServer server by binding and listening.
     * Call run to begin the processing of network data.
     * @param ip
     * @param port
     * @return
     */
    virtual bool start(const std::string &ip, unsigned short port) = 0;
    virtual bool stop() = 0;

    /**
     * Process incomming data and new connection using callback.
     */
    virtual bool run(int mstimeout) = 0;

    virtual void newConnectionCallback(std::function<bool (std::shared_ptr<ITcpSocket>) > c) = 0;
    virtual void connectionClosedCallback(std::function<void (std::shared_ptr<ITcpSocket>) > c) = 0;
};
}

#endif	/* ITCPSERVER_HPP */

