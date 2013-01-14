/*
 * File:   WinUdpServer.h
 * Author: toutouyoutou
 *
 * Created on January 7, 2013, 2:14 PM
 */

#ifndef WINUDPSERVER_H
#define	WINUDPSERVER_H

#pragma comment(lib, "Ws2_32.lib")

#include "IUdpServer.hpp"
#include <map>

namespace Net
{

class WinUdpServer : public IUdpServer
{
public:
    WinUdpServer();
    WinUdpServer(const WinUdpServer& orig);
    virtual ~WinUdpServer();

    bool start(const std::string &ip, unsigned short port);
    bool stop();

    /**
     * Process incomming data using callback.
     */
    bool run();

    void unknownSourceCallback(std::function<bool (const std::string &addr,
                               unsigned short port, char *data, int size) > c)
    {
        _unkownSourceCallback = c;
    }

    void registerFunctor(std::pair<std::string, unsigned short> origin,
                         std::function<bool (char *data, int size) > c);

    void unregisterFunctor(std::pair<std::string, unsigned short> origin);

    bool write(std::pair<std::string, int> target, char *data, int size);

private:
    WSAData WSAdata;
    SOCKET _sock;
    std::map<std::pair<std::string, int>,
    std::function<bool (char *data, int size) >> _functors;

    std::function<bool (const std::string &addr,
            unsigned short port, char *data, int size) > _unkownSourceCallback;

    bool bind(const std::string &ip, unsigned short port);
    void dispatch(const std::string &ip, unsigned short port, char *data, int size);

};
}
#endif	/* WINUDPSERVER_H */

