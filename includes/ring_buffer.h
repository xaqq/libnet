/*
** ring_buffer.h for  in /home/xaqq/Documents/net
**
** Made by arnaud kapp
** Login   <kapp_a@epitech.net>
**
** Started on  Wed Feb 22 21:32:42 2012 arnaud kapp
** Last update Wed Apr 18 18:46:07 2012 arnaud kapp
*/

#ifndef	RINGBUFFER_H
# define RINGBUFFER_H

# define	RGBUF_SIZE	262144

typedef struct	s_ring_buff
{
  unsigned char	*data;
  int		size;
  int		s; //start
  int		e; //end
  int		last_start;
}		t_ring_buff;

typedef t_ring_buff t_ring_buff;

t_ring_buff	*rgbuf_create(int s);
void		rgbuf_delete(t_ring_buff *b);
int		rgbuf_is_empty(t_ring_buff *b);
int		rgbuf_is_full(t_ring_buff *b);
int		rgbuf_write(t_ring_buff *b, unsigned char *d, int s);
int		rgbuf_read(t_ring_buff *b, unsigned char *d, int s);
int		rgbuf_r_available(t_ring_buff *b);
int		rgbuf_w_available(t_ring_buff *b);
int		rgbuf_read_rb(t_ring_buff *b);

#endif /* !RINGBUFFER_H */
