/*
** handle_client.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:06:10 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:06:10 2015 Dany Bouca Nova
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "server.h"
#include "common.h"

extern t_serv	g_serv;

int		handle_player2(t_player *player, char **tmp)
{
  char		*s;

  s = strtok(player->cmd_buff, "\n");
  if (s != NULL && (s = strdup(s)) == NULL)
    return (FAIL);
  if (append(&player->cmd, s) == FAIL)
    {
      erase_client(player, 1);
      return (FAIL);
    }
  *tmp = strtok(NULL, "");
  if (*tmp != NULL && (*tmp = strdup(*tmp)) == NULL)
    return (FAIL);
  return (NONE);
}

void		handle_player(t_player *player, char buff[])
{
  int		len;
  char		*tmp;

  if (player->cmd_buff == NULL)
    len = 0;
  else
    len = strlen(player->cmd_buff);
  if ((player->cmd_buff = realloc(player->cmd_buff, 256 + len)) == NULL)
    erase_client(player, 1);
  else
    {
      strcpy(player->cmd_buff + len, buff);
      while (player->cmd_buff && strchr(player->cmd_buff, '\n') != NULL)
	{
	  if (player->cmd.nb_elem < 10
	      && handle_player2(player, &tmp) == FAIL)
	    return ;
	  else if (player->cmd.nb_elem >= 10)
	    tmp = NULL;
	  free(player->cmd_buff);
	  player->cmd_buff = tmp;
	}
    }
}

void		*handle_client(t_elem *player)
{
  t_player	*data;
  char		buff[256];
  int		len;

  data = player->data;
  player = player->next;
  if ((len = read(data->fd, buff, 255)) > 0)
    {
      buff[len] = 0;
      if (data->state == WAITING)
	handle_waiting_player(data, buff);
      else
	handle_player(data, buff);
    }
  else
    erase_client(data, 1);
  return (player);
}
