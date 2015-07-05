/*
** graphic_handle.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:06:20 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:06:20 2015 Dany Bouca Nova
*/

#include <stdio.h>
#include <stdlib.h>
#include "server.h"

extern t_serv	g_serv;

int		mszgh(t_graph* ptr, char *s1, char *s2)
{
  void		*ret;

  (void)s1;
  (void)s2;
  if (mszg(ptr) == FAIL)
    return (FAIL);
  ret = pop_first(&ptr->cmd);
  free(ret);
  return (NONE);
}

int		bctgh(t_graph* ptr, char *s1, char *s2)
{
  int		x;
  int		y;
  void		*ret;

  if (s1 == NULL || s2 == NULL)
    {
      if (sbpg(ptr) == FAIL)
	return (FAIL);
    }
  else
    {
      x = atoi(s1);
      y = atoi(s2);
      if (x < 0 || x >= g_serv.opt.x || y < 0 || y >=g_serv.opt.y)
	{
	  if (sbpg(ptr) == FAIL)
	    return (FAIL);
	}
      else if (bctg(ptr, x, y) == FAIL)
	return (FAIL);
    }
  ret = pop_first(&ptr->cmd);
  free(ret);
  return (NONE);
}

int		mctgh(t_graph* ptr, char *s1, char *s2)
{
  void		*ret;

  (void)s1;
  (void)s2;
  if (mctg(ptr) == FAIL)
    return (FAIL);
  if (ptr->mct_x == g_serv.opt.x || ptr->mct_y == g_serv.opt.y)
    {
      ptr->mct_x = 0;
      ptr->mct_y = 0;
      ret = pop_first(&ptr->cmd);
      free(ret);
    }
  return (NONE);
}

int		pnwgh(t_graph* ptr, char *s1, char *s2)
{
  void		*ret;

  (void)s1;
  (void)s2;
  if (ptr->pos == NULL)
    ptr->pos = g_serv.players.first;
  if (ptr->pos != NULL)
    {
      if (((t_player*)ptr->pos->data )->state == CONNECTED
	  && pnwg(ptr, ptr->pos->data) == FAIL)
	return (FAIL);
      ptr->pos = ptr->pos->next;
    }
  if (ptr->pos == NULL)
    {
      ret = pop_first(&ptr->cmd);
      free(ret);
    }
  return (NONE);
}
