/*
 * File:   UnixTcpSocket.cpp
 * Author: xaqq
 *
 * Created on December 20, 2012, 9:35 PM
 */

#include <unistd.h>
#include "UnixTcpSocket.hpp"

using namespace Net;

UnixTcpSocket::UnixTcpSocket() : _fd(-1),
_rBuf(42 * 1024, 42 * 1024),
_wBuf(42 * 1024, 42 * 1024)
{
}

UnixTcpSocket::~UnixTcpSocket()
{
    close(_fd);
}

bool UnixTcpSocket::dataAvailable()
{
    return _callback();
}