/*
** tcpsrv.h for  in /home/xaqq/Documents/net
** 
** Made by arnaud kapp
** Login   <kapp_a@epitech.net>
** 
** Started on  Wed Feb 22 16:43:52 2012 arnaud kapp
** Last update Wed Feb 29 13:38:05 2012 arnaud kapp
*/

#ifndef	TCPSRV_H
#define TCPSRV_H

#include "tcpsock.h"
#include "tcpclient.h"

typedef struct s_tcp_server
{
  int		status;
  TcpSocket	sock;
}	       t_tcp_server;

typedef t_tcp_server TcpServer;

/**
 * Callback function for new incomming connection
 * malloc *user_data to application need, it is
 * stored inside clients' list.
 */
int	(*__cb_new_connection)(void **user_data);

/**
 * Callback function. Called when new data are avalaible
 * for reading.
 */
int	(*__cb_incomming_data)(TcpClient *c);

/**
 * Call when deleting a client
 */
int	(*__cb_free_user_data)(void *data);

void	tcpsrv_delete(void);
int	tcpsrv_create(void);
int	tcpsrv_listen(int max);
int	tcpsrv_bind(unsigned short port);

#endif
