//
// GetLine.hh for zappy in /home/bouca-_d/rendu/Zappy/Graphic
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:14:56 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:14:57 2015 Dany Bouca Nova
//

#ifndef GETLINE_H_
# define GETLINE_H_

# include <string>
# include <iostream>
# include <deque>
# include <sstream>

class					GetLine
{
private :
  bool					_set;
  std::istream*				_is;
  std::deque<std::string>*		_command;
  std::string				_line;

public :
  GetLine(std::istream& is);
  ~GetLine();
  int				readInput();
  void				setStream(std::istream& is);
  bool				isSet() const;
  std::deque<std::string>*	getCommand();
  std::string			getStringRequest() const;

private :
  std::istream&			getLine(std::string&);
};

#endif /* !GETLINE_H_ */
