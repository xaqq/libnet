/*
** tcpsrv_run.c for  in /home/xaqq/Documents/net
**
** Made by arnaud kapp
** Login   <kapp_a@epitech.net>
**
** Started on  Wed Feb 22 17:38:29 2012 arnaud kapp
** Last update Thu Apr  5 13:10:18 2012 arnaud kapp
*/

#define  _GNU_SOURCE
#include <stdlib.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include "tcpsrv_i.h"
#include "internal.h"

static int		check_new_connection()
{
  struct sockaddr_in	sclient;
  socklen_t		sclient_l;
  TcpServer		*const s = __tcp_server;
  TcpClient		*c;
  int			fd;
  struct epoll_event	e;

  bzero(&e, sizeof(struct epoll_event));
  sclient_l = sizeof(struct sockaddr_in);
  if ((fd = accept4(s->sock.fd, (struct sockaddr *)(&sclient),
		    &sclient_l, SOCK_NONBLOCK)) != -1)
    {
      c = tcpclient_create(fd);
      e.events = EPOLLIN | EPOLLRDHUP;
      e.data.fd = c->sock.fd;
      epoll_ctl(get_epoll_fd(), EPOLL_CTL_ADD, c->sock.fd, &e);
      __cb_new_connection(&(c->data));
      return (1);
    }
  return (0);
}

static TcpClient	*fd_to_client(int fd)
{
  TcpClient *c;

  c = __tcp_clients;
  while (c)
    {
      if (c->sock.fd == fd)
	return (c);
      c = c->next;
    }
  fprintf(stderr, "Data received, %s",
	  "but fd does not match any in client list\n");
  return (NULL);
}

static void		incomming_data(TcpClient *c)
{
  int			n;
  unsigned char		buffer[1024];

  if (!c)
    return;
  while (1)
    {
      bzero(buffer, sizeof(buffer));
      n = read(c->sock.fd, buffer, sizeof(buffer));
      if (!n || n == -1)
	break;
      rgbuf_write(c->sock.buffer, buffer, n);
    }
  __cb_incomming_data(c);
}

static int		disconnection(TcpClient *c)
{
  printf("Disconnection of one client...\n");
  tcpclient_delete(c);
  return (1);
}

/*
** Attention code autiste a cause de la norme
*/
int			tcpsrv_run(int timeout)
{
  struct epoll_event	events[42];
  int			ne;
  int			i;

  ne = epoll_wait(get_epoll_fd(), events, 42, timeout);
  i = 0;
  while (i < ne)
    {
      if (events[i].data.fd == __tcp_server->sock.fd)
	while (check_new_connection());
      else
	{
	  if (events[i].events & EPOLLRDHUP)
	    return (disconnection(fd_to_client(events[i].data.fd)));
	  if (events[i].events & EPOLLIN)
	    incomming_data(fd_to_client(events[i].data.fd));
	  if (events[i].events & EPOLLOUT)
	    write_to_sock(fd_to_client(events[i].data.fd));
	}
      i++;
    }
  return (1);
}
