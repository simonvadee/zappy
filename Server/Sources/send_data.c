/*
** send_data.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:04:21 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:04:22 2015 Dany Bouca Nova
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "server.h"
#include "common.h"

extern t_serv	g_serv;

void		send_to_client(t_player* player)
{
  char		*ptr;

  if (player != NULL)
    {
      ptr = pop_first(&player->send);
      if (ptr != NULL)
	{
	  dprintf(player->fd, "%s\n", ptr);
	  free(ptr);
	}
    }
}

void		send_to_graph(t_graph* graph)
{
  char		*ptr;

  if (graph)
    {
      ptr = pop_first(&graph->send);
      if (ptr != NULL)
	{
	  dprintf(graph->fd, "%s\n", ptr);
	  free(ptr);
	}
    }
}
