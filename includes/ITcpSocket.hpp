/*
 * File:   ITcpSocket.hpp
 * Author: xaqq
 *
 * Created on December 20, 2012, 9:28 PM
 */

#ifndef ITCPSOCKET_HPP
#define	ITCPSOCKET_HPP

#include <memory>

namespace Net
{

class ITcpSocket
{
public:

    virtual ~ITcpSocket()
    {
    }

    virtual bool start() = 0;
    virtual bool stop() = 0;

    virtual void dataAvailableCallback(std::function<bool (void) >) = 0;

    /**
     * Return the number of bytes that are still to be written into the
     * kernel socket buffer
     */
    virtual int pendingWriteBytes() const = 0;

    /**
     * Return the number of bytes that are available for reading
     * in the socket internal buff (NOT kernel buffer related)
     */
    virtual int availableBytes() const = 0;


    virtual bool read(char *dest, int len) = 0;

    /**
     * Writing to the TcpSocket means writting in its internal buffer.
     * The TcpServer implementation should refering the the specified class (WinTcpSocket or
     * UnixTcpSocket to see how to effectively write on socket)
     */
    virtual bool write(const char *data, int len) = 0;


    /**
     * Write some data to the underlying socket buffer.
     * Should return false if an error occurred.
     */
    virtual bool writeSome() = 0;

    /**
     * Read some data from the underlying socket buffer.
     * Should return false if an error occurred.
     *
     * Note that this function does NOT trigger the callback.
     */
    virtual bool readSome() = 0;
};
}


#endif	/* ITCPSOCKET_HPP */

