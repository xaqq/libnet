/*
** tcpsrv_delete.c for  in /home/xaqq/Documents/net
**
** Made by arnaud kapp
** Login   <kapp_a@epitech.net>
**
** Started on  Wed Feb 29 13:36:30 2012 arnaud kapp
** Last update Wed Apr 25 15:01:45 2012 arnaud kapp
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	"tcpsrv_i.h"

void		tcpsrv_delete(void)
{
  while (__tcp_clients)
    tcpclient_delete(__tcp_clients);
  if (__tcp_server)
    {
      close(__tcp_server->sock.fd);
      free(__tcp_server);
      __tcp_server = NULL;
    }
  if (get_select_sets())
    free(get_select_sets());
}
