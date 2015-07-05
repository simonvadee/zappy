/*
** str_to_wordtab.c for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:04:17 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:04:18 2015 Dany Bouca Nova
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static int	count_words(char *s)
{
  int		nb;
  int		i;

  i = -1;
  nb = 0;
  while (s[++i])
    if (s[i + 1] && (s[i + 1] != ' ' && s[i + 1] != '\t') &&
	((s[i] == ' ' || s[i] == '\t') || i == 0))
      ++nb;
  return (nb);
}

char		**str_to_wordtab(char *s)
{
  char		**tab;
  int		count;
  int		nb;
  int		i;
  int		j;

  if (((nb = count_words(s)) == 0) || (!(count = -1)) ||
      (!(tab = malloc(sizeof(char *) * (nb + 1)))))
    return (NULL);
  tab[nb] = NULL;
  while (++count != nb && (!(i = 0)))
    {
      while (*s == ' ' || *s == '\t')
	++s;
      while (s[i] && s[i] != ' ' && s[i] != '\t')
	++i;
      if ((j = 0) || (!(tab[count] = malloc(sizeof(char) * (i + 1)))))
	return (NULL);
      tab[count][i] = '\0';
      while (s && j < i)
	tab[count][j++] = *s++;
    }
  tab[count] = NULL;
  return (tab);
}
