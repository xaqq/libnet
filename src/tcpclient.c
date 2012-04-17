/*
** tcpclient.c for  in /home/xaqq/Documents/net
**
** Made by arnaud kapp
** Login   <kapp_a@epitech.net>
**
** Started on  Wed Feb 22 17:51:37 2012 arnaud kapp
** Last update Tue Apr 17 15:35:54 2012 arnaud kapp
*/

#include <sys/epoll.h>
#include <stdlib.h>
#include "tcpsrv_i.h"
#include "tcpclient.h"

__attribute__((visibility("internal")))
t_tcp_client	*tcpclient_create(int fd)
{
  t_tcp_client	*c;

  c = malloc(sizeof(t_tcp_client));
  if (!c)
    return (NULL);
  c->sock.fd = fd;

  c->prev = NULL;
  c->next = __tcp_clients;
  c->sock.buffer = rgbuf_create(RGBUF_SIZE);
  c->sock.wbuffer = rgbuf_create(RGBUF_SIZE);
  if (!c->sock.buffer || !c->sock.wbuffer)
    return (NULL);
  if (__tcp_clients)
    __tcp_clients->prev = c;
  __tcp_clients = c;
  return (c);
}

void		tcpclient_delete(t_tcp_client *c)
{
  if (__cb_free_user_data)
    __cb_free_user_data(c->data);

  if (c->prev)
    c->prev->next = c->next;
  if (c->next)
    c->next->prev = c->prev;
  if (c == __tcp_clients)
    __tcp_clients = c->next;
  rgbuf_delete(c->sock.buffer);
  rgbuf_delete(c->sock.wbuffer);
  free(c);
}
