/*
** write.c for  in /home/xaqq/Documents/myftp
** 
** Made by arnaud kapp
** Login   <kapp_a@epitech.net>
** 
** Started on  Tue Apr  3 16:13:44 2012 arnaud kapp
** Last update Tue Apr  3 18:45:30 2012 arnaud kapp
*/

#include	<stdio.h>
#include	<unistd.h>
#include	"tcpclient.h"

void		write_to_sock(t_tcp_client *c)
{
  unsigned char	buffer[512];
  int		r;

  r = rgbuf_r_available(c->sock.wbuffer);
  r = r > 512 ? 512 : r;
  rgbuf_read(c->sock.wbuffer, buffer, r);
  if (r)
    write(c->sock.fd, (char *)buffer, r);
}

void		swrite(t_tcp_client *c,
		       unsigned char *data,
		       int size)
{
  rgbuf_write(c->sock.wbuffer, data, size);
}
