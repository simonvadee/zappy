/*
** graphic_handle2.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:06:23 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:06:23 2015 Dany Bouca Nova
*/

#include <stdio.h>
#include <stdlib.h>
#include "server.h"

extern t_serv	g_serv;

int		loop_plv(int nb, t_graph *ptr, int i)
{
  t_elem*	tmp;

  tmp = g_serv.players.first;
  while (tmp)
    {
      if (((t_player*)tmp->data)->nb == nb)
	{
	  if (i == 0 && plvg(ptr, tmp->data) == FAIL)
	    return (FAIL);
	  else if (i == 1 && ping(ptr, tmp->data) == FAIL)
	    return (FAIL);
	  return (MATCH);
	}
      tmp = tmp->next;
    }
  return (NONE);
}

int		plvgh(t_graph *ptr, char *s1, char *s2)
{
  int		nb;
  void		*ret;

  (void)s2;
  if (s1 == NULL && sbpg(ptr) == FAIL)
    return (FAIL);
  else
    {
      nb = atoi(s1);
      if ((nb = loop_plv(nb, ptr, 0)) == FAIL)
	return (FAIL);
      if (nb != MATCH && sbpg(ptr) == FAIL)
	return (FAIL);
    }
  ret = pop_first(&ptr->cmd);
  free(ret);
  return (NONE);
}

int		pingh(t_graph* ptr, char *s1, char *s2)
{
  int		nb;
  void		*ret;

  (void)s2;
  if (s1 == NULL)
    sbpg(ptr);
  else
    {
      nb = atoi(s1);
      if ((nb = loop_plv(nb, ptr, 1)) == FAIL)
	return (FAIL);
      if (nb != MATCH && sbpg(ptr) == FAIL)
	return (FAIL);
    }
  ret = pop_first(&ptr->cmd);
  free(ret);
  return (NONE);
}

int	enwgh(t_graph *ptr, char *s1, char *s2)
{
  void	*ret;

  (void)s1;
  (void)s2;
  if (ptr->pos == NULL)
    ptr->pos = g_serv.eggs.first;
  if (ptr->pos != NULL)
    {
      if (enwg(ptr, ptr->pos->data) == FAIL)
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

int	sgtgh(t_graph* ptr, char *s1, char *s2)
{
  void	*ret;

  (void)s1;
  (void)s2;
  if (sgtg(ptr) == FAIL)
    return (FAIL);
  ret = pop_first(&ptr->cmd);
  free(ret);
  return (NONE);
}
