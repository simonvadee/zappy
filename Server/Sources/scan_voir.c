/*
** scan_voir.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:08:38 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:08:39 2015 Dany Bouca Nova
*/

#include <stdio.h>
#include "server.h"

extern t_serv		g_serv;

void			add_scan_n(int *x, int *y, int c, t_player *player)
{
  if (player->x - c < 0)
    {
      if ((*x = ((player->x - c) % g_serv.opt.x) + g_serv.opt.x)
	  == g_serv.opt.x)
	*x = 0;
    }
  else
    *x = player->x - c;
  if (player->y - c < 0)
    {
      if ((*y = ((player->y - c) % g_serv.opt.y) + g_serv.opt.y)
	  == g_serv.opt.y)
	*y = 0;
    }
  else
    *y = player->y - c;

}

int			scan_n(t_player *player, int c, char **buff)
{
  int			x;
  int			y;
  int			i;

  add_scan_n(&x, &y, c, player);
  i = c * 2 + 1;
  while (i > 0)
    {
      if (add_to_buff(",", buff) == FAIL || add_coord(x, y, buff) == FAIL)
	return (FAIL);
      ++x;
      if (x >= g_serv.opt.x)
	x = 0;
      --i;
    }
  return (NONE);
}

int			scan_s(t_player *player, int c, char **buff)
{
  int			x;
  int			y;
  int			i;

  x = (player->x + c) % g_serv.opt.x;
  y = (player->y + c) % g_serv.opt.y;
  i = c * 2 + 1;
  while (i > 0)
    {
      if (add_to_buff(",", buff) == FAIL || add_coord(x, y, buff) == FAIL)
	return (FAIL);
      --x;
      if (x < 0)
	if ((x = (x % g_serv.opt.x) + g_serv.opt.x)
	    == g_serv.opt.x)
	  x = 0;
      --i;
    }
  return (NONE);
}

int			scan_o(t_player *player, int c, char **buff)
{
  int			x;
  int			y;
  int			i;

  if (player->x - c < 0)
    {
      if ((x = ((player->x - c) % g_serv.opt.x) + g_serv.opt.x)
	  == g_serv.opt.x)
	x = 0;
    }
  else
    x = player->x - c;
  y = (player->y + c) % g_serv.opt.y;
  i = c * 2 + 1;
  while (i > 0)
    {
      if (add_to_buff(",", buff) == FAIL || add_coord(x, y, buff) == FAIL)
	return (FAIL);
      --y;
      if (y < 0 && (y = (y % g_serv.opt.y) + g_serv.opt.y) == g_serv.opt.y)
	y = 0;
      --i;
    }
  return (NONE);
}

int			scan_e(t_player *player, int c, char **buff)
{
  int			x;
  int			y;
  int			i;

  x = (player->x + c) % g_serv.opt.x;
  if (player->y - c < 0)
    {
      if ((y = ((player->y - c) % g_serv.opt.y) + g_serv.opt.y)
	  == g_serv.opt.y)
	y = 0;
    }
  else
    y = player->y - c;
  i = c * 2 + 1;
  while (i > 0)
    {
      if (add_to_buff(",", buff) == FAIL || add_coord(x, y, buff) == FAIL)
	return (FAIL);
      ++y;
      if (y >= g_serv.opt.y)
	y = 0;
      --i;
    }
  return (NONE);
}
