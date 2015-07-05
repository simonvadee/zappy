/*
** graphic_handle3.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:07:45 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:21:55 2015 Dany Bouca Nova
*/

#include <stdio.h>
#include <stdlib.h>
#include "server.h"

extern t_serv	g_serv;

int		loop_ppo(int nb, t_graph *ptr)
{
  t_elem*	tmp;

  tmp = g_serv.players.first;
  while (tmp)
    {
      if (((t_player*)tmp->data)->nb == nb)
	{
	  if (ppog(ptr, tmp->data) == FAIL)
	    return (FAIL);
	  return (MATCH);
	}
      tmp = tmp->next;
    }
  return (NONE);
}

int		ppogh(t_graph* ptr, char *s1, char *s2)
{
  int		nb;
  void		*ret;

  (void)s2;
  if (s1 == NULL && sbpg(ptr) == FAIL)
    return (FAIL);
  else if (s1 != NULL)
    {
      nb = atoi(s1);
      if ((nb = loop_ppo(nb, ptr)) == FAIL)
	  return (FAIL);
      if (nb != MATCH && sbpg(ptr) == FAIL)
	return (FAIL);
    }
  ret = pop_first(&ptr->cmd);
  free(ret);
  return (NONE);
}

int		sstgh(t_graph* ptr, char *s1, char *s2)
{
  int		delay;
  void		*ret;

  (void)s2;
  if (s1 == NULL && sbpg(ptr) == FAIL)
    return (FAIL);
  else if (s1 != NULL)
    {
      delay = atoi(s1);
      if (delay > 0 && delay < 1000000)
	g_serv.opt.delay = delay;
      if (sgtg(ptr) == FAIL)
	return (FAIL);
    }
  ret = pop_first(&ptr->cmd);
  free(ret);
  return (NONE);
}
