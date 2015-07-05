/*
** cycle.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:07:33 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:07:34 2015 Dany Bouca Nova
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "server.h"
#include "common.h"

extern t_serv	g_serv;

void		destroy_egg(t_egg *egg)
{
  t_elem	*tmp;
  void		*data;

  tmp = g_serv.opt.team.first;
  while (tmp)
    {
      if (strcmp(((t_team*)tmp->data)->name, egg->team) == 0)
	((t_team*)tmp->data)->nb_player -= 1;
      tmp = tmp->next;
    }
  tmp = g_serv.graphic.first;
  while (tmp != NULL)
    {
      data = tmp->data;
      tmp = tmp->next;
      if (edig(data, egg) == FAIL)
	erase_graphic(data);
    }
  del_at_data(&g_serv.map[egg->y][egg->x].eggs, egg);
  del_at_data(&g_serv.eggs, egg);
  free(egg);
}

void		egg_clot(t_egg *egg)
{
    t_elem	*ptr;

  ptr = g_serv.opt.team.first;
  while (ptr)
    {
      if (strcmp(((t_team*)ptr->data)->name, egg->team) == 0)
	((t_team*)ptr->data)->nb_player += 1;
      ptr = ptr->next;
    }
}

void		*manage_egg(t_elem* ptr, float time)
{
  t_elem	*tmp;
  t_egg		*egg;
  void		*data;

  egg = ptr->data;
  ptr = ptr->next;
  egg->time -= time;
  if (egg->time <= 0.0000 && egg->state == EGG)
    {
      egg->state = WAITING;
      egg->time = 1260.0f * (1.0f / g_serv.opt.delay);
      egg_clot(egg);
      tmp = g_serv.graphic.first;
      while (tmp != NULL)
	{
	  data = tmp->data;
	  tmp = tmp->next;
	  if (ehtg(data, egg) == FAIL)
	    erase_graphic(data);
	}
    }
  else if (egg->time <= 0.0000)
    destroy_egg(egg);
  return (ptr);
}

void		*manage_waiting_player(t_elem *ptr, float time)
{
  t_player	*player;

  player = ptr->data;
  ptr = ptr->next;
  player->time -= time;
  if (player->time <= 0.0000)
    {
      close(player->fd);
      erase_client(player, 1);
    }
  return (ptr);
}

void		cycle_management(float time)
{
  t_elem	*tmp;

  tmp = g_serv.eggs.first;
  while (tmp)
    tmp = manage_egg(tmp, time);
  tmp = g_serv.players.first;
  while (tmp)
    {
      if (((t_player*)tmp->data)->state == WAITING)
	tmp = manage_waiting_player(tmp, time);
      else
	tmp = manage_player(tmp, time);
    }
}
