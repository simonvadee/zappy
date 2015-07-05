/*
** incantation2.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:05:59 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:06:00 2015 Dany Bouca Nova
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"
#include "common.h"

extern t_serv	g_serv;

int		start_inc(t_player *player, char buff[])
{
  t_elem	*ptr;

  ptr = g_serv.map[player->y][player->x].players.first;
  while (ptr != NULL)
    {
      if (((t_player*)ptr->data)->state == CONNECTED
	  && ((t_player*)ptr->data)->x == player->x
	  && ((t_player*)ptr->data)->y == player->y
	  && ((t_player*)ptr->data)->lvl == player->lvl
	  && append(&((t_player*)ptr->data)->send, strdup(buff)) == FAIL)
	return (FAIL);
      ptr = ptr->next;
    }
  return (NONE);
}

int		start_incantation(t_player *player)
{
  char		buff[32];
  t_elem	*ptr;

  player->time = 300.0f / g_serv.opt.delay;
  sprintf(buff, "elevation en cours");
  if (start_inc(player, buff) == FAIL)
    return (FAIL);
  ptr = g_serv.graphic.first;
  while (ptr != NULL)
    {
      if (picg(ptr->data, player) == FAIL)
	return (FAIL);
      ptr = ptr->next;
    }
  return (NONE);
}

int		end_inc(t_player *player, int lvl, char buff[])
{
  t_elem	*ptr;

  ptr = g_serv.map[player->y][player->x].players.first;
  while (ptr != NULL)
    {
      if (((t_player*)ptr->data)->lvl == lvl
	  && ((t_player*)ptr->data)->state == CONNECTED)
	{
	  ((t_player*)ptr->data)->lvl += 1;
	  if (((t_player*)ptr->data)->lvl == 8)
	    inc_lvl_team(ptr->data);
	  if (append(&((t_player*)ptr->data)->send, strdup(buff)) == FAIL)
	    return (FAIL);
	}
      ptr = ptr->next;
    }
  return (NONE);
}

int		end_incantation(t_player *player, int state, int lvl)
{
  char		buff[32];

  if (state == 0)
    sprintf(buff, "ko");
  else
    {
      lvl = player->lvl;
      sprintf(buff, "niveau actuel : %i", player->lvl + 1);
      return (end_inc(player, lvl, buff));
    }
  return (NONE);
}
