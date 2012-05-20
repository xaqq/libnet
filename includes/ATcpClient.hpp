/*
 * File:   ATcpClient.hpp
 * Author: xaqq
 *
 * Created on May 11, 2012, 9:33 PM
 */

#ifndef ATCPCLIENT_HPP
#define	ATCPCLIENT_HPP

#include <memory>

namespace Net
{
  class TcpSocket;

  class ATcpClient
  {
    typedef std::auto_ptr<TcpSocket> sockPtr;
  protected:
    sockPtr             _socket;

  public:
    virtual             ~ATcpClient();
    void                setSocket(TcpSocket *s);
    const TcpSocket &   socket() const;
    /**
     * Needed by tcp server to work with socket's internal buffer
     */
    TcpSocket &         socket();

    /**
     * User function called whenever data were read from socket
     */
    virtual void        incomingData() = 0;
    /**
     * Called when client's socket is disconnected.
     * When this function is called, the client gets removed from the TcpServer
     * client's list. However, it is the role of the application server to delete
     * the client.
     */
    virtual void        disconnection() = 0;
  } ;
}


#endif	/* ITCPCLIENT_HPP */

