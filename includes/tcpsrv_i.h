/*
** tcpsrv_i.h for  in /home/xaqq/Documents/net
**
** Made by arnaud kapp
** Login   <kapp_a@epitech.net>
**
** Started on  Wed Feb 22 17:21:22 2012 arnaud kapp
** Last update Wed Apr 25 15:00:53 2012 arnaud kapp
*/

#ifndef		TCPSRV_I_H_
# define	TCPSRV_I_H_

# include "tcpsrv.h"
# include <sys/select.h>

# define	TCPSRV_BOUND		1
# define	TCPSRV_LISTENING	2

typedef struct	s_select_sets
{
  fd_set	read_set;
  fd_set	write_set;
  fd_set	x_set;
  int		maxfd;
}		t_select_sets;

/*
** Global pointer on server instance
*/
__attribute__((visibility("internal")))
extern t_tcp_server	*__tcp_server;

/*
** Global pointer on clients' linked list.
*/
__attribute__((visibility("internal")))
t_tcp_client	*__tcp_clients;

__attribute__((visibility("internal")))
t_select_sets	*get_select_sets();

__attribute__((visibility("internal")))
void		select_sets_reset();

__attribute__((visibility("internal")))
void		add_fd_to_wset(int fd);

__attribute__((visibility("internal")))
void		add_fd_to_rset(int fd);

__attribute__((visibility("internal")))
void		fill_sets();

/*
** fd are added to write set if there is data in
** socket's write buffer
*/
#endif /* !TCPSRV_I_H_ */
