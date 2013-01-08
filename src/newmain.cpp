/* 
 * File:   newmain.cpp
 * Author: xaqq
 *
 * Created on January 2, 2013, 2:33 PM
 */

#include <cstring>
#include <signal.h>
#include <iostream>
#include <cstdlib>
#include <functional>
#include <memory>
#include "ServerFactory.hpp"
#include "ITcpServer.hpp"
#include "ITcpSocket.hpp"
#include "IUdpServer.hpp"

using namespace Net;
using namespace std;

shared_ptr<IUdpServer> udp(0);

class Lama
{
public:
    std::weak_ptr<ITcpSocket> sock;
    std::pair<std::string, int> addr;
    
    bool data(void)
    {
        std::cout << "Un lama est la ! avec des datas " << sock.lock()->availableBytes() << std::endl;
        char buff[1024];

        memset(buff, 0, 1024);
        sock.lock()->read(buff, 1024);
        if (strcmp(buff, "bye\n") == 0)
            return false;
        return true;
    }

    bool udpData(char *data, int s)
    {
        std::cout << "Udp Lama ! {" << data << "}" << std::endl;
        udp->write(addr, "Stop me parler\n", strlen("Stop me parler\n"));
        return true;
    }

};

Lama *l = 0;

bool new_con(shared_ptr<ITcpSocket> s)
{
    std::cout << "In new connection !" << std::endl;

    l = new Lama();

    l->sock = s;
    std::function<bool (void) > fct = std::bind(&Lama::data, l);
    s->dataAvailableCallback(fct);
    fct();
    return true;
}

void closed_con(shared_ptr<ITcpSocket> s)
{
    std::cout << "Connection closed " << std::endl;
}

int run = 1;

void sighandler(int s)
{
    run = 0;
}


bool UDP_NEW(const std::string &addr, unsigned short port, char *data, int size)
{
    std::cout << "New UDP packet from unkown source: " << addr << ":" << port << std::endl;
    std::cout << "Data {" << data << "}" << std::endl;

    Lama *p = new Lama;

    p->addr = std::make_pair(addr, port);
    std::function<bool (char *, int) > test = std::bind(&Lama::udpData, p, std::placeholders::_1,
                                                        std::placeholders::_2);
    udp->registerFunctor(std::make_pair(addr, port), test);
    udp->write(p->addr, "coucou\n", 7);
	return (true);
}

int main(int argc, char** argv)
{
    shared_ptr<ITcpServer> tcp(ServerFactory::tcpServer());
    udp = std::shared_ptr<IUdpServer>(ServerFactory::udpServer());

    udp->start("0.0.0.0", 1338);
    tcp->start("0.0.0.0", 1337);

    std::function<bool (shared_ptr<ITcpSocket>) > lama = &new_con;
    std::function<void (shared_ptr<ITcpSocket>) > lama2 = &closed_con;
    tcp->newConnectionCallback(lama);
    tcp->connectionClosedCallback(lama2);

	
    udp->unknownSourceCallback(std::function<bool (const std::string &addr,
                               unsigned short port, char *data, int size) > (&UDP_NEW));
    signal(SIGINT, &sighandler);
    while (1)
    {
        if (run)
        {
            tcp->run(10);
            udp->run();
        }	
        else break;
    }
    //delete l;
    return 0;
}

