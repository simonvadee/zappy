/*
** graphic_response.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:07:56 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:07:57 2015 Dany Bouca Nova
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"

extern t_serv	g_serv;

int		mszg(t_graph *ptr)
{
  char		buff[256];

  sprintf(buff, "msz %i %i", g_serv.opt.x, g_serv.opt.y);
  return (append(&ptr->send, strdup(buff)));
}

int		bctg(t_graph* ptr, int x, int y)
{
  char		buff[256];

  sprintf(buff, "bct %i %i %i %i %i %i %i %i %i", x, y,
	  g_serv.map[y][x].obj[0], g_serv.map[y][x].obj[1],
	  g_serv.map[y][x].obj[2], g_serv.map[y][x].obj[3],
	  g_serv.map[y][x].obj[4], g_serv.map[y][x].obj[5],
	  g_serv.map[y][x].obj[6]);
  return (append(&ptr->send, strdup(buff)));
}

int		mctg(t_graph* ptr)
{
  char		buff[256];
  int		i;
  int		j;

  i = ptr->mct_y;
  j = ptr->mct_x;
  sprintf(buff, "bct %i %i %i %i %i %i %i %i %i", j, i,
	  g_serv.map[i][j].obj[0], g_serv.map[i][j].obj[1],
	  g_serv.map[i][j].obj[2], g_serv.map[i][j].obj[3],
	  g_serv.map[i][j].obj[4], g_serv.map[i][j].obj[5],
	  g_serv.map[i][j].obj[6]);
  if (append(&ptr->send, strdup(buff)) == FAIL)
    return (FAIL);
  ptr->mct_x += 1;
  if (ptr->mct_x == g_serv.opt.x)
    {
      ptr->mct_x = 0;
      ptr->mct_y += 1;
    }
  return (NONE);
}

int		tnag(t_graph *ptr)
{
  char		*buff;
  int		*ret;

  if (ptr->pos == NULL)
    ptr->pos = g_serv.opt.team.first;
  if ((buff = malloc(strlen(((t_team*)ptr->pos->data)->name) + 8)) == NULL)
    return (FAIL);
  sprintf(buff, "tna %s", ((t_team*)ptr->pos->data)->name);
  if (append(&ptr->send, buff) == FAIL)
    {
      free(buff);
      return (FAIL);
    }
  ptr->pos = ptr->pos->next;
  if (ptr->pos == NULL)
    {
      ret = pop_first(&ptr->cmd);
      free(ret);
    }
  return (NONE);
}

int		pnwg(t_graph *ptr, t_player *player)
{
  char		*buff;

  if ((buff = malloc(strlen(player->team) + 64)) == NULL)
    return (FAIL);
  sprintf(buff, "pnw %i %i %i %i %i %s", player->nb, player->x, player->y,
	  player->direction, player->lvl, player->team);
  if (append(&ptr->send, buff) == FAIL)
    {
      free(buff);
      return (FAIL);
    }
  return (NONE);
}
