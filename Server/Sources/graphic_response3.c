/*
** graphic_response3.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:06:16 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:06:17 2015 Dany Bouca Nova
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "server.h"

extern t_serv	g_serv;

int		picg(t_graph* ptr, t_player *player)
{
  char		*buff;
  t_elem	*tmp;

  if ((buff = malloc(4096)) == NULL)
    return (FAIL);
  sprintf(buff, "pic %i %i %i %i", player->x, player->y,
	  player->lvl, player->nb);
  tmp = g_serv.players.first;
  while (tmp != NULL)
    {
      if (((t_player*)tmp->data)->state == CONNECTED
	  && ((t_player*)tmp->data)->nb != player->nb
	  && ((t_player*)tmp->data)->x == player->x
	  && ((t_player*)tmp->data)->y == player->y
	  && ((t_player*)tmp->data)->lvl == player->lvl)
	sprintf(buff, " %i", ((t_player*)tmp->data)->nb);
      tmp = tmp->next;
    }
  if (append(&ptr->send, buff) == FAIL)
    {
      free(buff);
      return (FAIL);
    }
  return (NONE);
}

int		pieg(t_graph* ptr, t_player *player, int result)
{
  char		buff[256];

  sprintf(buff, "pie %i %i %i", player->x, player->y, result);
  return (append(&ptr->send, strdup(buff)));
}

int		pfkg(t_graph* ptr, t_player *player)
{
  char		buff[256];

  sprintf(buff, "pfk %i", player->nb);
  return (append(&ptr->send, strdup(buff)));
}

int		pdrg(t_graph* ptr, t_player *player, eObjet objet)
{
  char		buff[256];

  sprintf(buff, "pdr %i %i", player->nb, objet);
  return (append(&ptr->send, strdup(buff)));
}

int		pgtg(t_graph* ptr, t_player* player, eObjet objet)
{
  char		buff[256];

  sprintf(buff, "pgt %i %i", player->nb, objet);
  return (append(&ptr->send, strdup(buff)));
}
