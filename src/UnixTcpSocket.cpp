/*
 * File:   UnixTcpSocket.cpp
 * Author: xaqq
 *
 * Created on December 20, 2012, 9:35 PM
 */

#include <unistd.h>
#include <cstring>
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

bool UnixTcpSocket::writeSome()
{
    char buffer[1024 * 42];
    int r;
    int ret;

    r = _wBuf.rAvailable();
    r = r > static_cast<int>(sizeof (buffer)) ? static_cast<int>(sizeof (buffer)) : r;
    if (r)
    {
        _wBuf.read(&buffer[0], r);
        if ((ret = ::write(_fd, (char *) buffer, r)) == -1)
        {
            if (errno != EWOULDBLOCK &&
                    errno != EAGAIN)
            {
                return false;
            }
            _wBuf.readRollback();
        }
        if (ret != r) /* we didnt write everything */
            _wBuf.readRollback(r - ret);
    }
    return (true);
}

bool UnixTcpSocket::readSome()
{
    int n;
    char buffer[1024];

    bzero(buffer, sizeof (buffer));
    n = ::read(_fd, buffer, sizeof (buffer));
    if (n == 0 || (n == -1 && (errno != EWOULDBLOCK &&
            errno != EAGAIN)))
        return false;
    return true;
}

bool UnixTcpSocket::read(char *dest, int len)
{
    return _rBuf.read(dest, len);
}

bool UnixTcpSocket::write(const char *data, int len)
{
    return _wBuf.write(data, len);
}