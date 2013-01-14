/*
 * File:   IUdpServer.hpp
 * Author: xaqq
 *
 * Created on January 7, 2013, 2:08 PM
 */

#ifndef IUDPSERVER_HPP
#define	IUDPSERVER_HPP

#include <string>
#include <memory>
#include <functional>

namespace Net
{
    class IUdpSocket;

    class IUdpServer
    {
    public:

        virtual ~IUdpServer()
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
         * Process incomming data using callback.
         */
        virtual bool run() = 0;

        /**
         * Write to a specified client. Target is identified using its address and
         * its destination port.
         * @param
         * @param
         */
        virtual bool write(std::pair<std::string, int> target, char *data, int size) = 0;

        virtual void unknownSourceCallback(std::function<bool (const std::string &addr,
                unsigned short port, char *data, int size) > c) = 0;
        virtual void registerFunctor(std::pair<std::string, unsigned short> origin,
                std::function<bool (char *data, int size) >) = 0;
        virtual void unregisterFunctor(std::pair<std::string, unsigned short> origin) = 0;
    };
}


#endif	/* IUDPSERVER_HPP */

