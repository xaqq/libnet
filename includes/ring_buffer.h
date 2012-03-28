/*
** ring_buffer.h for  in /home/xaqq/Documents/net
** 
** Made by arnaud kapp
** Login   <kapp_a@epitech.net>
** 
** Started on  Wed Feb 22 21:32:42 2012 arnaud kapp
** Last update Tue Feb 28 13:11:05 2012 arnaud kapp
*/

#ifndef	RINGBUFFER_H
#define RINGBUFFER_H

#define	RGBUF_SIZE	2048

typedef struct s_ring_buff
{
  unsigned char	*data;
  int		size;
  int		s; //start
  int		e; //end
}		t_ring_buff;

typedef t_ring_buff RingBuffer;

RingBuffer	*rgbuf_create(int s);
void		rgbuf_delete(RingBuffer *b);
int		rgbuf_is_empty(RingBuffer *b);
int		rgbuf_is_full(RingBuffer *b);
int		rgbuf_write(RingBuffer *b, unsigned char *d, int s);
int		rgbuf_read(RingBuffer *b, unsigned char *d, int s);
int		rgbuf_r_available(RingBuffer *b);
int		rgbuf_w_available(RingBuffer *b);

#endif
