/*
** tcpsrv_i.h for  in /home/xaqq/Documents/net
**
** Made by arnaud kapp
** Login   <kapp_a@epitech.net>
**
** Started on  Wed Feb 22 17:21:22 2012 arnaud kapp
** Last update Tue Apr 17 15:35:26 2012 arnaud kapp
*/

#ifndef		TCPSRV_I_H
# define	TCPSRV_I_H

# include "tcpsrv.h"
# include <sys/select.h>

# define	TCPSRV_BOUND		1
# define	TCPSRV_LISTENING	2

typedef struct	s_select_sets
{
  fd_set	read_set;
  fd_set	write_set;
  fd_set	x_set;
}		t_select_sets

/*
** Global pointer on server instance
*/
__attribute__((visibility("internal")))
t_tcp_server	*__tcp_server;

/*
** Global pointer on clients' linked list.
*/
__attribute__((visibility("internal")))
t_tcp_client	*__tcp_clients;

__attribute__((visibility("internal")))
t_select_sets	*get_select_sets();

#endif /* !TCPSRV_I_H */
