/*
** broadcast_graphic.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:07:21 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:07:22 2015 Dany Bouca Nova
*/

#include "server.h"

extern t_serv	g_serv;

void		broadcast_graphic(t_player *player, char *msg)
{
  t_elem	*ptr;
  void		*tmp;

  ptr = g_serv.graphic.first;
  while (ptr)
    {
      tmp = ptr->data;
      ptr = ptr->next;
      if (pbcg(tmp, player, msg) == FAIL)
	erase_graphic(tmp);
    }
}
