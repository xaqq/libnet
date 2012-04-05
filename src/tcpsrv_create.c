/*
** tcpsrv_create.c for  in /home/xaqq/Documents/net/src
** 
** Made by arnaud kapp
** Login   <kapp_a@epitech.net>
** 
** Started on  Wed Feb 22 16:43:06 2012 arnaud kapp
** Last update Thu Apr  5 12:28:25 2012 arnaud kapp
*/

#include <stdlib.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include "tcpsrv_i.h"
#include "internal.h"

static int		epoll_init(int sock)
{
  struct epoll_event	ev;
  int			efd;

  bzero(&ev, sizeof(struct epoll_event));
  ev.events = EPOLLIN;
  ev.data.fd = get_epoll_fd();
  if ((efd = epoll_create(10)) == -1)
    {
      perror("Epoll");
      return (0);
    }
  set_epoll_fd(efd);
  ev.events = EPOLLIN;
  ev.data.fd = sock;
  epoll_ctl(efd, EPOLL_CTL_ADD, sock, &ev);
  return (1);
}

int		tcpsrv_create()
{
  TcpServer	*new;

  new = malloc(sizeof(TcpServer));
  if (!new)
    return (0);
  new->sock.fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
  if (new->sock.fd == -1)
    {
      free(new);
      return (0);
    }
  set_flag(&(new->status), TCPSRV_BOUND, 1);
  set_flag(&(new->status), TCPSRV_LISTENING, 0);
  __tcp_server = new;

  if (epoll_init(new->sock.fd) == 0)
    return (0);
  return (1);
}

