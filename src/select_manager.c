/*
** select_manager.c for  in /home/xaqq/Documents/net
**
** Made by arnaud kapp
** Login   <kapp_a@epitech.net>
**
** Started on  Tue Apr 17 15:30:32 2012 arnaud kapp
** Last update Thu Apr 19 22:31:22 2012 arnaud kapp
*/

#include <stdlib.h>
#include "tcpsrv_i.h"

t_select_sets		*get_select_sets()
{
  static t_select_sets	*s = NULL;

  if (!s)
    {
      s = malloc(sizeof(t_select_sets));
      select_sets_reset();
    }
  return (s);
}

void		select_sets_reset()
{
  t_select_sets *s;

  s = get_select_sets();
  FD_ZERO(&(s->read_set));
  FD_ZERO(&(s->write_set));
  FD_ZERO(&(s->x_set));
  s->maxfd = -1;
}

void		add_fd_to_wset(int fd)
{
  t_select_sets *s;

  s = get_select_sets();
  if (!s)
    return;
  FD_SET(fd, &(s->write_set));
  if (fd + 1 > s->maxfd)
    s->maxfd = fd + 1;
}

void			add_fd_to_rset(int fd)
{
  t_select_sets		*s;

  s = get_select_sets();
  if (!s)
    return;
  FD_SET(fd, &(s->read_set));
  if (fd + 1 > s->maxfd)
    s->maxfd = fd + 1;
}

void			fill_sets()
{

  t_tcp_client		*c;

  select_sets_reset();
  add_fd_to_rset(__tcp_server->sock.fd);
  c = __tcp_clients;
  while (c)
    {
      if (rgbuf_r_available(c->sock.wbuffer))
	add_fd_to_wset(c->sock.fd);
      add_fd_to_rset(c->sock.fd);
      c = c->next;
    }
}

