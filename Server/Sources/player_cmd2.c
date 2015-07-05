/*
** player_cmd2.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:08:31 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:08:31 2015 Dany Bouca Nova
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"
#include "common.h"

extern t_serv	g_serv;

static char	*obj[] = {"nourriture", "linemate", "deraumere", "sibur",
			  "mendiane", "phiras", "thystame", NULL};

int		send_prend(t_player *player, char **buff, int i, int j)
{
  t_elem	*ptr;
  void		*data;

  if (append(&player->send, *buff) == FAIL)
    {
      free(buff);
      erase_client(player, 1);
      return (FAIL);
    }
  ptr = g_serv.graphic.first;
  while (ptr != NULL)
    {
      data = ptr->data;
      ptr = ptr->next;
      if (j == 0 && pgtg(data, player, i) == FAIL)
	erase_graphic(data);
      else if (j != 0 && pdrg(data, player, i) == FAIL)
	erase_graphic(data);
      if (data && (ping(data, player) == FAIL
		   || bctg(data, player->x, player->y) == FAIL))
	erase_graphic(data);
    }
  return (NONE);
}

void		change_ressource(int nb, t_player *player, char **buff, int i)
{
  if (i == 0)
    {
      if (nb == FOOD)
	{
	  player->food += 126.0f / g_serv.opt.delay;
	  g_serv.map[random() % g_serv.opt.y]
	    [random() % g_serv.opt.x].obj[0] += 1;
	}
      else
	player->obj[nb - 1] += 1;
      g_serv.map[player->y][player->x].obj[nb] -= 1;
    }
  else
    {
      if (nb == FOOD)
	player->food -= 126.0f / g_serv.opt.delay;
      else if (player->obj[nb - 1] > 0)
	player->obj[nb - 1] -= 1;
      g_serv.map[player->y][player->x].obj[nb] += 1;
    }
  sprintf(*buff, "ok");
}

int		prend(t_player *player, int nb, char *s2)
{
  char		*buff;

  if (nb == 0)
    player->time = 7.0f / g_serv.opt.delay;
  else
    {
      nb = -1;
      if ((buff = malloc(4)) == NULL)
	erase_client(player, 1);
      else
	{
	  while (s2 != NULL && obj[++nb] != NULL && strcmp(s2, obj[nb]) != 0);
	  if (obj[nb] != NULL && g_serv.map[player->y][player->x].obj[nb] > 0)
	    change_ressource(nb, player, &buff, 0);
	  else
	    {
	      nb = -1;
	      sprintf(buff, "ko");
	    }
	  return (send_prend(player, &buff, nb, 0));
	}
    }
  return (NONE);
}

int		pose(t_player *player, int nb, char *s2)
{
  char		*buff;

  if (nb == 0)
    player->time = 7.0f / g_serv.opt.delay;
  else
    {
      nb = -1;
      if ((buff = malloc(4)) == NULL)
	{
	  erase_client(player, 1);
	  return (FAIL);
	}
      while (s2 != NULL && obj[++nb] != NULL && strcmp(s2, obj[nb]) != 0);
      if (nb == 0)
	change_ressource(nb, player, &buff, 1);
      else if (obj[nb] != NULL && player->obj[nb - 1] > 0)
	change_ressource(nb, player, &buff, 1);
      else
	{
	  nb = -1;
	  sprintf(buff, "ko");
	}
      return (send_prend(player, &buff, nb, 1));
    }
  return (NONE);
}
