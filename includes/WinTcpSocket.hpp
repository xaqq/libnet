/*
 * File:   WinTcpSocket.hpp
 * Author: toutouyoutou
 *
 * Created on December 20, 2012, 9:35 PM
 */

#ifndef WINTCPSOCKET_HPP
#define	WINTCPSOCKET_HPP

#pragma comment(lib, "Ws2_32.lib")

#include <winsock2.h>
#include <functional>
#include "RingBuffer.hpp"
#include "ITcpSocket.hpp"
namespace Net
{

class WinTcpSocket : public ITcpSocket
{
public:
    WinTcpSocket();
    virtual ~WinTcpSocket();

    bool start();
    bool stop();

    void dataAvailableCallback(std::function<bool (void) >c)
    {
        _callback = c;
    }

    /**
     * Called by the TcpServer implementation. The class is supposed
     * to forward the notification using the callback
     */
    bool dataAvailable();
    /**
     * Return the number of bytes that are still to be written into the
     * kernel socket buffer
     */
    int pendingWriteBytes() const
    {
        return _wBuf.rAvailable();
    }

    /**
     * Return the number of bytes that are available for reading
     * in the socket internal buff (NOT kernel buffer related)
     */
    int availableBytes() const
    {
        return _rBuf.rAvailable();
    }

    /**
     * Write some data to the underlaying socket buffer.
     * Should return false if an error occured.
     */
    bool writeSome();
    /**
     * Read some data from the underlying socket buffer.
     * Should return false if an error occurred.
     *
     * Note that this function does NOT trigger the callback.
     */
    bool readSome();

    bool read(char *dest, int len);

    bool write(const char *data, int len);

	SOCKET &sock()
    {
        return socket;
    }

    void sock(SOCKET sock)
    {
        socket = sock;
    }

private:
    WinTcpSocket(const WinTcpSocket& orig);

    std::function<bool (void) > _callback;

	SOCKET socket;

    /**
     * Input buffer, which stores data read from the socket
     */
    RingBuffer _rBuf;
    /**
     * Output buffer, which stores data that are to be written to the socket.
     */
    RingBuffer _wBuf;


};
}
#endif	/* WINTCPSOCKET_HPP */

