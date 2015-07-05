/*
** inventaire.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:08:19 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:08:19 2015 Dany Bouca Nova
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"
#include "common.h"

extern t_serv	g_serv;

int		inventaire(t_player *player, int nb, char *s2)
{
  char		*buff;

  (void)s2;
  if (nb == 0)
    player->time = 1.0f / g_serv.opt.delay;
  else
    {
      if ((buff = malloc(128)) == NULL)
	{
	  erase_client(player, 1);
	  return (FAIL);
	}
      sprintf(buff, "{nourriture %i,linemate %i,deraumere %i,sibur %i,\
mendiane %i,phiras %i,thystame %i}", (int)((player->food * g_serv.opt.delay)
					   / 126),
	      player->obj[0], player->obj[1], player->obj[2],
	      player->obj[3], player->obj[4], player->obj[5]);
      if (append(&player->send, buff) == FAIL)
	erase_client(player, 1);
    }
  return (NONE);
}
