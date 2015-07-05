//
// Line.cpp for zappy in /home/bouca-_d/rendu/Zappy/Graphic
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:11:00 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:11:02 2015 Dany Bouca Nova
//

#include "Line.hh"

Line::Line()
  : _command(new std::deque<std::string>)
{
}

Line::~Line()
{
  delete _command;
}

void				Line::parseString(std::string const& line)
{
  std::istringstream		is;
  std::string			elem;

  (*_command).clear();
  is.str(line);
  while (is >> elem)
    (*_command).push_back(elem);
}

std::deque<std::string>*	Line::getCommand()
{
  return (_command);
}
