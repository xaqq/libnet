/*
** tcpsrv.c for  in /home/xaqq/Documents/net
**
** Made by arnaud kapp
** Login   <kapp_a@epitech.net>
**
** Started on  Wed Feb 22 17:00:00 2012 arnaud kapp
** Last update Wed Apr 18 19:43:56 2012 arnaud kapp
*/

#include <stdlib.h>
#include "tcpsrv_i.h"

int		(*__cb_incomming_data)(t_tcp_client *c)	 = NULL;
int		(*__cb_new_connection)(void **user_data) = NULL;
t_tcp_server	*__tcp_server = NULL;
t_tcp_client	*__tcp_clients = NULL;

t_tcp_client	*get_all_clients()
{
  return (__tcp_clients);
}
