/*
** broadcasts.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:08:58 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:08:59 2015 Dany Bouca Nova
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

extern t_serv	g_serv;

void		send_msg(t_player *speaker, char *msg)
{
  t_elem	*tmp;
  char		*buff;

  tmp = g_serv.players.first;
  while (tmp != NULL)
    {
      if (((t_player *)tmp->data)->nb != speaker->nb
	  && ((t_player *)tmp->data)->state == CONNECTED
	  && (buff = malloc(32 + strlen(msg))) != NULL)
	{
	  sprintf(buff, "message %d,%s",
		  direction_player(speaker, tmp->data), msg);
	  if (append(&((t_player*)tmp->data)->send, buff) == FAIL)
	    free (buff);
	}
      tmp = tmp->next;
    }
}

int		broadcasts(t_player *speaker, int nb, char *msg)
{
  if (msg == NULL)
    {
      if (append(&speaker->send, strdup("ko")) == FAIL)
	erase_client(speaker, 1);
      return (FAIL);
    }
  if (nb == 0)
    speaker->time = 7.0f / g_serv.opt.delay;
  else
    {
      send_msg(speaker, msg);
      if (append(&speaker->send, strdup("ok")) == FAIL)
	{
	  erase_client(speaker, 1);
	  return (FAIL);
	}
      broadcast_graphic(speaker, msg);
    }
  return (NONE);
}
