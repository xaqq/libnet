/*
** ring_buffer.c for  in /home/xaqq/Documents/net
** 
** Made by arnaud kapp
** Login   <kapp_a@epitech.net>
** 
** Started on  Wed Feb 22 21:48:40 2012 arnaud kapp
** Last update Tue Feb 28 14:48:54 2012 arnaud kapp
*/

#include	<stdlib.h>
#include	<strings.h>
#include	<string.h>
#include	<stdio.h>
#include	"ring_buffer.h"

static int	resize(RingBuffer *b)
{
  unsigned char	*ptr;
  unsigned char	*tmp;
  int		r;
  
  if ((r = rgbuf_r_available(b)))
    {
      tmp = malloc(r);
      if (!tmp)
	return (0);
      rgbuf_read(b, tmp, r);
    }
  ptr = realloc(b->data, b->size + RGBUF_SIZE);
  if (!ptr)
    return (0);
  memcpy(ptr, tmp, r);
  b->s = 0;
  b->e = r;
  b->data = ptr;
  b->size += RGBUF_SIZE;
  return (1);
}

RingBuffer	*rgbuf_create(int s)
{
  RingBuffer	*n;
  
  s++;
  n = malloc(sizeof(RingBuffer));
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
  bzero(n->data, s);
  return (n);
}

void		rgbuf_delete(RingBuffer *b)
{
  if (b)
    free(b->data);
  free(b);
}

int		rgbuf_write(RingBuffer *b, unsigned char *d, int s)
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

int		rgbuf_read(RingBuffer *b, unsigned char *d, int s)
{
  int		direct;

  if (s > rgbuf_r_available(b))
    s = rgbuf_r_available(b);
  
  direct = b->size - b->s;
  direct = direct > s ? s : direct;
  memcpy(d, b->data + b->s, direct);
  s -= direct;
  b->s+= direct;
  b->s %= b->size;
  if (s)
    rgbuf_read(b, d + direct, s);
  return (s);
}
