/*
** start_server.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:09:06 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:09:07 2015 Dany Bouca Nova
*/

#include <stdio.h>
#include <unistd.h>
#include "server.h"
#include "common.h"

extern t_serv		g_serv;

void			set_graphic_fd()
{
  t_elem		*ptr;

  ptr = g_serv.graphic.first;
  while (ptr != NULL)
    {
      FD_SET(((t_graph*)ptr->data)->fd, &g_serv.readfd);
      if (((t_graph*)ptr->data)->send.nb_elem != 0)
	FD_SET(((t_graph*)ptr->data)->fd, &g_serv.writefd);
      g_serv.maxfd = MAX(((t_graph*)ptr->data)->fd, g_serv.maxfd);
      ptr = ptr->next;
    }
}

void			set_fd(struct timeval *tv)
{
  t_elem		*tmp;
  int			i;

  g_serv.maxfd = g_serv.sock;
  i = (1.0f / g_serv.opt.delay) * 1000000;
  tv->tv_sec = i / 1000000;
  tv->tv_usec = i % 1000000;
  FD_ZERO(&g_serv.readfd);
  FD_ZERO(&g_serv.writefd);
  FD_SET(g_serv.sock, &g_serv.readfd);
  tmp = g_serv.players.first;
  while (tmp != NULL)
    {
      FD_SET(((t_player*)tmp->data)->fd, &g_serv.readfd);
      if (((t_player*)tmp->data)->send.nb_elem != 0)
	FD_SET(((t_player*)tmp->data)->fd, &g_serv.writefd);
      g_serv.maxfd = MAX(((t_player*)tmp->data)->fd, g_serv.maxfd);
      tmp = tmp->next;
    }
  set_graphic_fd();
  g_serv.maxfd += 1;
}

void			check_fd()
{
  t_elem		*ptr;

  if (FD_ISSET(g_serv.sock, &g_serv.readfd))
    new_client();
  ptr = g_serv.graphic.first;
  while (ptr != NULL)
    {
      if (FD_ISSET(((t_graph*)ptr->data)->fd, &g_serv.writefd))
	send_to_graph(ptr->data);
      if (FD_ISSET(((t_graph*)ptr->data)->fd, &g_serv.readfd))
	ptr = handle_graphic(ptr);
      else
	ptr = ptr->next;
    }
  ptr = g_serv.players.first;
  while (ptr != NULL)
    {
      if (FD_ISSET(((t_player*)ptr->data)->fd, &g_serv.writefd))
	send_to_client(ptr->data);
      if (FD_ISSET(((t_player*)ptr->data)->fd, &g_serv.readfd))
	ptr = handle_client(ptr);
      else
	ptr = ptr->next;
    }
}

int			check_team()
{
  t_elem		*ptr;
  char			*team;

  ptr = g_serv.opt.team.first;
  while (ptr)
    {
      if (((t_team*)ptr->data)->nb_lvl_max == 6)
	{
	  team = ((t_team*)ptr->data)->name;
	  ptr = g_serv.graphic.first;
	  while (ptr)
	    {
	      clean(&((t_graph*)ptr->data)->send, 1);
	      segg(ptr->data, team);
	      ptr = ptr->next;
	    }
	  return (MATCH);
	}
      ptr = ptr->next;
    }
  return (NONE);
}

void			start_server()
{
  struct timeval	tv;
  float			time;

  tv.tv_sec = 0;
  tv.tv_usec = 0;
  while (check_team() == 0)
    {
      set_fd(&tv);
      if (select(g_serv.maxfd, &g_serv.readfd, &g_serv.writefd, NULL, &tv)
	  >= 0)
	check_fd();
      else
	break;
      time = (1.0f / g_serv.opt.delay) - (tv.tv_sec + (tv.tv_usec / 1000000.0));
      graphic_cycle();
      cycle_management(time);
    }
  graphic_cycle();
}
