//
// Requests.hh for zappy in /home/bouca-_d/rendu/Zappy/Graphic
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:11:56 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:13:58 2015 Dany Bouca Nova
//

#ifndef REQUESTS_HH_
# define REQUESTS_HH_

# include <map>
# include <deque>
# include <string>
# include <cstdlib>

class				Requests
{
private :
  std::map<std::string,int>	_requestsMap;

public :
  Requests();
  ~Requests();

  bool				isValid(std::deque<std::string> *command);
  bool				isNumber(const std::string& s);
  bool				isArgValid(std::deque<std::string> *command);
};

#endif /* !REQUESTS_HH_ */
