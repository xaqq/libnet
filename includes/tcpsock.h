/*
** tcpsock.h for  in /home/xaqq/Documents/net
**
** Made by arnaud kapp
** Login   <kapp_a@epitech.net>
**
** Started on  Wed Feb 22 16:45:54 2012 arnaud kapp
** Last update Sun Apr  8 19:05:53 2012 arnaud kapp
*/

#ifndef		TCPSOCK_H
# define	TCPSOCK_H

# include	"ring_buffer.h"

typedef struct	s_tcp_socket
{
  int		fd;
  int		available_bytes;
  t_ring_buff	*buffer;
  t_ring_buff	*wbuffer;
}	       t_tcp_socket;

typedef t_tcp_socket t_tcp_socket;

#endif /* !TCPSOCK_H */
