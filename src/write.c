/*
** write.c for  in /home/xaqq/Documents/myftp
**
** Made by arnaud kapp
** Login   <kapp_a@epitech.net>
**
** Started on  Tue Apr  3 16:13:44 2012 arnaud kapp
** Last update Thu Apr 19 17:24:24 2012 arnaud kapp
*/

#include	<errno.h>
#include	<stdio.h>
#include	<unistd.h>
#include	<sys/epoll.h>
#include	<sys/socket.h>
#include	<strings.h>
#include	<sys/types.h>
#include	<sys/ioctl.h>
#include	"tcpsrv_i.h"
#include	"tcpclient.h"

int			write_to_sock(t_tcp_client *c)
{
  unsigned char		buffer[512];
  int			r;

  r = rgbuf_r_available(c->sock.wbuffer);
  r = r > 512 ? 512 : r;
  if (r)
    {
      rgbuf_read(c->sock.wbuffer, buffer, r);
      if (write(c->sock.fd, (char *)buffer, r) == -1)
	{
	  if (errno != EWOULDBLOCK &&
	      errno != EAGAIN)
	    return (-1);
	  rgbuf_read_rb(c->sock.wbuffer);
	}
    }
  return (0);
}

void			swrite(t_tcp_client *c,
			       unsigned char *data,
			       int size)
{
  rgbuf_write(c->sock.wbuffer, data, size);
}
