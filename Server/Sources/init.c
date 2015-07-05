/*
** init.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:05:54 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:05:55 2015 Dany Bouca Nova
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "server.h"

extern t_serv		g_serv;

int			init_server(int i)
{
  struct protoent	*pe;
  struct sockaddr_in	s_in;

  init_list(&g_serv.graphic);
  init_list(&g_serv.players);
  init_list(&g_serv.eggs);
  if (!(pe = getprotobyname("TCP")))
    return (my_perror("Error Getprotobyname"));
  if ((g_serv.sock = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (my_perror("Error Socket"));
  if (setsockopt(g_serv.sock, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i)) < 0)
    return (my_perror("Error Socket "));
  s_in.sin_family = AF_INET;
  s_in.sin_port = htons(g_serv.opt.port);
  s_in.sin_addr.s_addr = INADDR_ANY;
  if (bind(g_serv.sock, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1)
    {
      fprintf(stderr, "Error : cannot listen on port %i\n", g_serv.opt.port);
      return (FAIL);
    }
  if (listen(g_serv.sock, SOMAXCONN) == -1)
    return (my_perror("Error Listen"));
  printf("Listening on port %i...\n", g_serv.opt.port);
  g_serv.opt.number_of_client = 0;
  return (NONE);
}

void			rand_res(int x, int y)
{
  int			i;

  i = 1;
  while (i < 7)
    {
      srandom(time(0) * rand());
      g_serv.map[y][x].obj[i] += random() % 3;
      ++i;
    }
}

void			init_map2(int y, int x)
{
  while (++x < g_serv.opt.x)
    {
      g_serv.map[y][x].obj[0] = 2;
      g_serv.map[y][x].obj[1] = 0;
      g_serv.map[y][x].obj[2] = 0;
      g_serv.map[y][x].obj[3] = 0;
      g_serv.map[y][x].obj[4] = 0;
      g_serv.map[y][x].obj[5] = 0;
      g_serv.map[y][x].obj[6] = 0;
      if (random() % 2 == 0)
	g_serv.map[y][x].obj[0] = random() % 4;
      rand_res(x, y);
      init_list(&g_serv.map[y][x].players);
      init_list(&g_serv.map[y][x].eggs);
    }
}

int			init_map(void)
{
  int			i;

  if (!(g_serv.map = malloc(sizeof(t_map *) * g_serv.opt.y)))
    return (my_perror("Error Malloc"));
  i = -1;
  while (++i != g_serv.opt.y)
    g_serv.map[i] = NULL;
  i = -1;
  while (++i != g_serv.opt.y)
    {
      if (!(g_serv.map[i] = malloc(sizeof(t_map) * g_serv.opt.x)))
	return (my_perror("Error Malloc"));
      init_map2(i, -1);
    }
  return (NONE);
}
