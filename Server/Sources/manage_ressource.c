/*
** manage_ressource.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:04:30 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:05:05 2015 Dany Bouca Nova
*/

#include "server.h"
#include "common.h"

extern t_serv	g_serv;

void		managelvl4(t_player *player)
{
  if (player->lvl == 2)
    g_serv.map[player->y][player->x].obj[1] -= 1;
  else if (player->lvl == 3)
    {
      g_serv.map[player->y][player->x].obj[1] -= 1;
      g_serv.map[player->y][player->x].obj[2] -= 1;
      g_serv.map[player->y][player->x].obj[3] -= 1;
    }
  else
    {
      g_serv.map[player->y][player->x].obj[1] -= 2;
      g_serv.map[player->y][player->x].obj[3] -= 1;
      g_serv.map[player->y][player->x].obj[5] -= 2;
    }
}

void		managelvl7(t_player *player)
{
  if (player->lvl == 5)
    {
      g_serv.map[player->y][player->x].obj[1] -= 1;
      g_serv.map[player->y][player->x].obj[2] -= 1;
      g_serv.map[player->y][player->x].obj[3] -= 2;
      g_serv.map[player->y][player->x].obj[5] -= 1;
    }
  else if (player->lvl == 6)
    {
      g_serv.map[player->y][player->x].obj[1] -= 1;
      g_serv.map[player->y][player->x].obj[2] -= 2;
      g_serv.map[player->y][player->x].obj[3] -= 1;
      g_serv.map[player->y][player->x].obj[4] -= 3;
    }
  else
    {
      g_serv.map[player->y][player->x].obj[1] -= 1;
      g_serv.map[player->y][player->x].obj[2] -= 2;
      g_serv.map[player->y][player->x].obj[3] -= 3;
      g_serv.map[player->y][player->x].obj[5] -= 1;
    }
}

int		manage_ressource(t_player *player)
{
  if (player->lvl <= 4)
    managelvl4(player);
  else if (player->lvl <= 7)
    managelvl7(player);
  else
    {
      g_serv.map[player->y][player->x].obj[1] -= 2;
      g_serv.map[player->y][player->x].obj[2] -= 2;
      g_serv.map[player->y][player->x].obj[3] -= 2;
      g_serv.map[player->y][player->x].obj[4] -= 2;
      g_serv.map[player->y][player->x].obj[5] -= 2;
      g_serv.map[player->y][player->x].obj[6] -= 1;
    }
  return (NONE);
}
