/*
** expulse.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:06:36 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:06:37 2015 Dany Bouca Nova
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"
#include "common.h"

extern t_serv	g_serv;

int		get_dir(t_player *p1, t_player *p2)
{
  int		dir[4][4] = {{5, 7, 1, 3},
			     {3, 5, 7, 1},
			     {1, 3, 5, 7},
			     {7, 1, 3, 5}};

  return (dir[p1->direction -1][p2->direction - 1]);
}

void		verif_pos(t_player *player, t_player *main)
{
  int		x[] = {0, 1, 0, -1};
  int		y[] = {-1, 0, 1, 0};

  player->x += x[main->direction - 1];
  player->y += y[main->direction - 1];
  if (player->x < 0)
    player->x = g_serv.opt.x -1;
  else if (player->x >= g_serv.opt.x)
    player->x = 0;
  if (player->y < 0)
    player->y = g_serv.opt.y -1;
  else if (player->y >= g_serv.opt.y)
    player->y = 0;
}

void		move_player(t_player *player)
{
  int		ret;
  char		buff[32];
  t_elem	*ptr;
  t_player	*tmp;

  ptr = g_serv.map[player->y][player->x].players.first;
  while (ptr != NULL)
    {
      tmp = ptr->data;
      ptr = ptr->next;
      if (tmp->nb != player->nb && tmp->x == player->x
	  && tmp->y == player->y && tmp->state == CONNECTED)
	{
	  del_at_data(&g_serv.map[tmp->y][tmp->x].players, tmp);
	  verif_pos(tmp, player);
	  ret = sprintf(buff, "deplacement: %i", get_dir(player, tmp));
	  buff[ret] = 0;
	  if (append(&tmp->send, strdup(buff)) == FAIL
	      || append(&g_serv.map[tmp->y][tmp->x].players, tmp) == FAIL)
	    erase_client(tmp, 1);
	}
    }
}

void		send_graph(t_player *player)
{
  t_elem	*ptr;
  t_elem	*tmp;
  void		*data;

  ptr = g_serv.graphic.first;
  while (ptr != NULL)
    {
      data = ptr->data;
      ptr = ptr->next;
      if (pexg(data, player) == FAIL)
	erase_graphic(data);
      tmp = g_serv.players.first;
      while (tmp != NULL)
	{
	  if (ppog(data, tmp->data) == FAIL)
	    {
	      erase_graphic(data);
	      break ;
	    }
	  tmp = tmp->next;
	}
    }
}

int		expulse(t_player* player, int nb, char *s2)
{
  char		*buff;

  (void)s2;
  if (nb == 0)
    player->time = 7.0f / g_serv.opt.delay;
  else
    {
      if ((buff = malloc(4)) == NULL)
	{
	  erase_client(player, 1);
	  return (FAIL);
	}
      sprintf(buff, "ok");
      if (g_serv.map[player->y][player->x].players.nb_elem == 1)
	sprintf(buff, "ko");
      if (append(&player->send, buff) == FAIL)
	{
	  free(buff);
	  erase_client(player, 1);
	  return (FAIL);
	}
      move_player(player);
      send_graph(player);
    }
  return (NONE);
}
