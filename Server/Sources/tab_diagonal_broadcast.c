/*
** tab_diagonal_broadcast.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:09:11 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:09:11 2015 Dany Bouca Nova
*/

#include "server.h"

void	no_tab(int tab[])
{
  tab[0] = 2;
  tab[1] = 8;
  tab[2] = 4;
  tab[3] = 6;
}

void	ne_tab(int tab[])
{
  tab[0] = 8;
  tab[1] = 6;
  tab[2] = 2;
  tab[3] = 4;
}

void	so_tab(int tab[])
{
  tab[0] = 4;
  tab[1] = 2;
  tab[2] = 6;
  tab[3] = 8;
}

void	se_tab(int tab[])
{
  tab[0] = 6;
  tab[1] = 4;
  tab[2] = 8;
  tab[3] = 2;
}
