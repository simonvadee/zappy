/*
** forkp.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:07:39 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:07:39 2015 Dany Bouca Nova
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"
#include "common.h"

extern t_serv	g_serv;

int		conf_egg(t_egg *egg, t_player *player)
{

  egg->nb = g_serv.opt.number_of_client;
  egg->father = player->nb;
  egg->x = player->x;
  egg->y = player->y;
  egg->state = EGG;
  egg->time = 600.0f / g_serv.opt.delay;
  egg->team = player->team;
  if (append(&g_serv.eggs, egg) == FAIL)
    {
      free(egg);
      erase_client(player, 1);
      return (FAIL);
    }
  return (NONE);
}

t_egg		*create_egg(t_player *player)
{
  char		*buff;
  t_egg		*egg;

  if ((egg = malloc(sizeof(t_egg))) == NULL)
    return (NULL);
  if ((buff = malloc(4)) == NULL)
    {
      free(egg);
      return (NULL);
    }
  ++g_serv.opt.number_of_client;
  if (conf_egg(egg, player) == FAIL)
    return (NULL);
  sprintf(buff, "ok");
  if (append(&g_serv.map[egg->y][egg->x].eggs, egg) == FAIL
      || append(&player->send, buff) == FAIL)
    {
      destroy_egg(egg);
      erase_client(player, 1);
      return (NULL);
    }
  return (egg);
}

void		fork2(t_player *player)
{
  t_egg		*egg;
  t_elem	*graph;
  void		*data;

  egg = create_egg(player);
  graph = g_serv.graphic.first;
  while (egg != NULL && graph != NULL)
    {
      data = graph->data;
      graph = graph->next;
      if (enwg(data, egg) == FAIL)
	erase_graphic(data);
    }
}

int		forkp(t_player *player, int nb, char *s2)
{
  t_elem	*graph;
  void		*data;

  (void)s2;
  graph = g_serv.graphic.first;
  if (nb == 0)
    {
      player->time = 42.0f / g_serv.opt.delay;
      while (graph != NULL)
	{
	  data = graph->data;
	  graph = graph->next;
	  if (pfkg(data, player) == FAIL)
	    erase_graphic(data);
	}
    }
  else
    fork2(player);
  return (NONE);
}
