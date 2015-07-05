/*
** graphic_response4.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:07:52 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:07:54 2015 Dany Bouca Nova
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"

extern t_serv	g_serv;

int		pdig(t_graph* ptr, t_player *player)
{
  char		buff[256];

  sprintf(buff, "pdi %i", player->nb);
  return (append(&ptr->send, strdup(buff)));
}

int		enwg(t_graph *ptr, t_egg *egg)
{
  char		buff[256];

  sprintf(buff, "enw %i %i %i %i", egg->nb, egg->father, egg->x, egg->y);
  return (append(&ptr->send, strdup(buff)));
}

int		ehtg(t_graph *ptr, t_egg *egg)
{
  char		buff[256];

  sprintf(buff, "eht %i", egg->nb);
  return (append(&ptr->send, strdup(buff)));
}

int		ebog(t_graph* ptr, t_egg *egg)
{
  char		buff[256];

  sprintf(buff, "ebo %i", egg->nb);
  return (append(&ptr->send, strdup(buff)));
}

int		edig(t_graph* ptr, t_egg *egg)
{
  char		buff[256];

  sprintf(buff, "edi %i", egg->nb);
  return (append(&ptr->send, strdup(buff)));
}
