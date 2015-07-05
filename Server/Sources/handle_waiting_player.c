/*
** handle_waiting_player.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:08:07 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:08:08 2015 Dany Bouca Nova
*/

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "server.h"
#include "common.h"

extern t_serv	g_serv;

void		get_team(t_player *player)
{
  t_elem	*tmp;

  if (strcmp("GRAPHIC", player->team) == 0)
    connect_graphic(player);
  else
    {
      tmp = g_serv.opt.team.first;
      while (tmp != NULL)
	{
	  if (strcmp(((t_team*)tmp->data)->name, player->team) == 0)
	    {
	      if (((t_team*)tmp->data)->nb_player > 0)
		return (connect_client(player, (t_team*)tmp->data));
	      break;
	    }
	  tmp = tmp->next;
	}
      write(player->fd, "ko\n", 3);
      close(player->fd);
      erase_client(player, 1);
    }
}

void		handle_waiting_player(t_player *player, char buff[])
{
  int		len;

  if (player->team == NULL)
    len = 0;
  else
    len = strlen(player->team);
  if ((player->team = realloc(player->team, len + 256)) == NULL)
    {
      my_perror("Error malloc :");
      erase_client(player, 1);
      return;
    }
  player->team[len] = 0;
  strcat(player->team, buff);
  len = -1;
  while (player->team[++len])
    {
      if (player->team[len] == '\n')
	{
	  player->team[len] = 0;
	  get_team(player);
	  break;
	}
    }
}
