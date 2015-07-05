/*
** common.h for zappy in /home/bouca-_d/rendu/Zappy/Server
**
** Made by Dany Bouca Nova
** Login   <bouca-_d@epitech.net>
**
** Started on  Sun Jul  5 02:07:12 2015 Dany Bouca Nova
** Last update Sun Jul  5 02:07:13 2015 Dany Bouca Nova
*/

#ifndef COMMON_H_
# define COMMON_H_

typedef struct	s_elem
{
  void		*data;
  struct s_elem	*prev;
  struct s_elem	*next;
}		t_elem;

typedef struct	s_list
{
  unsigned int	nb_elem;
  t_elem	*first;
  t_elem	*last;
}		t_list;

# define FAIL		-1
# define NONE		0
# define MATCH		1
# define PROTOCOL	(char *)"TCP"

int			tablen(char **);
int			my_puterr(const char *);
int			my_perror(const char *);
int			is_number(const char *);
char			**str_to_wordtab(char *);

/*
**		LIST
*/

void			init_list(t_list *);
int			append(t_list *, void *);
int			push(t_list *, void *);
void			*pop_last(t_list *);
void			*pop_first(t_list *);
void			aff_list(t_list *);
void			*del_at_data(t_list *, void *);
void			*del_at_pos(t_list *, unsigned int);
void			clean(t_list *, int);

#endif /* !COMMON_H_ */
