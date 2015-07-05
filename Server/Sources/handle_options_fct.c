/*
** handle_options_fct.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:08:04 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:08:05 2015 Dany Bouca Nova
*/

#include <stdio.h>
#include <stdlib.h>
#include "server.h"

extern t_serv	g_serv;

inline int	fill_port(char **cmd)
{
  return (g_serv.opt.port = atoi(cmd[0]));
}

inline int	fill_x(char **cmd)
{
  return (g_serv.opt.x = atoi(cmd[0]));
}

inline int	fill_y(char **cmd)
{
  return (g_serv.opt.y = atoi(cmd[0]));
}

inline int	fill_nb_players(char **cmd)
{
  return (g_serv.opt.nb_players = atoi(cmd[0]));
}

inline int	fill_delay(char **cmd)
{
  return (g_serv.opt.delay = atoi(cmd[0]));
}
