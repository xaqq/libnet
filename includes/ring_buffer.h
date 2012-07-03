/*
** ring_buffer.h for  in /home/xaqq/Documents/net
**
** Made by arnaud kapp
** Login   <kapp_a@epitech.net>
**
** Started on  Wed Feb 22 21:32:42 2012 arnaud kapp
** Last update Sat Jun  9 17:15:52 2012 arnaud kapp
*/

#ifndef	RINGBUFFER_H
# define RINGBUFFER_H

# define	RGBUF_SIZE	131072
# ifndef RGBUF_MAX_SIZE
#  define RGBUF_MAX_SIZE	282144
# endif

typedef struct	s_ring_buff
{
  unsigned char	*data;
  int		size;
  int		s; //start
  int		e; //end
  int		last_start;
  int		max_size;
}		t_ring_buff;

t_ring_buff	*rgbuf_create(int s);
void		rgbuf_delete(t_ring_buff *b);
int		rgbuf_is_empty(t_ring_buff *b);
int		rgbuf_is_full(t_ring_buff *b);
int		rgbuf_write(t_ring_buff *b, unsigned char *d, int s);
int		rgbuf_read(t_ring_buff *b, unsigned char *d, int s);
int		rgbuf_r_available(t_ring_buff *b);
int		rgbuf_w_available(t_ring_buff *b);
int		rgbuf_read_rb(t_ring_buff *b);
void		rgbuf_read_rb_x(t_ring_buff *b, int x);

#endif /* !RINGBUFFER_H */