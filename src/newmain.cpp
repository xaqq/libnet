/* 
 * File:   newmain.cpp
 * Author: xaqq
 *
 * Created on January 2, 2013, 2:33 PM
 */

#include <signal.h>
#include <iostream>
#include <cstdlib>
#include <functional>
#include <memory>
#include "../includes/ServerFactory.hpp"
#include "../includes/ITcpServer.hpp"
#include "../includes/ITcpSocket.hpp"

using namespace Net;
using namespace std;

class Lama
{
public:
    std::weak_ptr<ITcpSocket> sock;

    bool data(void)
    {
        std::cout << "Un lama est la ! avec des datas " << sock.lock()->availableBytes() << std::endl;
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

/*
 * 
 */
int main(int argc, char** argv)
{
    shared_ptr<ITcpServer> tcp(ServerFactory::tcpServer());

    tcp->start("0.0.0.0", 1337);
    std::function<bool (shared_ptr<ITcpSocket>) > lama = &new_con;
    std::function<void (shared_ptr<ITcpSocket>) > lama2 = &closed_con;
    tcp->newConnectionCallback(lama);
    tcp->connectionClosedCallback(lama2);
    signal(SIGINT, &sighandler);
    while (1)
    {
        if (run)
            tcp->run(10);
        else break;
    }
    //delete l;
    return 0;
}

