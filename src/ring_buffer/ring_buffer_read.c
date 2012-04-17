/*
** ring_buffer_read.c for  in /home/xaqq/Documents/net
**
** Made by arnaud kapp
** Login   <kapp_a@epitech.net>
**
** Started on  Tue Apr 17 17:22:07 2012 arnaud kapp
** Last update Tue Apr 17 17:42:25 2012 arnaud kapp
*/

#include	<stdlib.h>
#include	<strings.h>
#include	<string.h>
#include	<stdio.h>
#include	"ring_buffer.h"

static int	read_i(t_ring_buff *b, unsigned char *d, int s)
{
  int		direct;

  if (s > rgbuf_r_available(b))
    s = rgbuf_r_available(b);
  direct = b->size - b->s;
  direct = direct > s ? s : direct;
  memcpy(d, b->data + b->s, direct);
  s -= direct;
  b->s += direct;
  b->s %= b->size;
  if (s)
    read_i(b, d + direct, s);
  return (s);
}

int		rgbuf_read(t_ring_buff *b, unsigned char *d, int s)
{
  b->last_start = b->s;
  return (read_i(b, d, s));
}

int		rgbuf_read_rb(t_ring_buff *b)
{
  if (b->s == b->last_start)
    return (0);
  b->s = b->last_start;
  return (1);
}
