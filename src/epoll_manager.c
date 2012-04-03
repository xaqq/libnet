/*
** epoll_manager.c for  in /home/xaqq/Documents/net
** 
** Made by arnaud kapp
** Login   <kapp_a@epitech.net>
** 
** Started on  Tue Feb 28 11:07:18 2012 arnaud kapp
** Last update Tue Apr  3 11:51:27 2012 arnaud kapp
*/

static int	epoll_fd_manager(int get, int v)
{
  static int	efd = -1;

  if (get)
    return (efd);
  efd = v;
  return (efd);
}

__attribute__((visibility("internal")))
int		get_epoll_fd()
{
  return (epoll_fd_manager(1, 0));
}

__attribute__((visibility("internal")))
int		set_epoll_fd(int v)
{
  return (epoll_fd_manager(0, v));
}

