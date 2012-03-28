/*
** tcpsock.h for  in /home/xaqq/Documents/net
** 
** Made by arnaud kapp
** Login   <kapp_a@epitech.net>
** 
** Started on  Wed Feb 22 16:45:54 2012 arnaud kapp
** Last update Tue Feb 28 12:54:52 2012 arnaud kapp
*/

#ifndef	TCPSOCK_H
#define	TCPSOCK_H

#include	"ring_buffer.h"

typedef struct	s_tcp_socket
{
  int		fd;
  int		available_bytes;
  RingBuffer	*buffer;
}	       t_tcp_socket;

typedef t_tcp_socket TcpSocket;

#endif
