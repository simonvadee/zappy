/*
** manage_player.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:08:27 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:08:28 2015 Dany Bouca Nova
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"
#include "common.h"

extern t_serv		g_serv;

static const t_cmd	cmd[] =
  {
    {"avance", &avance},
    {"droite", &droite},
    {"gauche", &gauche},
    {"voir", &voir},
    {"inventaire", &inventaire},
    {"prend", &prend},
    {"pose", &pose},
    {"expulse", &expulse},
    {"broadcast", &broadcasts},
    {"incantation", &incantation},
    {"fork", &forkp},
    {"connect_nbr", &connect_nbr},
    {NULL, NULL}
  };

void			send_ko(t_player *player)
{
  char			*buff;

  if ((buff = malloc(4)) == NULL)
    erase_client(player, 1);
  sprintf(buff, "ko");
  if (append(&player->send, buff) == FAIL)
    {
      free(buff);
      erase_client(player, 1);
    }
}

void			del_cmd(t_player *player)
{

  void			*ptr;

  ptr = pop_first(&player->cmd);
  free(ptr);
  player->time = -1;
}

void			cmd_player(t_player *player, int nb)
{
  int			i;
  char			*s;
  char			*s1;
  char			*s2;

  if (player->cmd.first->data != NULL)
    {
      s = strdup((char*)player->cmd.first->data);
      s1 = strtok(s, " ");
      s2 = strtok(NULL, "");
      i = -1;
      while (s1 && cmd[++i].cmd != NULL)
	{
	  if (strcmp(s1, cmd[i].cmd) == 0)
	    {
	      cmd[i].ptr(player, nb, s2);
	      free(s);
	      return;
	    }
	}
      free(s);
    }
  send_ko(player);
  if (player)
    player->time = -1;
}

void			*manage_player(t_elem *ptr, float time)
{
  t_player		*player;

  player = ptr->data;
  ptr = ptr->next;
  player->food -= time;
  if (player->food <= 0.0000)
    erase_client(player, 1);
  else if (player->cmd.nb_elem > 0)
    {
      if (player->time == -1.0000)
	cmd_player(player, 0);
      else
	{
	  player->time -= time;
	  if (player->time <= 0.0000
	      || strncmp("incantation", player->cmd.first->data, 11) == 0)
	    cmd_player(player, 1);
	}
      if (player && player->time <= 0.0000)
	del_cmd(player);
    }
  return (ptr);
}
