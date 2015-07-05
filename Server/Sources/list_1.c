/*
** list_1.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:05:40 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:05:41 2015 Dany Bouca Nova
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "common.h"

void		aff_list(t_list *list)
{
  t_elem	*tmp;

  tmp = list->first;
  while (tmp != NULL)
    {
      write(STDOUT_FILENO, tmp->data, strlen(tmp->data));
      write(STDOUT_FILENO, "\n", 1);
      tmp = tmp->next;
    }
}

void		*del_at_data(t_list *l, void *data)
{
  t_elem	*tmp;
  void		*value;

  tmp = l->first;
  if (!tmp)
    return (NULL);
  if (l->first->data == data)
    return (pop_first(l));
  if (l->last->data == data)
    return (pop_last(l));
  while (tmp && tmp->data != data)
    tmp = tmp->next;
  if (tmp == NULL)
    return (NULL);
  value = tmp->data;
  tmp->prev->next = tmp->next;
  tmp->next->prev = tmp->prev;
  free(tmp);
  l->nb_elem -= 1;
  return (value);
}

void		*del_at_pos(t_list *l, unsigned int pos)
{
  t_elem	*tmp;
  void		*value;
  unsigned int	i;

  i = 0;
  tmp = l->first;
  if (!tmp)
    return (NULL);
  if (pos == 0)
    return (pop_first(l));
  if (pos == l->nb_elem)
    return (pop_last(l));
  while (i != pos)
    {
      tmp = tmp->next;
      ++i;
    }
  value = tmp->data;
  tmp->prev->next = tmp->next;
  tmp->next->prev = tmp->prev;
  free(tmp);
  l->nb_elem -= 1;
  return (value);
}

void		clean(t_list *l, int erase)
{
  void		*tmp;

  while ((tmp = pop_first(l)) != NULL)
    {
      if (erase == 1)
	free(tmp);
    }
}
