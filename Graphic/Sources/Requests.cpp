//
// Requests.cpp for zappy in /home/bouca-_d/rendu/Zappy/Graphic
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:10:46 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:10:47 2015 Dany Bouca Nova
//

#include "Requests.hh"

Requests::Requests()
{
  _requestsMap["msz"] = 1;
  _requestsMap["bct"] = 3;
  _requestsMap["mct"] = 1;
  _requestsMap["tna"] = 1;
  _requestsMap["ppo"] = 2;
  _requestsMap["plv"] = 2;
  _requestsMap["pin"] = 2;
  _requestsMap["sgt"] = 1;
  _requestsMap["sst"] = 2;
}

Requests::~Requests()
{

}

bool				Requests::isNumber(const std::string& s)
{
  std::string::const_iterator	it;

  for (it = s.begin(); it != s.end(); ++it)
    {
      if (!std::isdigit(*it))
	return (false);
    }
  return (true);
}

bool				Requests::isArgValid(std::deque<std::string> *command)
{
  std::deque<std::string>::iterator	it;

  for (it = command->begin(); it != command->end(); ++it)
    {
      if (it != command->begin() && !isNumber(*it))
	return (false);
    }
  return (true);
}

bool				Requests::isValid(std::deque<std::string> *command)
{
  std::map<std::string,int>::iterator	it;

  for (it = _requestsMap.begin(); it != _requestsMap.end(); ++it)
    {
      if (command->front() == it->first
	  && static_cast<int>(command->size()) == it->second)
	return (static_cast<int>(command->size()) == 1 ? isArgValid(command) : true);
    }
  return (false);
}
