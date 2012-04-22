/*
** tcpclient.h for  in /home/xaqq/Documents/net
**
** Made by arnaud kapp
** Login   <kapp_a@epitech.net>
**
** Started on  Wed Feb 22 16:56:05 2012 arnaud kapp
** Last update Sun Apr 22 15:04:02 2012 arnaud kapp
*/

#ifndef	TCPCLIENT_H_
# define TCPCLIENT_H_

# include "tcpsock.h"

/*
** data is a pointer to application's
** data for client
*/
typedef struct s_tcp_client
{
  t_tcp_socket		sock;
  void			*data;
  struct s_tcp_client	*next;
  struct s_tcp_client	*prev;
}		t_tcp_client;


__attribute__((visibility("internal")))
t_tcp_client	*tcpclient_create(int fd);
void		tcpclient_delete(t_tcp_client *c);

__attribute__((visibility("internal")))
int		write_to_sock(t_tcp_client *c);
void		swrite(t_tcp_client *c,
		       unsigned char *data,
		       int size);

#endif /* !TCPCLIENT_H_ */
