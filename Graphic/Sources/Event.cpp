//
// Event.cpp for zappy in /home/bouca-_d/rendu/Zappy/Graphic
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:19:30 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:19:30 2015 Dany Bouca Nova
//

#include <iostream>
#include "Event.hh"

Event::Event(std::string const& commandType)
  : _commandType(commandType),
    _X(-1),
    _Y(-1),
    _typeRessource(NONE),
    _O(NODIR),
    _nbPlayer(-1),
    _nbEgg(-1),
    _lvl(-1),
    _resultIncant(false),
    _messageBroadcast(""),
    _time(0),
    _teamName("")
{
  for (int i = 0; i < 7; ++i)
    _quantities.push_back(0);
}

Event::Event(Event const& event)
{
  _commandType = event._commandType;
  _X = event._X;
  _Y = event._Y;
  for (size_t i = 0; i < event._quantities.size(); ++i)
    _quantities.push_back(event._quantities[i]);
  _typeRessource = event._typeRessource;
  _O = event._O;
  _nbPlayer = event._nbPlayer;
  _nbEgg = event._nbEgg;
  _lvl = event._lvl;
  _resultIncant = event._resultIncant;
  _messageBroadcast = event._messageBroadcast;
  _teamName = event._teamName;
  _time = event._time;
}

Event::~Event()
{
}

void			Event::setQuantities(e_ressource ressource, int nb)
{
  _quantities[ressource] = nb;
}

void			Event::setXY(int X, int Y)
{
  _X = X;
  _Y = Y;
}

void			Event::setTeamName(std::string const& teamName)
{
  _teamName = teamName;
}

void			Event::setNbPlayer(int nbPlayer)
{
  _nbPlayer = nbPlayer;
}

void			Event::setOrientation(e_orientation O)
{
  _O = O;
}

void			Event::setLvl(int lvl)
{
  _lvl = lvl;
}


void			Event::setRessourceTaken(e_ressource ressource)
{
  _typeRessource = ressource;
}


void			Event::setMessageBroadcast(std::string const& message)
{
  _messageBroadcast = message;
}

void			Event::setNbPlayerIncant(int nbPlayer)
{
  _nbsPlayersIncant.push_back(nbPlayer);
}

void			Event::setResultIncant(bool result)
{
  _resultIncant = result;
}

void			Event::setNbEgg(int nbEgg)
{
  _nbEgg = nbEgg;
}

void			Event::setTime(std::size_t time)
{
  _time = time;
}

int			Event::getX() const
{
  return _X;
}

int			Event::getY() const
{
  return _Y;
}

int			Event::getQuantities(e_ressource type) const
{
  return _quantities[type];
}

int			Event::getNbPlayer() const
{
  return _nbPlayer;
}

e_orientation		Event::getOrientation() const
{
  return _O;
}

int			Event::getLvl() const
{
  return _lvl;
}

std::string const&	Event::getTeamName() const
{
  return _teamName;
}

e_ressource		Event::getRessourceTaken() const
{
  return _typeRessource;
}


std::string const&	Event::getMessageBroadcast() const
{
  return _messageBroadcast;
}

std::vector<int> const&	Event::getNbsPlayersIncant() const
{
  return _nbsPlayersIncant;
}

bool			Event::getResultIncant() const
{
  return _resultIncant;
}

int			Event::getNbEgg() const
{
  return _nbEgg;
}

std::size_t		Event::getTime() const
{
  return _time;
}

std::string const&	Event::getCommandType() const
{
  return _commandType;
}
