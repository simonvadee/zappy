//
// Lexer.cpp for zappy in /home/bouca-_d/rendu/Zappy/Client
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:01:32 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:03:25 2015 Dany Bouca Nova
//

#include "Lexer.hh"

Lexer::Lexer(int ac, char **av)
  : _nb(ac), _args(av)
{
}

Lexer::~Lexer()
{
}

bool			Lexer::usage()
{
  std::cerr << "Usage :  ./client [-n teamname] [-p port] (([-h machine name]))" << std::endl;
  return false;
}

bool			Lexer::lex(Network &obj)
{
  std::string		tmp;
  std::string		next;

  if (_nb < 5)
    return usage();
  for (unsigned int i = 0; i != _nb; ++i)
    {
      tmp = _args[i];
      next = (_args[i + 1] ? _args[i + 1] : "");
      if (tmp == "-p")
	{
	  if (next != "" && std::all_of(next.begin(), next.end(), ::isdigit))
	    obj.setPort(std::atoi(next.c_str()));
	  else
	    {
	      std::cerr << "Argument -p must be followed by a valid port" << std::endl;
	      return false;
	    }
	}
      else if (tmp == "-n")
	{
	  if (next != "" && std::all_of(next.begin(), next.end(), ::isalnum))
	    obj.setTeamname(next.c_str());
	  else
	    {
	      std::cerr << "Argument -n must be followed by a valid team name (with alphanumeric characters)" << std::endl;
	      return false;
	    }
	}
      else if (tmp == "-h")
	{
	  if (next != "")
	    obj.setHostname(next.c_str());
	  else
	    {
	      std::cerr << "Argument -h must be followed by a hostname" << std::endl;
	      return false;
	    }
	}
    }
  return obj.checkArgs();
}
