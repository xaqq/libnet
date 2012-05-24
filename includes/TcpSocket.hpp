/*
 * File:   TcpSocket.hpp
 * Author: xaqq
 *
 * Created on May 11, 2012, 8:46 PM
 */

#ifndef TCPSOCKET_HPP
#define	TCPSOCKET_HPP

#include "RingBuffer.hpp"

namespace Net
{

  /**
   * @brief TcpSocket class.
   *
   * This class represents a TcpSocket.
   * It has 2 buffers associated with it.
   */
  class TcpSocket
  {
  protected:
    /**
     * The file descriptor associated with the socket.
     * Default to -1.
     */
    int         _fd;
    /**
     * Input buffer, which stores data read from the socket
     */
    RingBuffer  _rBuf;
    /**
     * Output buffer, which stores data that are to be written to the socket.
     */
    RingBuffer  _wBuf;

  public:
    /**
     * Create a new TcpSocket
     * @param fd the fd corresponding to the socket.
     */
    TcpSocket(int fd = -1);

    /**
     * Notifies server that it will be deleted.
     */
    ~TcpSocket();

    /**
     * @return fd associated with socket
     */
    int         fd() const;

    /**
     * Write data to the socket.
     * @param source
     * @param len number of bytes to write
     * @return false if write failed, true otherwise
     * @throw Does not throw
     */
    bool write(const char *source, int len);

    /**
     * Tries to flush the output buffer by writing to the socket.
     * @return 0 if ok, something else on error
     */
    int flush();

    
    TcpSocket &operator>>(int &i);
    friend class TcpServer;
    friend class ATcpClient;
  } ;
}


#endif	/* TCPSOCKET_HPP */

