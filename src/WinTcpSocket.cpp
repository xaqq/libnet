/*
 * File:   WinTcpSocket.cpp
 * Author: toutouyoutou
 *
 * Created on December 20, 2012, 9:35 PM
 */

#include <cstring>
#include "WinTcpSocket.hpp"

using namespace Net;

WinTcpSocket::WinTcpSocket() :
_rBuf(42 * 1024, 42 * 1024),
_wBuf(42 * 1024, 42 * 1024)
{
}

WinTcpSocket::~WinTcpSocket()
{
    closesocket(socket);
}

bool WinTcpSocket::start()
{
    return true;
}

bool WinTcpSocket::stop()
{
    return true;
}

bool WinTcpSocket::dataAvailable()
{
    return _callback();
}

bool WinTcpSocket::writeSome()
{
	WSABUF buffer;
    char tbuffer[1024 * 42];
    int r;
    int ret;
	DWORD nb_read;

	buffer.buf = tbuffer;
	buffer.len = 1024 * 42;
    r = _wBuf.rAvailable();
    r = r > static_cast<int>(sizeof (tbuffer)) ? static_cast<int>(sizeof (tbuffer)) : r;
    if (r)
    {
        _wBuf.read(&tbuffer[0], r);
		ret = WSASend(socket, &buffer, 1, &nb_read, 0, NULL, NULL);
		if (ret == SOCKET_ERROR)
        {
			int err = WSAGetLastError();
            if (err != WSAEWOULDBLOCK)
                return false;
            _wBuf.readRollback();
        }
        if (nb_read != r) /* we didnt write everything */
            _wBuf.readRollback(r - ret);
    }
    return (true);
}

bool WinTcpSocket::readSome()
{
    int ret;
	DWORD nb_read;
	WSABUF buffer;
    char tbuffer[1024];

	buffer.buf = tbuffer;
	buffer.len = 1024;
	memset(tbuffer, 0, sizeof (buffer));
	ret = WSARecv(socket, &buffer, 1, &nb_read, 0, NULL, NULL);
	if ((ret == 0 && nb_read == 0) || (ret == -1 && WSAGetLastError() != WSAEWOULDBLOCK))
        return false;
    return _rBuf.write(tbuffer, nb_read);
}

bool WinTcpSocket::read(char *dest, int len)
{
    return _rBuf.read(dest, len) != 0;
}

bool WinTcpSocket::write(const char *data, int len)
{
    return _wBuf.write(data, len);
}