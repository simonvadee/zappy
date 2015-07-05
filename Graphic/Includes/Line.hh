//
// Line.hh for zappy in /home/bouca-_d/rendu/Zappy/Graphic
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:17:50 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:17:53 2015 Dany Bouca Nova
//

#ifndef LINE_H_
# define LINE_H_

# include <string>
# include <iostream>
# include <deque>
# include <sstream>

class					Line
{
private :
  std::deque<std::string>*		_command;

public :
  Line();
  ~Line();
  std::deque<std::string>*		getCommand();
  void					parseString(std::string const&);
};

#endif /* !LINE_H_ */
