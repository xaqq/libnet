#include	"TcpServer.hpp"
#include	"TcpSocket.hpp"
#include	<iostream>
#include	<errno.h>
#include	<cstdio>
#include	<stdlib.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<string.h>
using namespace Net;

TcpServer       *TcpServer::_instance = 0;
TcpServer::factoryPtr TcpServer::_factory = 0;

TcpServer::TcpServer()
{
  _sock = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
  if (_sock == -1)
    {
      std::cerr << "Cannot create server socket :(" << std::endl;
    }
}

TcpServer::~TcpServer()
{
  if (_sock != -1)
    close(_sock);
}

TcpServer       *TcpServer::instance()
{
  if (!_instance)
    _instance = new TcpServer;
  return _instance;
}

bool TcpServer::bindlol(unsigned short port /* = 4242 */)
{
  struct sockaddr_in	sa;
  const  int            i = 1;

  memset(&sa, 0, sizeof (struct sockaddr_in) );
  sa.sin_family = AF_INET;
  sa.sin_addr.s_addr = INADDR_ANY;
  sa.sin_port = htons(port);

  setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, &i, sizeof (int) );
  if (bind(_sock, (struct sockaddr *) &sa,
	   sizeof (struct sockaddr_in)) != 0)
    {
      perror("bind:");
      return (false);
    }
  return (true);
}

bool TcpServer::listen(int max /* = 10 */)
{
  if (::listen(_sock, max) != 0)
    {
      perror("listen:");
      return false;
    }
  return true;
}

int TcpServer::incomingData(ATcpClient* c)
{
  int			n;
  char                  buffer[1024];

  bzero(buffer, sizeof (buffer));
  n = read(c->socket().fd(), buffer, sizeof (buffer));
  if (n == 0 || (n == -1 && (errno != EWOULDBLOCK &&
                             errno != EAGAIN)))
    return (-1);
  if (n == 0 || n == -1)
    return (0);
  if (c->socket()._rBuf.write(buffer, n) != true)
    return (-1);
  std::cout << c->socket()._rBuf.rAvailable() << std::endl;
  c->incomingData();
  return (0);
}

void TcpServer::loopOnClients()
{
  int           del;

  for (clientsList::iterator it = _clients.begin();
       it != _clients.end();
       )
    {
      del = 0;
      if (FD_ISSET((*it)->socket().fd(), &_wSet) == 1)
        del |= (*it)->socket().flush();
      if (FD_ISSET((*it)->socket().fd(), &_rSet) == 1)
	del |= incomingData(*it);
      if (del)
        {
          (*it)->disconnection();
          it = _clients.erase(it);
        }
      else
        ++it;
    }
}

bool TcpServer::run(int timeout /* = 0 */)
{
  struct timeval	t;

  fillSets();
  t.tv_usec = timeout * 1000;
  t.tv_sec = 0;
  if (select(_maxFd + 1, &_rSet, &_wSet, &_eSet, &t) == -1)
    perror("select()");
  else
    {
      loopOnClients();
      if (FD_ISSET(_sock, &_rSet))
        while (checkNewConnection());
    }
  return (1);

}

bool TcpServer::checkNewConnection()
{
  struct sockaddr_in	sclient;
  socklen_t		sclient_l;
  ATcpClient            *client;
  TcpSocket             *sock;
  int			fd;

  sclient_l = sizeof (struct sockaddr_in) ;
  if ((fd = accept4(_sock, (struct sockaddr *) (&sclient),
                    &sclient_l, SOCK_NONBLOCK)) != -1)
    {
      client = _factory();
      if (!client)
        return false;
      if (!dynamic_cast<ATcpClient *> (client))
        return false;
      sock = new TcpSocket(fd);
      client->setSocket(sock);
      _clients.push_back(client);
      return true;
    }
  return false;
}

void TcpServer::fillSets()
{
  int           fd;

  FD_ZERO(&_wSet);
  FD_ZERO(&_rSet);
  FD_ZERO(&_eSet);
  _maxFd = 0;
  FD_SET(_sock, &_rSet);
  _maxFd = _sock > _maxFd ? _sock : _maxFd;
  for (clientsList::const_iterator it = _clients.begin();
       it != _clients.end();
       ++it)
    {
      fd = (*it)->socket().fd();
      FD_SET(fd, &_rSet);
      if ((*it)->socket()._wBuf.rAvailable())
        FD_SET(fd, &_wSet);
      _maxFd = fd > _maxFd ? fd : _maxFd;
    }
}
