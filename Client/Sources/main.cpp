//
// main.cpp for zappy in /home/bouca-_d/rendu/Zappy/Client
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:00:27 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:00:27 2015 Dany Bouca Nova
//

#include <cstdlib>
#include <ctime>
#include "Network.hh"
#include "Lexer.hh"
#include "ZappyIA.hh"

int				main(int ac, char **av)
{
  Lexer				lexer(ac, av);
  Correspondances		database;
  std::deque<std::string>	toReceive;
  std::deque<std::string>	toSend;

  Network			network(&toSend, &toReceive, database);
  ZappyIA			ia(&toSend, &toReceive, &network, database);

  if (!lexer.lex(network))
    return 1;
  srand(time(NULL));
  ia.run();
  return 0;
}
