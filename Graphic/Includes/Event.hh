//
// Event.hh for zappy in /home/bouca-_d/rendu/Zappy/Graphic
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:16:41 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:16:45 2015 Dany Bouca Nova
//

#ifndef EVENT_HH_
# define EVENT_HH_

# include <vector>
# include <string>
# include <utility>
# include <deque>
# include <cstdlib>
# include "Common.hh"

class				Event {

private :
  std::string			_commandType;
  int				_X;
  int				_Y;
  std::vector<int>		_quantities;
  e_ressource			_typeRessource;
  e_orientation			_O;
  int				_nbPlayer;
  std::vector<int>		_nbsPlayersIncant;
  int				_nbEgg;
  int				_lvl;
  bool				_resultIncant;
  std::string			_messageBroadcast;
  std::size_t			_time;
  std::string			_teamName;

public :
  Event(std::string const&);
  ~Event();
  Event(Event const&);
  void				setQuantities(e_ressource, int);
  void				setXY(int, int);
  void				setTeamName(std::string const&);
  void				setNbPlayer(int);
  void				setNbPlayerIncant(int);
  void				setOrientation(e_orientation);
  void				setLvl(int);
  void				setRessourceTaken(e_ressource);
  void				setMessageBroadcast(std::string const&);
  void				setResultIncant(bool);
  void				setNbEgg(int);
  void				setTime(size_t);
  int				getX() const;
  int				getY() const;
  int				getQuantities(e_ressource) const;
  int				getNbPlayer() const;
  e_orientation			getOrientation() const;
  int				getLvl() const;
  std::string const&		getTeamName() const;
  e_ressource			getRessourceTaken() const;
  std::string const&		getMessageBroadcast() const;
  std::vector<int> const&	getNbsPlayersIncant() const;
  bool				getResultIncant() const;
  int				getNbEgg() const;
  std::string const&		getCommandType() const;
  size_t			getTime() const;
};

#endif /* !EVENT_HH_ */
