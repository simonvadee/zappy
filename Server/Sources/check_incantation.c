/*
** check_incantation.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:06:49 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:07:02 2015 Dany Bouca Nova
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"
#include "common.h"

extern t_serv	g_serv;

int		check1(t_player *player, int i)
{
  if (player->lvl == 1 &&
      (i != 1 || g_serv.map[player->y][player->x].obj[1] != 1
       || g_serv.map[player->y][player->x].obj[2] != 0
       || g_serv.map[player->y][player->x].obj[3] != 0
       || g_serv.map[player->y][player->x].obj[4] != 0
       || g_serv.map[player->y][player->x].obj[5] != 0
       || g_serv.map[player->y][player->x].obj[6] != 0))
    return (-1);
  if (player->lvl == 2 &&
      (g_serv.map[player->y][player->x].obj[1] != 1
       || g_serv.map[player->y][player->x].obj[2] != 1
       || g_serv.map[player->y][player->x].obj[3] != 1
       || g_serv.map[player->y][player->x].obj[4] != 0
       || g_serv.map[player->y][player->x].obj[5] != 0
       || g_serv.map[player->y][player->x].obj[6] != 0 || i != 2))
    return (-1);
  if (player->lvl == 3 &&
      (g_serv.map[player->y][player->x].obj[1] != 2
       || g_serv.map[player->y][player->x].obj[2] != 0
       || g_serv.map[player->y][player->x].obj[3] != 1
       || g_serv.map[player->y][player->x].obj[4] != 0
       || g_serv.map[player->y][player->x].obj[5] != 2
       || g_serv.map[player->y][player->x].obj[6] != 0 || i != 2))
    return (-1);
  return (i);
}

int		check2(t_player *player, int i)
{
  if (player->lvl == 4 &&
      (g_serv.map[player->y][player->x].obj[1] != 1
       || g_serv.map[player->y][player->x].obj[2] != 1
       || g_serv.map[player->y][player->x].obj[3] != 2
       || g_serv.map[player->y][player->x].obj[4] != 0
       || g_serv.map[player->y][player->x].obj[5] != 1
       || g_serv.map[player->y][player->x].obj[6] != 0 || i != 4))
    return (-1);
  if (player->lvl == 5 &&
      (g_serv.map[player->y][player->x].obj[1] != 1
       || g_serv.map[player->y][player->x].obj[2] != 2
       || g_serv.map[player->y][player->x].obj[3] != 1
       || g_serv.map[player->y][player->x].obj[4] != 3
       || g_serv.map[player->y][player->x].obj[5] != 0
       || g_serv.map[player->y][player->x].obj[6] != 0 || i != 4))
    return (-1);
  if (player->lvl == 6 &&
      (g_serv.map[player->y][player->x].obj[1] != 2
       || g_serv.map[player->y][player->x].obj[2] != 2
       || g_serv.map[player->y][player->x].obj[3] != 3
       || g_serv.map[player->y][player->x].obj[4] != 0
       || g_serv.map[player->y][player->x].obj[5] != 1
       || g_serv.map[player->y][player->x].obj[6] != 0 || i != 6))
    return (-1);
  return (i);
}

int		check3(t_player *player, int i)
{
  if (g_serv.map[player->y][player->x].obj[1] != 2
      || g_serv.map[player->y][player->x].obj[2] != 2
      || g_serv.map[player->y][player->x].obj[3] != 2
      || g_serv.map[player->y][player->x].obj[4] != 2
      || g_serv.map[player->y][player->x].obj[5] != 2
      || g_serv.map[player->y][player->x].obj[6] != 1 || i != 6)
    return (-1);
  return (i);
}

int		check_incantation(t_player *player)
{
  int		i;
  t_elem	*ptr;

  i = 0;
  ptr = g_serv.map[player->y][player->x].players.first;;
  while (ptr != NULL)
    {
      if (((t_player*)ptr->data)->state == CONNECTED)
	++i;
      ptr = ptr->next;
    }
  if (player->lvl <= 3)
    return (check1(player, i));
  else if (player->lvl > 3 && player->lvl <= 6)
    return (check2(player, i));
  else
    return (check3(player, i));
}
