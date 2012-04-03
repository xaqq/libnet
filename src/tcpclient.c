/*
** tcpclient.c for  in /home/xaqq/Documents/net
** 
** Made by arnaud kapp
** Login   <kapp_a@epitech.net>
** 
** Started on  Wed Feb 22 17:51:37 2012 arnaud kapp
** Last update Tue Apr  3 11:36:36 2012 arnaud kapp
*/

#include <sys/epoll.h>
#include <stdlib.h>
#include "tcpsrv_i.h"
#include "tcpclient.h"

TcpClient	*tcpclient_create(int fd)
{
  TcpClient	*c;

  c = malloc(sizeof(TcpClient));
  if (!c)
    return (NULL);
  c->sock.fd = fd;

  c->prev = NULL;
  c->next = __tcp_clients;
  c->sock.buffer = rgbuf_create(RGBUF_SIZE);
  if (!c->sock.buffer)
    return (NULL);
  if (__tcp_clients)
    __tcp_clients->prev = c;
  __tcp_clients = c;
  return (c);
}

void		tcpclient_delete(TcpClient *c)
{
  if (__cb_free_user_data)
    __cb_free_user_data(c->data);
  
  if (c->prev)
    c->prev->next = c->next;
  if (c->next)
    c->next->prev = c->prev;
  if (c == __tcp_clients)
    __tcp_clients = c->next;
  epoll_ctl(get_epoll_fd(), EPOLL_CTL_DEL, c->sock.fd, NULL);
  rgbuf_delete(c->sock.buffer);
  free(c);  
}
