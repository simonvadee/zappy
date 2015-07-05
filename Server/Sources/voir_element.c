/*
** voir_element.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:04:10 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:04:11 2015 Dany Bouca Nova
*/

#include <string.h>
#include <stdio.h>
#include "server.h"

extern t_serv	g_serv;

int		food_linemate_deraumere(int x, int y, char **buff)
{
  int		c;

  c = g_serv.map[y][x].obj[0];
  while (c > 0)
    {
      if (add_to_buff(" nourriture", buff) == FAIL)
	return (FAIL);
      --c;
    }
  c = g_serv.map[y][x].obj[1];
  while (c > 0)
    {
      if (add_to_buff(" linemate", buff) == FAIL)
	return (FAIL);
      --c;
    }
  c = g_serv.map[y][x].obj[2];
  while (c > 0)
    {
      if (add_to_buff(" deraumere", buff) == FAIL)
	return (FAIL);
      --c;
    }
  return (NONE);
}

int		sibur_mendiane_phiras(int x, int y, char **buff)
{
  int		c;

  c = g_serv.map[y][x].obj[3];
  while (c > 0)
    {
      if (add_to_buff(" sibur", buff) == FAIL)
	return (FAIL);
      --c;
    }
  c = g_serv.map[y][x].obj[4];
  while (c > 0)
    {
      if (add_to_buff(" mendiane", buff) == FAIL)
	return (FAIL);
      --c;
    }
  c = g_serv.map[y][x].obj[5];
  while (c > 0)
    {
      if (add_to_buff(" phiras", buff) == FAIL)
	return (FAIL);
      --c;
    }
  return (NONE);
}

int		thystame_players_eggs(int x, int y, char **buff)
{
  int		c;
  t_elem	*ptr;

  c = g_serv.map[y][x].obj[6];
  while (c > 0)
    {
      if (add_to_buff(" thystame", buff) == FAIL)
	return (FAIL);
      --c;
    }
  ptr = g_serv.map[y][x].players.first;
  while (ptr)
    {
      if (((t_player*)ptr->data)->state == CONNECTED
	  && add_to_buff(" joueur", buff) == FAIL)
	return (FAIL);
      ptr = ptr->next;
    }
  return (NONE);
}
