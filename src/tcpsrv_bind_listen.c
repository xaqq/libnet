/*
** tcpsrv_bind_listen.c for  in /home/xaqq/Documents/net
** 
** Made by arnaud kapp
** Login   <kapp_a@epitech.net>
** 
** Started on  Wed Feb 22 17:16:32 2012 arnaud kapp
** Last update Wed Feb 29 14:05:01 2012 arnaud kapp
*/

#include	<stdlib.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<string.h>
#include	"tcpsrv_i.h"
#include	"internal.h"

int			tcpsrv_bind(unsigned short port)
{
  struct sockaddr_in	sa;
  TcpServer		* const s = __tcp_server;
  const int		opt = 1;
  
  memset(&sa, 0, sizeof(struct sockaddr_in));
  sa.sin_family = AF_INET;
  sa.sin_addr.s_addr = INADDR_ANY;
  sa.sin_port = htons(port);
  setsockopt(s->sock.fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));
  if (bind(s->sock.fd, (struct sockaddr *)&sa,
	   sizeof(struct sockaddr_in)) == -1)
    return (0);
  set_flag(&(s->status), TCPSRV_BOUND, 1);
  return (1);
}

int		tcpsrv_listen(int max)
{
  TcpServer	*s = __tcp_server;

  if (listen(s->sock.fd, max) == -1)
    return (0);
  set_flag(&(s->status), TCPSRV_LISTENING, 1);
  return (1);
}
