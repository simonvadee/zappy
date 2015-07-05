/*
** graphic_response2.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:07:49 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:07:50 2015 Dany Bouca Nova
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "server.h"

extern t_serv	g_serv;

int		ppog(t_graph *ptr, t_player *player)
{
  char		buff[256];

  sprintf(buff, "ppo %i %i %i %i", player->nb, player->x, player->y,
	  player->direction);
  return (append(&ptr->send, strdup(buff)));
}

int		plvg(t_graph* ptr, t_player *player)
{
  char		buff[256];

  sprintf(buff, "plv %i %i", player->nb, player->lvl);
  return (append(&ptr->send, strdup(buff)));
}

int		ping(t_graph* ptr, t_player *player)
{
  char		buff[256];

  sprintf(buff, "pin %i %i %i %i %i %i %i %i %i %i", player->nb,
	  player->x, player->y, (int)((player->food * g_serv.opt.delay)
				      / 126.0f),
	  player->obj[0], player->obj[1], player->obj[2], player->obj[3],
	  player->obj[4], player->obj[5]);
  return (append(&ptr->send, strdup(buff)));
}

int		pexg(t_graph* ptr, t_player *player)
{
  char		buff[256];

  sprintf(buff, "pex %i", player->nb);
  return (append(&ptr->send, strdup(buff)));
}

int		pbcg(t_graph *ptr, t_player *player, char *msg)
{
  char		*buff;

  if ((buff = malloc(strlen(msg) + 16)) == NULL)
    return (FAIL);
  sprintf(buff, "pbc %i %s", player->nb, msg);
  if (append(&ptr->send, buff) == FAIL)
    {
      free(buff);
      return (FAIL);
    }
  return (NONE);
}
