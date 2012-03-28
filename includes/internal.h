/*
** internal.h for  in /home/xaqq/Documents/net
** 
** Made by arnaud kapp
** Login   <kapp_a@epitech.net>
** 
** Started on  Wed Feb 22 17:13:07 2012 arnaud kapp
** Last update Wed Feb 29 13:38:38 2012 arnaud kapp
*/

#ifndef	INTERNAL_H
#define INTERNAL_H

__attribute__((visibility("internal")))
void		set_flag(int *, int, int);

__attribute__((visibility("internal")))
int		get_flag(int *, int);

/*
** Epoll function
*/
__attribute__((visibility("internal")))
int		get_epoll_fd();

__attribute__((visibility("internal")))
int		set_epoll_fd();

#endif
