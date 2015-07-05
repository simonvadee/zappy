/*
** handle_options.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:06:06 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:06:07 2015 Dany Bouca Nova
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "server.h"
#include "common.h"

static const t_cmdopt	g_cmdopt[] =
  {
    {'p', &fill_port},
    {'y', &fill_y},
    {'x', &fill_x},
    {'c', &fill_nb_players},
    {'t', &fill_delay},
    {0, NULL}
  };

extern t_serv		g_serv;

int			double_team(char *s)
{
  t_elem		*team;

  team = g_serv.opt.team.first;
  while (team)
    {
      if (strcmp(((t_team*)team->data)->name, s) == 0)
	{
	  fprintf(stderr, "Cannot choose a team name twice\n");
	  return (FAIL);
	}
      team = team->next;
    }
  return (NONE);
}

static int		fill_names(char **av, int *i)
{
  t_team		*team;

  ++(*i);
  while (av[*i] && av[*i][0] != '-')
    {
      if (strcmp(av[*i], "GRAPHIC") == 0)
	fprintf(stderr, "You cannot choose GRAPHIC for a team name\n");
      else if (double_team(av[*i]) == NONE)
	{
	  if ((team = malloc(sizeof(t_team))) == NULL)
	    return (my_perror("Error malloc :"));
	  team->nb_lvl_max = 0;
	  team->name = av[*i];
	  if (append(&g_serv.opt.team, team) == FAIL)
	    return (FAIL);
	}
      ++(*i);
    }
  --(*i);
  return (NONE);
}

static int		check_options(int *i, int *j, char **av)
{
  while (g_cmdopt[++*j].c != 0)
    {
      if (g_cmdopt[*j].c == av[*i][1])
	{
	  if ((!(av[*i + 1])) || is_number(av[*i + 1]) == FAIL ||
	      ((g_cmdopt[*j].ptr)(&av[++*i]) == FAIL))
	    return (my_puterr(MSG1));
	  break ;
	}
    }
  if (g_cmdopt[*j].c == 0)
    return (my_puterr(MSG1));
  return (NONE);
}

int			end_option()
{
  t_elem		*ptr;

  ptr = g_serv.opt.team.first;
  while (ptr)
    {
      ((t_team*)ptr->data)->nb_player = g_serv.opt.nb_players;
      ptr = ptr->next;
    }
  if (g_serv.opt.port < 0 || g_serv.opt.x < 1 || g_serv.opt.y < 1
      || g_serv.opt.delay < 1|| g_serv.opt.nb_players < 1
      || g_serv.opt.team.nb_elem < 2)
    return (my_puterr(MSG1));
  return (NONE);
}

int			handle_options(int ac, char **av, int i, int j)
{
  g_serv.opt.x = 20;
  g_serv.opt.y = 20;
  g_serv.opt.port = 4242;
  g_serv.opt.nb_players = 1;
  g_serv.opt.delay = 100;
  init_list(&g_serv.opt.team);
  while (++i != ac && av[i])
    {
      j = -1;
      if (av[i][0] == '-' && av[i][1])
  	{
  	  if (av[i][1] == 'n')
	    {
	      if (fill_names(av, &i) == FAIL)
		return (FAIL);
	    }
	  else if (av[i][1] != 'n' && check_options(&i, &j, av) == FAIL)
	    return (FAIL);
  	}
      else
	return (my_puterr(MSG1));
    }
  return (end_option());
}
