/*
** list.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:08:23 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:08:24 2015 Dany Bouca Nova
*/

#include <stdlib.h>
#include <string.h>
#include "common.h"

void		init_list(t_list *l)
{
  l->nb_elem = 0;
  l->first = NULL;
  l->last = NULL;
}

int		append(t_list *l, void *data)
{
  t_elem	*new;

  if (!(new = malloc(sizeof(t_elem))))
    return (-1);
  new->data = data;
  new->prev = l->last;
  new->next = NULL;
  if (l->last)
    l->last->next = new;
  else
    l->first = new;
  l->last = new;
  l->nb_elem += 1;
  return (0);
}

int		push(t_list *l, void *data)
{
  t_elem	*new;

  if (!(new = malloc(sizeof(t_elem))))
    return (-1);
  new->data = data;
  new->next = l->first;
  new->prev = NULL;
  if (l->first)
    l->first->prev = new;
  else
    l->last = new;
  l->first = new;
  l->nb_elem += 1;
  return (0);
}

void		*pop_last(t_list *l)
{
  void		*data;
  t_elem	*tmp;

  tmp = l->last;
  if (!tmp)
    return (NULL);
  data = tmp->data;
  l->last = tmp->prev;
  if (l->last)
    l->last->next = NULL;
  else
    l->first = NULL;
  free(tmp);
  l->nb_elem -= 1;
  return (data);
}

void		*pop_first(t_list *l)
{
  void		*data;
  t_elem	*tmp;

  tmp = l->first;
  if (!tmp)
    return (NULL);
  data = tmp->data;
  l->first = tmp->next;
  if (l->first)
    l->first->prev = NULL;
  else
    l->last = NULL;
  free(tmp);
  l->nb_elem -= 1;
  return (data);
}
