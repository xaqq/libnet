/*
 * File:   UnixTcpSocket.hpp
 * Author: xaqq
 *
 * Created on December 20, 2012, 9:35 PM
 */

#ifndef UNIXTCPSOCKET_HPP
#define	UNIXTCPSOCKET_HPP

#include "RingBuffer.hpp"
#include "ITcpSocket.hpp"
namespace Net
{

class UnixTcpSocket : public ITcpSocket
{
public:
    UnixTcpSocket();
    virtual ~UnixTcpSocket();

    bool start();
    bool stop();

    void dataAvailableCallback(std::function<bool (void) >);

    /**
     * Return the number of bytes that are still to be written into the
     * kernel socket buffer
     */
    int pendingWriteBytes() const;

    /**
     * Return the number of bytes that are available for reading
     * in the socket internal buff (NOT kernel buffer related)
     */
    int availableBytes() const;


    bool read(char *dest, int len);

    bool write(const char *data, int len);

    int fd() const
    {
        return _fd;
    }

    void fd(int fd)
    {
        _fd = fd;
    }

private:
    UnixTcpSocket(const UnixTcpSocket& orig);

    /**
     * The file descriptor associated with the socket.
     * Default to -1.
     */
    int _fd;
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
#endif	/* UNIXTCPSOCKET_HPP */

