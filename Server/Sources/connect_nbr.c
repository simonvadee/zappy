/*
** connect_nbr.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:06:46 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:06:46 2015 Dany Bouca Nova
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"
#include "common.h"

extern t_serv	g_serv;

int		connect_nbr(t_player *player, int nb, char *s2)
{
  char		*buff;
  t_elem	*ptr;

  (void)nb;
  (void)s2;
  player->time = -1;
  if ((buff = malloc(8)) == NULL)
    {
      erase_client(player, 1);
      return (FAIL);
    }
  ptr = g_serv.opt.team.first;
  while (ptr != NULL)
    {
      if (strcmp(((t_team*)ptr->data)->name, player->team) == 0)
	{
	  sprintf(buff, "%i", ((t_team*)ptr->data)->nb_player);
	  break ;
	}
      ptr = ptr->next;
    }
  if (append(&player->send, buff) == FAIL)
    erase_client(player, 1);
  return (NONE);
}
