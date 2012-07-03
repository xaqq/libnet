/*
** tcpsrv.h for  in /home/xaqq/Documents/net
**
** Made by arnaud kapp
** Login   <kapp_a@epitech.net>
**
** Started on  Wed Feb 22 16:43:52 2012 arnaud kapp
** Last update Tue Jul  3 20:12:59 2012 arnaud kapp
*/

#ifndef	TCPSRV_H_
# define TCPSRV_H_

# include "tcpsock.h"
# include "tcpclient.h"

typedef struct s_tcp_server
{
  int		status;
  t_tcp_socket	sock;
}	       t_tcp_server;

/*
** Callback function for new incomming connection
** malloc *user_data to application need, it is
** stored inside clients' list.
*/
int	(*__cb_new_connection)(void **user_data);

/*
** Callback function for new incomming connection
** It gives to the application a pointer to the new
** "network" client.
*/
int	(*__cb_new_connection_2)(t_tcp_client *c);

/*
** Callback function. Called when new data are avalaible
** for reading.
** If is doesnt return 0, then the client will be kicked
** from server
*/
int	(*__cb_incomming_data)(t_tcp_client *c);

/*
** Call when deleting a client
*/
int		(*__cb_free_user_data)(void *data);

void		tcpsrv_delete(void);
int		tcpsrv_create(void);
int		tcpsrv_listen(int max);
int		tcpsrv_bind(unsigned short port);
int		tcpsrv_run(int timeout);
t_tcp_client	*get_all_clients();

#endif /* !TCPSRV_I_H_ */