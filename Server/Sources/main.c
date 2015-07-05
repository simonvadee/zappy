/*
** main.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:05:22 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:05:23 2015 Dany Bouca Nova
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include "server.h"

t_serv		g_serv;

void		print_conf()
{
  t_elem	*tmp;

  printf("Configuration : Max(%i) WorldX(%i) WorldY(%i) T(%i)\n",
	 g_serv.opt.nb_players, g_serv.opt.x, g_serv.opt.y, g_serv.opt.delay);
  printf("Teams :\n");
  tmp = g_serv.opt.team.first;
  while (tmp != NULL)
    {
      printf("\tName(%s) Max(%i)\n", ((t_team*)tmp->data)->name,
	     g_serv.opt.nb_players);
      tmp = tmp->next;
    }
}

int		main(int ac, char **av)
{
  srandom(time(NULL) * getpid());
  signal(SIGINT, handle_sigint_server);
  if (handle_options(ac, av, 0, 0) == FAIL)
    return (FAIL);
  if (init_server(1) == FAIL || init_map() == FAIL)
    {
      close(g_serv.sock);
      return (FAIL);
    }
  print_conf();
  if (atexit(&free_server) != 0)
    {
      free_server();
      return (FAIL);
    }
  start_server();
  return (NONE);
}
