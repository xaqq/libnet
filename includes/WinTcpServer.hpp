/*
 * File:   WinTcpServer.hpp
 * Author: toutouyoutou
 */

#ifndef WINTCPSERVER_HPP
#define	WINTCPSERVER_HPP

#pragma comment(lib, "Ws2_32.lib")

#include <WinSock2.h>
#include <list>
#include <memory>
#include "ITcpServer.hpp"
#include "WinTcpSocket.hpp"

namespace Net
{
class WinTcpSocket;
class WinTcpServer : public ITcpServer
{
public:
    WinTcpServer();
    WinTcpServer(const WinTcpServer& orig);
    virtual ~WinTcpServer();


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
    SOCKET _sock;

	WSADATA WSAdata;

    /**
     * Clients ' list
     */
    std::list<std::shared_ptr<WinTcpSocket >> _clients;

    fd_set _wSet;
    fd_set _rSet;
    fd_set _eSet;



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

    bool process(std::shared_ptr<WinTcpSocket> s);
};
}
#endif	/* UNIXTCPSERVER_HPP */

