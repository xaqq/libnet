/*
** ring_buffer.c for  in /home/xaqq/Documents/net
**
** Made by arnaud kapp
** Login   <kapp_a@epitech.net>
**
** Started on  Wed Feb 22 21:48:40 2012 arnaud kapp
** Last update Sat Jun  9 17:04:34 2012 arnaud kapp
*/

#include	<stdlib.h>
#include	<strings.h>
#include	<string.h>
#include	<stdio.h>
#include	"ring_buffer.h"

static int	resize(t_ring_buff *b)
{
  unsigned char	*ptr;
  unsigned char	*tmp;
  int		r;

  if (b->size + RGBUF_SIZE > RGBUF_MAX_SIZE)
    return (0);
  tmp = NULL;
  if ((r = rgbuf_r_available(b)))
    {
      tmp = malloc(r);
      if (!tmp)
	return (0);
      rgbuf_read(b, tmp, r);
    }
  if ((ptr = realloc(b->data, b->size + RGBUF_SIZE)) == 0)
    return (0);
  memcpy(ptr, tmp, r);
  b->s = 0;
  b->last_start = 0;
  b->e = r;
  b->data = ptr;
  b->size += RGBUF_SIZE;
  free(tmp);
  return (1);
}

t_ring_buff	*rgbuf_create(int s)
{
  t_ring_buff	*n;

  s++;
  n = malloc(sizeof(t_ring_buff));
  if (!n)
    return (NULL);
  n->size = s;
  n->data = malloc(s);
  if (!n->data)
    {
      free(n);
      return (NULL);
    }
  n->s = 0;
  n->e = 0;
  n->max_size = RGBUF_MAX_SIZE;
  bzero(n->data, s);
  return (n);
}

void		rgbuf_delete(t_ring_buff *b)
{
  if (b)
    free(b->data);
  free(b);
}

int		rgbuf_write(t_ring_buff *b, unsigned char *d, int s)
{
  int		direct;

  while (rgbuf_w_available(b) < s)
    if (!resize(b))
      return (-1);
  if (rgbuf_w_available(b) >= s)
    {
      direct = b->size - b->e;
      direct = direct > s ? s : direct;
      memcpy(b->data + b->e, d, direct);
      s -= direct;
      b->e += direct;
      b->e %= b->size;
      if (s)
	rgbuf_write(b, d + direct, s);
      return (s);
    }
  return (0);
}

int		rgbuf_read_rb_x(t_ring_buff *b, int x)
{
  int           tmp;

  tmp = b->s;
  tmp -= diff;
  tmp %= b->size;
  if (tmp < 0)
    b->s = b->size - abs(tmp);
  else
    b->s = tmp;
}
