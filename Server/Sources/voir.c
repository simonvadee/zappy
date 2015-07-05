/*
** voir.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:09:14 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:09:15 2015 Dany Bouca Nova
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

extern t_serv		g_serv;

static int		(*tab[4])() = {&scan_n, &scan_e, &scan_s, &scan_o};

int			add_coord(int x, int y, char **buff)
{
  if (food_linemate_deraumere(x, y, buff) == FAIL
      || sibur_mendiane_phiras(x, y, buff) == FAIL
      || thystame_players_eggs(x, y, buff) == FAIL)
    return (FAIL);
  return (NONE);
}

int			add_to_buff(char *s, char **buff)
{
  int			len;

  if (*buff == NULL)
    {
      if ((*buff = malloc(1024)) == NULL)
	return (FAIL);
      (*buff)[0] = 0;
    }
  len = strlen(*buff);
  while (len > 1024)
    len -= 1024;
  if ((1024 - len) <= (int)(strlen(s) + 1)
      && (*buff = realloc(*buff, MULT(strlen(*buff) + strlen(s) + 1, 1024)))
      == NULL)
    return (FAIL);
  *buff = strcat(*buff, s);
  return (NONE);
}

void			voir2(t_player *player, char **buff)
{
  int			c;

  c = 1;
  while (c <= player->lvl)
    {
      if ((tab[player->direction - 1])(player, c, buff) == FAIL)
	return (erase_client(player, 1));
      ++c;
    }
  if (add_to_buff("}", buff) == FAIL || append(&player->send, *buff) == FAIL)
    return (erase_client(player, 1));
}

int			voir(t_player *player, int nb)
{
  char			*buff;

  buff = NULL;
  if (nb == 0)
    player->time = 7.0f / g_serv.opt.delay;
  else
    {
      if (add_to_buff("{", &buff) == FAIL)
	erase_client(player, 1);
      else
	{
	  if (add_coord(player->x, player->y, &buff) == FAIL)
	    erase_client(player, 1);
	  else
	    voir2(player, &buff);
	}
    }
  return (NONE);
}
