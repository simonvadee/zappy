/*
** handle_graphic.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:07:59 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:08:00 2015 Dany Bouca Nova
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

extern t_serv	g_serv;

void		handle_graphic2(t_graph* ptr, int len, char (*tmp)[])
{
  char		*buff;

  strcpy(ptr->buff + len, *tmp);
  while (ptr->buff && strchr(ptr->buff, '\n'))
    {
      buff = strtok(ptr->buff, "\n");
      if (buff != NULL && (buff = strdup(buff)) == NULL)
	return;
      if (append(&ptr->cmd, buff) == FAIL)
	{
	  erase_graphic(ptr);
	  return;
	}
      buff = strtok(NULL, "");
      if (buff != NULL && (buff = strdup(buff)) == NULL)
	return;
      free(ptr->buff);
      ptr->buff = buff;
    }
}

void		*handle_graphic(t_elem* ptr)
{
  int		len;
  char		tmp[256];
  t_graph	*data;

  data = ptr->data;
  ptr = ptr->next;
  if ((len = read(data->fd, tmp, 255)) <= 0)
    erase_graphic(data);
  else
    {
      tmp[len] = 0;
      if (data->buff == NULL)
	len = 0;
      else
	len = strlen(data->buff);
      if ((data->buff = realloc(data->buff, 256 + len)) == NULL)
	erase_graphic(data);
      else
	handle_graphic2(data, len, &tmp);
    }
  return (ptr);
}
