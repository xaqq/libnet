/*
** tcpclient.h for  in /home/xaqq/Documents/net
** 
** Made by arnaud kapp
** Login   <kapp_a@epitech.net>
** 
** Started on  Wed Feb 22 16:56:05 2012 arnaud kapp
** Last update Tue Apr  3 16:20:15 2012 arnaud kapp
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

__attribute__((visibility("internal")))
TcpClient	*tcpclient_create(int fd);
void		tcpclient_delete(TcpClient *c);

__attribute__((visibility("internal")))
void		write_to_sock(t_tcp_client *c);
void		swrite(t_tcp_client *c,
		       unsigned char *data,
		       int size);

#endif
