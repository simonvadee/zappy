/*
** functions.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:06:26 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:06:27 2015 Dany Bouca Nova
*/

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "common.h"

int	my_puterr(const char *s)
{
  write(STDERR_FILENO, s, strlen(s));
  return (FAIL);
}

int	my_perror(const char *s)
{
  perror(s);
  return (FAIL);
}

int	is_number(const char *s)
{
  int	i;

  i = -1;
  while (++i)
    {
      if (s[i] < 48 && s[i] > 57)
	return (FAIL);
    }
  return (NONE);
}

int	tablen(char **cmd)
{
  int	i;

  i = 0;
  while (cmd[i])
    ++i;
  return (i);
}
