/*
** player_cmd.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:04:25 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:04:26 2015 Dany Bouca Nova
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "server.h"
#include "common.h"

extern t_serv	g_serv;

int		dir_rep(t_player *player)
{
  char		*buff;
  t_elem	*ptr;
  void		*data;

  if ((buff = malloc(4)) == NULL)
    return (FAIL);
  sprintf(buff, "ok");
  if (append(&player->send, buff) == FAIL)
    {
      free(buff);
      return (FAIL);
    }
  ptr = g_serv.graphic.first;
  while (ptr != NULL)
    {
      data = ptr->data;
      ptr = ptr->next;
      if (ppog(data, player) == FAIL)
	erase_graphic(data);
    }
  return (NONE);
}

int		avance(t_player *player, int nb, char *s2)
{
  int		x[4] = {0, 1, 0, -1};
  int		y[4] = {-1, 0, 1, 0};

  (void)s2;
  if (nb == 0)
    player->time = 7.0f / g_serv.opt.delay;
  else
    {
      del_at_data(&g_serv.map[player->y][player->x].players, player);
      player->x += x[player->direction - 1];
      if (player->x < 0)
	player->x = g_serv.opt.x - 1;
      else if (player->x >= g_serv.opt.x)
	player->x = 0;
      player->y += y[player->direction - 1];
      if (player->y < 0)
	player->y = g_serv.opt.y - 1;
      else if (player->y >= g_serv.opt.y)
	player->y = 0;
      if (dir_rep(player) == FAIL ||
	  append(&g_serv.map[player->y][player->x].players, player) == FAIL)
	erase_client(player, 1);
    }
  return (NONE);
}

int		droite(t_player *player, int nb, char *s2)
{
  (void)s2;
  if (nb == 0)
    player->time = 7.0f / g_serv.opt.delay;
  else
    {
      if (player->direction == O)
	player->direction = N;
      else
	player->direction += 1;
      if (dir_rep(player) == FAIL)
	erase_client(player, 1);
    }
  return (NONE);
}

int		gauche(t_player *player, int nb, char *s2)
{
  (void)s2;
  if (nb == 0)
    player->time = 7.0f / g_serv.opt.delay;
  else
    {
      if (player->direction == N)
	player->direction = O;
      else
	player->direction -= 1;
      if (dir_rep(player) == FAIL)
	erase_client(player, 1);
    }
  return (NONE);
}
