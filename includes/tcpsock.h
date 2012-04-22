/*
** tcpsock.h for  in /home/xaqq/Documents/net
**
** Made by arnaud kapp
** Login   <kapp_a@epitech.net>
**
** Started on  Wed Feb 22 16:45:54 2012 arnaud kapp
** Last update Sun Apr 22 15:03:19 2012 arnaud kapp
*/

#ifndef		TCPSOCK_H_
# define	TCPSOCK_H_

# include	"ring_buffer.h"

typedef struct	s_tcp_socket
{
  int		fd;
  int		available_bytes;
  t_ring_buff	*buffer;
  t_ring_buff	*wbuffer;
}	       t_tcp_socket;

#endif /* !TCPSOCK_H_ */
