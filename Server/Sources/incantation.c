/*
** incantation.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:08:11 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:08:12 2015 Dany Bouca Nova
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"
#include "common.h"

extern t_serv	g_serv;

void		inc_lvl_team(t_player *player)
{
  t_elem	*ptr;

  ptr = g_serv.opt.team.first;
  while (ptr != NULL)
    {
      if (strcmp(((t_team*)ptr->data)->name, player->team) == 0)
	{
	  ((t_team*)ptr->data)->nb_lvl_max += 1;
	  break;
	}
      ptr = ptr->next;
    }
}

int		end_inc_graph(t_player* player, int end)
{
  t_elem	*graph;
  t_elem	*tmp;

  graph = g_serv.graphic.first;
  while (graph != NULL)
    {
      if (pieg(graph->data, player, end) == FAIL)
	return (FAIL);
      tmp = g_serv.map[player->y][player->x].players.first;
      while (tmp != NULL)
	{
	  if (((t_player*)tmp->data)->lvl == player->lvl
	      && plvg(graph->data, tmp->data) == FAIL)
	    return (FAIL);
	  tmp = tmp->next;
	}
      if (bctg(graph->data, player->x, player->y) == FAIL)
	return (FAIL);
      graph = graph->next;
    }
  return (NONE);
}

int		incantation(t_player* player, int nb, char *s2)
{
  int		i;

  (void)s2;
  if (player->lvl == 8 || (i = check_incantation(player) == -1))
    {
      send_ko(player);
      player->time = -1;
      if (end_incantation(player, 0, 0) == FAIL)
	erase_client(player, 1);
      return (FAIL);
    }
  if (nb == 0 && start_incantation(player) == FAIL)
    erase_client(player, 1);
  else if (nb != 0 && player->time <= 0)
    {
      if (end_incantation(player, 1, 0) == FAIL
	  || manage_ressource(player) == FAIL
	  || end_inc_graph(player, 1) == FAIL)
	erase_client(player, 1);
    }
  return (NONE);
}
