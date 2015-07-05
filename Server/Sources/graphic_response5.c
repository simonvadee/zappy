/*
** graphic_response5.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:06:13 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:06:14 2015 Dany Bouca Nova
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "server.h"

extern t_serv	g_serv;

int	sgtg(t_graph *ptr)
{
  char	buff[256];

  sprintf(buff, "sgt %i", g_serv.opt.delay);
  return (append(&ptr->send, strdup(buff)));
}

int	segg(t_graph* ptr, char *team)
{
  char	*buff;

  if ((buff = malloc(strlen(team) + 8)) == NULL)
    return (FAIL);
  sprintf(buff, "seg %s", team);
  if (append(&ptr->send, buff) == FAIL)
    {
      free(buff);
      return (FAIL);
    }
  return (NONE);
}

int	smgg(t_graph* ptr, char *msg)
{
  char	*buff;

  if ((buff = malloc(strlen(msg) + 8)) == NULL)
    return (FAIL);
  sprintf(buff, "smg %s", msg);
  if (append(&ptr->send, buff) == FAIL)
    {
      free(buff);
      return (FAIL);
    }
  return (NONE);
}

int	sucg(t_graph *ptr)
{
  char	buff[256];

  sprintf(buff, "suc");
  return (append(&ptr->send, strdup(buff)));
}

int	sbpg(t_graph* ptr)
{
  char	buff[256];

  sprintf(buff, "sbp");
  return (append(&ptr->send, strdup(buff)));
}
