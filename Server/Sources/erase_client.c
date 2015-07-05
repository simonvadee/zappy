/*
** erase_client.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:07:36 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:07:37 2015 Dany Bouca Nova
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "server.h"
#include "common.h"

extern t_serv	g_serv;

void		del_from_team(t_player* player)
{
  t_elem	*ptr;

  ptr = g_serv.opt.team.first;
  while (ptr != NULL)
    {
      if (strcmp(((t_team*)ptr->data)->name, player->team) == 0)
	{
	  if (player->lvl == 8)
	    ((t_team*)ptr->data)->nb_lvl_max -= 1;
	  ((t_team*)ptr->data)->nb_player += 1;
	  break;
	}
      ptr = ptr->next;
    }
  del_at_data(&g_serv.map[player->y][player->x].players, player);
}

void		erase_client2(t_player *player, int i)
{
  if (i == 1)
    {
      close(player->fd);
      printf("*** Attempting to delete player %i\n", player->nb);
      printf("*** Deleting player %i\n", player->nb);
    }
}

void		erase_client(t_player *player, int i)
{
  t_elem	*ptr;

  player = del_at_data(&g_serv.players, player);
  clean(&player->cmd, 1);
  clean(&player->send, 1);
  if (player->state == CONNECTED)
    {
      if (player->food <= 0.0000f)
	write(player->fd, "mort\n", 5);
      close(player->fd);
      ptr = g_serv.graphic.first;
      while (ptr != NULL)
	{
	  pdig(ptr->data, player);
	  ptr = ptr->next;
	}
      del_from_team(player);
    }
  erase_client2(player, i);
  free(player);
  player = NULL;
}

void		erase_graphic(t_graph *ptr)
{
  printf("*** Attempting to delete player %i\n", ptr->nb);
  printf("*** Deleting player %i\n", ptr->nb);
  ptr = del_at_data(&g_serv.graphic, ptr);
  close(ptr->fd);
  clean(&ptr->cmd, 1);
  clean(&ptr->send, 1);
  free(ptr);
  ptr = NULL;
}
