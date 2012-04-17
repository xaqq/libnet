/*
** tcpsrv_create.c for  in /home/xaqq/Documents/net/src
**
** Made by arnaud kapp
** Login   <kapp_a@epitech.net>
**
** Started on  Wed Feb 22 16:43:06 2012 arnaud kapp
** Last update Tue Apr 17 17:31:04 2012 arnaud kapp
*/

#include <stdlib.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include "tcpsrv_i.h"
#include "internal.h"

int		tcpsrv_create()
{
  t_tcp_server	*new;

  new = malloc(sizeof(t_tcp_server));
  if (!new)
    return (0);
  new->sock.fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
  if (new->sock.fd == -1)
    {
      free(new);
      return (0);
    }
  set_flag(&(new->status), TCPSRV_BOUND, 0);
  set_flag(&(new->status), TCPSRV_LISTENING, 0);
  __tcp_server = new;
  return (1);
}

