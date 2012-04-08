/*
** ring_buffer_st.c for  in /home/xaqq/Documents/net/src/ring_buffer
**
** Made by arnaud kapp
** Login   <kapp_a@epitech.net>
**
** Started on  Fri Feb 24 21:53:03 2012 arnaud kapp
** Last update Thu Apr  5 13:10:47 2012 arnaud kapp
*/

#include	"ring_buffer.h"

int		rgbuf_is_empty(t_ring_buff *b)
{
  if (b->s == b->e)
    return (1);
  return (0);
}

int		rgbuf_is_full(t_ring_buff *b)
{
  if ((b->e + 1) % b->size == b->s)
    return (1);
  return (0);
}

int		rgbuf_r_available(t_ring_buff *b)
{
  if (b->s == b->e)
    return (0);
  if (b->s < b->e)
    return (b->e - b->s);
  if (b->s > b->e)
    return (b->e + b->size - b->s);
  return (0);
}

int		rgbuf_w_available(t_ring_buff *b)
{
  return (b->size - rgbuf_r_available(b) - 1);
}
