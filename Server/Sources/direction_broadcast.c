/*
** direction_broadcast.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:06:39 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:06:40 2015 Dany Bouca Nova
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

extern t_serv		g_serv;

int			direction_horizontal(t_player *speaker,
					     t_player *listener)
{
  int			tmp;
  int			c;
  e_direction		dir[4];
  int			left[4];
  int			right[4];

  c = 0;
  tmp = calculate(speaker->x, listener->x, g_serv.opt.x);
  direction_tab(dir);
  horizontal_tab(left, right);
  while (listener->direction != dir[c])
    ++c;
  if (tmp < 0)
    return (left[c]);
  if (tmp > 0)
    return (right[c]);
  return (0);
}

int			direction_vertical(t_player *speaker,
					   t_player *listener)
{
  int			tmp;
  int			c;
  e_direction		dir[4];
  int			up[4];
  int			down[4];

  c = 0;
  tmp = calculate(speaker->y, listener->y, g_serv.opt.y);
  direction_tab(dir);
  vertical_tab(up, down);
  while (listener->direction != dir[c])
    ++c;
  if (tmp < 0)
    return (up[c]);
  if (tmp > 0)
    return (down[c]);
  return (0);
}

int			direction_diagonal(t_player *speaker,
					   t_player *listener)
{
  int			x;
  int			y;
  int			c;
  e_direction		dir[4];
  int			tab[4];

  c = 0;
  x = calculate(speaker->x, listener->x, g_serv.opt.x);
  y = calculate(speaker->y, listener->y, g_serv.opt.y);
  direction_tab(dir);
  while (listener->direction != dir[c])
    ++c;
  no_tab(tab);
  if (x < 0 && y < 0)
    return (tab[c]);
  ne_tab(tab);
  if (x > 0 && y < 0)
    return (tab[c]);
  so_tab(tab);
  if (x < 0 && y > 0)
    return (tab[c]);
  se_tab(tab);
  if (x > 0 && y > 0)
    return (tab[c]);
  return (0);
}

int			direction_player(t_player *speaker,
					 t_player *listener)
{
  if (speaker->x == listener->x &&
      speaker->y == listener->y)
    return (0);
  if (speaker->y == listener->y)
    return (direction_horizontal(speaker, listener));
  if (speaker->x == listener->x)
    return (direction_vertical(speaker, listener));
  return (direction_diagonal(speaker, listener));
}
