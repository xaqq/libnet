/*
** tcpsrv_i.h for  in /home/xaqq/Documents/net
**
** Made by arnaud kapp
** Login   <kapp_a@epitech.net>
**
** Started on  Wed Feb 22 17:21:22 2012 arnaud kapp
** Last update Sun Apr 22 15:08:47 2012 arnaud kapp
*/

#ifndef		TCPSRV_I_H_
# define	TCPSRV_I_H_

# include "tcpsrv.h"

# define	TCPSRV_BOUND		1
# define	TCPSRV_LISTENING	2

/**
 * Global pointer on server instance
 */
__attribute__((visibility("internal")))
extern t_tcp_server	*__tcp_server;

/**
 * Global pointer on clients' linked list.
 */
__attribute__((visibility("internal")))
t_tcp_client	*__tcp_clients;

__attribute__((visibility("internal")))
int		get_epoll_fd();

#endif /* !TCPSRV_I_H */
