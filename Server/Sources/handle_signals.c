/*
** handle_signals.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:06:03 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:06:04 2015 Dany Bouca Nova
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "server.h"

extern t_serv	g_serv;

void		free_server()
{
  int		i;

  i = -1;
  while (g_serv.players.first != NULL)
    erase_client((t_player*)g_serv.players.first->data, 1);
  while (g_serv.graphic.first != NULL)
    erase_graphic((t_graph*)g_serv.graphic.first->data);
  while (++i < g_serv.opt.y)
    free(g_serv.map[i]);
  free(g_serv.map);
  clean(&g_serv.opt.team, 1);
  clean(&g_serv.eggs, 1);
  close(g_serv.sock);
}

void		handle_sigint_server(int sig)
{
  (void)sig;
  (void)printf("\b\b  SIGINT Catched. Freeing ressources ...\n");
  exit(FAIL);
}
