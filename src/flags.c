/*
** flags.c for  in /home/xaqq/Documents/net
** 
** Made by arnaud kapp
** Login   <kapp_a@epitech.net>
** 
** Started on  Wed Feb 22 17:12:13 2012 arnaud kapp
** Last update Tue Feb 28 11:08:07 2012 arnaud kapp
*/

#include "internal.h"

__attribute__((visibility("internal")))
int		get_flag(int *bf, int f)
{
  return ((*bf & f) == 0 ? 0 : 1);
}

__attribute__((visibility("internal")))
void	set_flag(int *bf, int f, int v)
{
  if (v)
    *bf |= f;
  else
    *bf &= ~f;
}
