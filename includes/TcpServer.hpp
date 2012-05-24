/*
 * File:   TcpServer.hpp
 * Author: xaqq
 *
 * Created on May 11, 2012, 9:49 PM
 */

#ifndef TCPSERVER_HPP
#define	TCPSERVER_HPP

#include <sys/select.h>
#include <list>
#include "ATcpClient.hpp"

namespace Net
{
  class ATcpClient;

  /**
   * @brief A TcpServer class.
   *
   * TcpServer is singleton-based.
   * The server calls a user factory function to create its new client when a
   * connection is pending. The client's class must inherits ATcpClient.
   *
   * When the connection is closed, the client is removed from the TcpServer's
   * clients list and is not watched anymore. However, because the user factory
   * created the Client object, it is not deleted.
   * User should delete its client when "disconnection" function is called.
   */
  class TcpServer
  {
    typedef std::list<ATcpClient *> clientsList;
  private:
    static TcpServer            *_instance;
    TcpServer();

    /**
     * Server socket
     */
    int                         _sock;
    /**
     * Clients ' list
     */
    clientsList                 _clients;
    fd_set                      _wSet;
    fd_set                      _rSet;
    fd_set                      _eSet;
    /**
     * Max fd (used by select).
     */
    int                         _maxFd;

  public:
    /**
     * Return the singleton
     * @return The singleton instance
     */
    static TcpServer *instance();

    ~TcpServer();

    /**
     * Attempt to bind the server to port port
     * @param port
     * @return true on success, false on error
     */
    bool        bind(unsigned short port = 4242);

    /**
     * Makes the server listen.
     * @param max max pending connection
     * @return true on success, false on error
     */
    bool        listen(int max = 10);

    /**
     * This is the loop of the tcp server.
     * @param timeout timeout of multiplexer (in ms)
     * @return false is an error occurred (should not happen)
     */
    bool        run(int timeout = 0);
    
    typedef ATcpClient *(*factoryPtr)(void);
    /**
     * This is a factory's function pointer which points to a user defined
     * function whose role is to create a new TcpClient which itself inherits
     * ATcpClient
     */
    static factoryPtr _factory;


  protected:
    /**
     * Accept new incoming connection
     * @return true is a new connection has been accepted
     */
    bool checkNewConnection();

    /**
     * Fill select's fds sets.
     */
    void fillSets();

    /**
     * Loop over client, doing lib job
     */
    void loopOnClients();

    /**
     * Handle new data on client socket
     * @param c the client
     * @return 0 if ok, something else otherwise. Returning something else
     * here cause the client not to be watched anymore
     */
    int  incomingData(ATcpClient *c);
  } ;
}

#endif	/* TCPSERVER_HPP */

