//
// GetLine.cpp for zappy in /home/bouca-_d/rendu/Zappy/Graphic
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:19:38 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:19:38 2015 Dany Bouca Nova
//

#include "GetLine.hh"

GetLine::GetLine(std::istream& is)
  : _set(true), _is(&is), _command(new std::deque<std::string>)
{
}

GetLine::~GetLine()
{
  delete _command;
}

std::istream&			GetLine::getLine(std::string& line)
{
  char				c;

  line.clear();
  while ((*_is).good())
    {
      c = (*_is).get();
      if (c == '\n'
	  || (c == '\r' && (*_is).get() == '\n'))
	break;
      line += c;
    }
  return ((*_is));
}

int				GetLine::readInput()
{
  std::istringstream		is;
  std::string			line;
  std::string			elem;

  (*_command).clear();
  getLine(line);
  _line = line;
  is.str(line);
  while (is >> elem)
    (*_command).push_back(elem);
  return (1);
}

bool				GetLine::isSet() const
{
  return (_set);
}

void				GetLine::setStream(std::istream& is)
{
  _is = &is;
  _set = true;
}

std::deque<std::string>*	GetLine::getCommand()
{
  return (_command);
}

std::string			GetLine::getStringRequest() const
{
  return (_line);
}
