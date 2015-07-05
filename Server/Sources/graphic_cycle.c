/*
** graphic_cycle.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:07:42 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:07:42 2015 Dany Bouca Nova
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "server.h"
#include "common.h"

extern t_serv		g_serv;

static const t_cmd	g_cmd[] =
  {
    {"msz", &mszgh},
    {"bct", &bctgh},
    {"mct", &mctgh},
    {"tna", &tnag},
    {"pnw", &pnwgh},
    {"ppo", &ppogh},
    {"plv", &plvgh},
    {"pin", &pingh},
    {"enw", &enwgh},
    {"sgt", &sgtgh},
    {"sst", &sstgh},
    {NULL, NULL}
  };

void			end_analyze(t_graph *graph)
{
  void			*ret;

  if (sucg(graph) == FAIL)
    erase_graphic(graph);
  else
    {
      ret = pop_first(&graph->cmd);
      free(ret);
    }
}

void			analyze_command(t_graph* graph)
{
  int			i;
  char			*array[3];

  if (graph->cmd.first->data != NULL)
    {
      array[0] = strtok((char*)graph->cmd.first->data, " ");
      array[1] = strtok(NULL, " ");
      array[2] = strtok(NULL, " ");
      i = -1;
      while (g_cmd[++i].cmd)
	{
	  if (array[0] && strcmp(array[0], g_cmd[i].cmd) == 0)
	    {
	      if (g_cmd[i].ptr(graph, array[1], array[2]) == FAIL)
		erase_graphic(graph);
	      return;
	    }
	}
    }
  end_analyze(graph);
}

void			graphic_cycle()
{
  t_elem		*ptr;
  t_graph		*data;

  ptr = g_serv.graphic.first;
  while (ptr != NULL)
    {
      data = ptr->data;
      ptr = ptr->next;
      if (data->cmd.nb_elem != 0)
	analyze_command(data);
    }
}
