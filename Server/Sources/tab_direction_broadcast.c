/*
** tab_direction_broadcast.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:04:14 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:04:14 2015 Dany Bouca Nova
*/

#include "server.h"

void			direction_tab(e_direction dir[])
{
  dir[0] = N;
  dir[1] = O;
  dir[2] = E;
  dir[3] = S;
}

void			horizontal_tab(int left[], int right[])
{
  left[0] = 3;
  left[1] = 1;
  left[2] = 5;
  left[3] = 7;
  right[0] = 7;
  right[1] = 5;
  right[2] = 1;
  right[3] = 3;
}

void			vertical_tab(int up[], int down[])
{
  up[0] = 1;
  up[1] = 7;
  up[2] = 3;
  up[3] = 5;
  down[0] = 5;
  down[1] = 3;
  down[2] = 7;
  down[3] = 1;
}
