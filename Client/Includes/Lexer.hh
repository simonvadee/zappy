//
// Lexer.hh for zappy in /home/bouca-_d/rendu/Zappy/Client
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:01:25 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:03:18 2015 Dany Bouca Nova
//

#ifndef LEXER_HH_
# define LEXER_HH_

# include <algorithm>
# include "Network.hh"

class		Lexer
{

public:
  Lexer(int ac, char **av);
  ~Lexer();

  bool		lex(Network &obj);

private:
  unsigned int	_nb;
  char		**_args;

  bool		usage();
};

#endif /* !LEXER_HH_ */
