/*
** tcpclient.h for  in /home/xaqq/Documents/net
** 
** Made by arnaud kapp
** Login   <kapp_a@epitech.net>
** 
** Started on  Wed Feb 22 16:56:05 2012 arnaud kapp
** Last update Wed Feb 22 21:42:18 2012 arnaud kapp
*/

#ifndef	TCPCLIENT_H
#define TCPCLIENT_H

#include "tcpsock.h"

typedef struct s_tcp_client
{
  TcpSocket		sock;
  void			*data; // application data for client
  struct s_tcp_client	*next;
  struct s_tcp_client	*prev;
}		t_tcp_client;

typedef t_tcp_client TcpClient;

TcpClient	*tcpclient_create(int fd);
void		tcpclient_delete(TcpClient *c);

#endif
