/*
** tcpsrv_run.c for  in /home/xaqq/Documents/net
**
** Made by arnaud kapp
** Login   <kapp_a@epitech.net>
**
** Started on  Wed Feb 22 17:38:29 2012 arnaud kapp
** Last update Wed Apr 18 20:54:12 2012 arnaud kapp
*/

#define  _GNU_SOURCE
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <errno.h>
#include "tcpsrv_i.h"
#include "internal.h"

static int		disconnection(t_tcp_client *c)
{
  printf("Disconnection of one client...\n");
  tcpclient_delete(c);
  return (1);
}

static int		check_new_connection()
{
  struct sockaddr_in	sclient;
  socklen_t		sclient_l;
  t_tcp_server		*const s = __tcp_server;
  t_tcp_client		*c;
  int			fd;

  sclient_l = sizeof(struct sockaddr_in);
  if ((fd = accept4(s->sock.fd, (struct sockaddr *)(&sclient),
		    &sclient_l, SOCK_NONBLOCK)) != -1)
    {
      c = tcpclient_create(fd);
      add_fd_to_rset(fd);
      __cb_new_connection(&(c->data));
      return (1);
    }
  return (0);
}

static int		incomming_data(t_tcp_client *c)
{
  int			n;
  unsigned char		buffer[1024];
  int			omg;

  omg = 42;
  while (omg)
    {
      bzero(buffer, sizeof(buffer));
      n = read(c->sock.fd, buffer, sizeof(buffer));
      if (n == 0 || (n == -1 && (errno != EWOULDBLOCK &&
				 errno != EAGAIN)))
	return (-1);
      if (n == 0 || n == -1)
	omg = 0;
      if (omg && --omg)
	if (rgbuf_write(c->sock.buffer, buffer, n) == -1)
	  return (-1);
    }
  return (__cb_incomming_data(c));
}

static void		loop_on_clients()
{
  t_tcp_client		*c;
  t_tcp_client		*prev;
  t_select_sets		*s;
  int			del;

  s = get_select_sets();
  c = __tcp_clients;
  del = 0;
  while (c)
    {
      if (FD_ISSET(c->sock.fd, &s->write_set) == 1)
	del |= write_to_sock(c);
      if (FD_ISSET(c->sock.fd, &s->read_set) == 1)
	del |= incomming_data(c);
      if (del)
	prev = c;
      else
	prev = NULL;
      c = c->next;
      if (prev)
	disconnection(prev);
    }
}

static void		fill_sets()
{
  t_tcp_client		*c;

  select_sets_reset();
  add_fd_to_rset(__tcp_server->sock.fd);
  c = __tcp_clients;
  while (c)
    {
      add_fd_to_wset(c->sock.fd);
      add_fd_to_rset(c->sock.fd);
      c = c->next;
    }
}

int			tcpsrv_run(__attribute__((unused))int timeout)
{
  t_select_sets		*s;

  s = get_select_sets();
  if (!s)
    return (0);
  fill_sets();
  if (select(s->maxfd, &s->read_set,
	     &s->write_set, &s->x_set, NULL) == -1)
    perror("select()");
  else
    {
      loop_on_clients();
      if (FD_ISSET(__tcp_server->sock.fd, &s->read_set))
	while (check_new_connection());
    }
  return (1);
}
