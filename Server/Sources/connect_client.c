/*
** connect_client.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:07:30 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:07:31 2015 Dany Bouca Nova
*/

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "server.h"
#include "common.h"

extern t_serv	g_serv;

void		connect_from_egg(t_player *player, t_egg *egg)
{
  t_elem	*ptr;
  void		*data;

  ptr = g_serv.graphic.first;
  while (ptr != NULL)
    {
      data = ptr->data;
      ptr = ptr->next;
      if (ebog(data, egg) == FAIL)
	erase_graphic(data);
    }
  player->nb = egg->nb;
  player->x = egg->x;
  player->y = egg->y;
  del_at_data(&g_serv.map[egg->y][egg->x].eggs, egg);
  del_at_data(&g_serv.eggs, egg);
  free(egg);
  player->state = EGG;
}

int		connect_client2(t_player *player)
{
  t_elem	*list;

  list = g_serv.eggs.first;
  while (list != NULL)
    {
      if (((t_egg*)list->data)->state == WAITING
	  && strcmp(((t_egg*)list->data)->team, player->team) == 0)
	{
	  connect_from_egg(player, list->data);
	  break ;
	}
      list = list->next;
    }
  player->state = CONNECTED;
  player->time = -1;;
  return (NONE);
}

void		connect_client(t_player *player, t_team *team)
{
  t_elem	*list;
  void		*data;

  if (connect_client2(player) == FAIL)
    return ;
  list = g_serv.graphic.first;
  while (list != NULL)
    {
      data = list->data;
      list = list->next;
      if (pnwg(data, player) == FAIL
	  || ping(data, player) == FAIL)
	erase_graphic(data);
    }
  team->nb_player -= 1;
  dprintf(player->fd, "%i\n%i %i\n", team->nb_player, g_serv.opt.x, g_serv.opt.y);
  if (append(&g_serv.map[player->y][player->x].players, player) == FAIL)
    erase_client(player, 1);
}

int		connect_graphic2(t_graph* ptr)
{
  if (append(&ptr->cmd, strdup("msz")) == FAIL
      || append(&ptr->cmd, strdup("sgt")) == FAIL
      || append(&ptr->cmd, strdup("mct")) == FAIL
      || append(&ptr->cmd, strdup("tna")) == FAIL
      || append(&ptr->cmd, strdup("pnw")) == FAIL
      || append(&ptr->cmd, strdup("enw")) == FAIL)
    return (FAIL);
  return (NONE);
}

void		connect_graphic(t_player *player)
{
  t_graph	*new;

  if ((new = malloc(sizeof(t_graph))) == NULL)
    {
      perror("Error malloc");
      erase_client(player, 1);
    }
  else
    {
      new->fd = player->fd;
      new->nb = player->nb;
      new->buff = NULL;
      init_list(&new->cmd);
      init_list(&new->send);
      new->mct_x = 0;
      new->mct_y = 0;
      new->pos = NULL;
      if (connect_graphic2(new) == FAIL
	  || append(&g_serv.graphic, new) == FAIL)
	erase_graphic(new);
      erase_client(player, 0);
    }
}
