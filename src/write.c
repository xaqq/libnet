/*
** write.c for  in /home/xaqq/Documents/myftp
**
** Made by arnaud kapp
** Login   <kapp_a@epitech.net>
**
** Started on  Tue Apr  3 16:13:44 2012 arnaud kapp
** Last update Sat Jun  9 17:15:56 2012 arnaud kapp
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
#include	"ring_buffer.h"

int			write_to_sock(t_tcp_client *c)
{
  unsigned char		buffer[1024 * 42];
  int			r;
  int			ret;

  r = rgbuf_r_available(c->sock.wbuffer);
  r = r > (int)sizeof(buffer) ? (int)sizeof(buffer) : r;
  if (r)
    {
      rgbuf_read(c->sock.wbuffer, buffer, r);
      if ((ret = write(c->sock.fd, (char *)buffer, r)) == -1)
	{
	  if (errno != EWOULDBLOCK &&
	      errno != EAGAIN)
	    return (-1);
	  rgbuf_read_rb(c->sock.wbuffer);
	}
      else if (ret != r)
	{
	  rgbuf_read_rb_x(c->sock.wbuffer, r - ret);
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
