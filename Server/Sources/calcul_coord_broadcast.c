/*
** calcul_coord_broadcast.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:07:26 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:07:26 2015 Dany Bouca Nova
*/

#include "server.h"

int	calculate_lower(int speaker, int listener, int max, int coord1)
{
  int	coord2;

  if (listener >= (max / 2))
    coord2 = max - listener + 1 + speaker;
  else
    return (-1);
  coord1 = -coord1;
  if (coord1 < coord2)
    return (-1);
  else
    return (1);
  return (0);
}

int	calculate_higher(int speaker, int listener, int max, int coord1)
{
  int	coord2;

  if (listener <= (max / 2))
    coord2 =listener + (max - speaker);
  else
    return (1);
  if (coord1 > coord2)
    return (-1);
  else
    return (1);
  return (0);
}

int	calculate(int speaker, int listener, int max)
{
  int	coord1;

  coord1 = speaker - listener;
  if (coord1 < 0)
    return (calculate_lower(speaker, listener, max, coord1));
  else
    return (calculate_higher(speaker, listener, max, coord1));
  return (0);
}
