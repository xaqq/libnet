/*
** tcpsrv.c for  in /home/xaqq/Documents/net
** 
** Made by arnaud kapp
** Login   <kapp_a@epitech.net>
** 
** Started on  Wed Feb 22 17:00:00 2012 arnaud kapp
** Last update Tue Feb 28 11:29:03 2012 arnaud kapp
*/

#include <stdlib.h>
#include "tcpsrv.h"

int		(*__cb_incomming_data)(TcpClient *c)	 = NULL;
int		(*__cb_new_connection)(void **user_data) = NULL;
TcpServer	*__tcp_server = NULL;
TcpClient	*__tcp_clients = NULL;
