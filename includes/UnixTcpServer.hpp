/*
 * File:   UnixTcpServer.hpp
 * Author: xaqq
 *
 * Created on December 20, 2012, 8:57 PM
 */

#ifndef UNIXTCPSERVER_HPP
#define	UNIXTCPSERVER_HPP

#include <sys/select.h>
#include <list>
#include <memory>
#include "ITcpServer.hpp"

namespace Net
{
class UnixTcpSocket;
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
    bool run(int timeout);

    void newConnectionCallback(std::function<bool (std::shared_ptr<ITcpSocket>) > c)
    {
        _newConnectionCb = c;
    }

    void connectionClosedCallback(std::function<void (std::shared_ptr<ITcpSocket>) > c)
    {
        _closedConnectionCb = c;
    }

private:
    std::function<bool (std::shared_ptr<ITcpSocket >) > _newConnectionCb;
    std::function<void (std::shared_ptr<ITcpSocket >) > _closedConnectionCb;
    /**
     * Server socket
     */
    int _sock;

    /**
     * Clients ' list
     */
    std::list<std::shared_ptr<UnixTcpSocket >> _clients;

    fd_set _wSet;
    fd_set _rSet;
    fd_set _eSet;

    /**
     * Max fd (used by select).
     */
    int _maxFd;



    /**
     * Attempt to bind the server to port port
     * @param port
     * @return true on success, false on error
     */
    bool bind(const std::string &ip, unsigned short port);

    /**
     * Makes the server listen.
     * @param max max pending connection
     * @return true on success, false on error
     */
    bool listen(int max = 10);

    bool newConnection();

    void fillSets();
};
}
#endif	/* UNIXTCPSERVER_HPP */

