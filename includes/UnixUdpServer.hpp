/* 
 * File:   UnixUdpServer.h
 * Author: xaqq
 *
 * Created on January 7, 2013, 2:14 PM
 */

#ifndef UNIXUDPSERVER_H
#define	UNIXUDPSERVER_H

#include "IUdpServer.hpp"
#include <map>

namespace Net
{

    class UnixUdpServer : public IUdpServer
    {
    public:
        UnixUdpServer();
        UnixUdpServer(const UnixUdpServer& orig);
        virtual ~UnixUdpServer();

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

        void registerFunctor(std::pair<std::string, int> origin,
                std::function<bool (char *data, int size) > c);
        
        bool write(std::pair<std::string, int> target, char *data, int size);
        
    private:
        int _sock;
        std::map<std::pair<std::string, int>,
        std::function<bool (char *data, int size) >> _functors;

        std::function<bool (const std::string &addr,
                unsigned short port, char *data, int size) > _unkownSourceCallback;

        bool bind(const std::string &ip, unsigned short port);
        void dispatch(const std::string &ip, unsigned short port, char *data, int size);

    };
}
#endif	/* UNIXUDPSERVER_H */

