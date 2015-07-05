/*
** add_client.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:07:08 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:07:09 2015 Dany Bouca Nova
*/

#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "server.h"
#include "common.h"

extern t_serv		g_serv;

t_player		*add_player()
{
  t_player		*new;

  ++g_serv.opt.number_of_client;
  if ((new = malloc(sizeof(t_player))) == NULL)
    {
      my_perror("Error malloc :");
      return (NULL);
    }
  new->nb = g_serv.opt.number_of_client;
  new->direction = random() % 4 + 1;
  new->obj[0] = 0;
  new->obj[1] = 0;
  new->obj[2] = 0;
  new->obj[3] = 0;
  new->obj[4] = 0;
  new->obj[5] = 0;
  new->food = 1260.0f / g_serv.opt.delay;
  if (append(&g_serv.players, new) == FAIL)
    {
      free(new);
      return (NULL);
    }
  return (new);
}

void			player_conf(t_player *player, int fd)
{
  player->team = NULL;
  player->x = random() % g_serv.opt.x;
  player->y = random() % g_serv.opt.y;
  player->state = WAITING;
  player->fd = fd;
  player->lvl = 1;
  player->cmd_buff = NULL;
  player->time = 10;
  init_list(&player->send);
  init_list(&player->cmd);
}

void			new_client()
{
  int			fd;
  t_player		*player;
  struct sockaddr_in	client_sin;
  socklen_t		client_sin_len;

  client_sin_len = sizeof(client_sin);
  if ((fd = accept(g_serv.sock, (struct sockaddr*)&client_sin,
		   &client_sin_len)) == -1)
    {
      my_perror("Error accept :");
      return ;
    }
  printf("*** New connection from %s:%i\n", inet_ntoa(client_sin.sin_addr),
	 client_sin.sin_port);
  if ((player = add_player()) == NULL)
    {
      close(fd);
      return ;
    }
  player_conf(player, fd);
  printf("*** Added new player %i at (%i, %i)\n", player->nb, player->x,
	 player->y);
  write(fd, "BIENVENUE\n", 10);
}
