//
// Correspondances.hh for zappy in /home/bouca-_d/rendu/Zappy/Client
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:01:14 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:01:15 2015 Dany Bouca Nova
//

#ifndef CORRESPONDANCES_H_
# define CORRESPONDANCES_H_

# include <iostream>
# include <vector>
# include <map>
# include <regex>

enum							e_msgtype
  {
    NOTHING = 0,
    INCANTATION,
    DEATH,
    STOPHELPING,
    STOPCOMING,
    HELP,
    UP,
    INVENTAIRE,
    VOIR,
    CAN_FAIL,
    CANNOT_FAIL,
    CONNECT_NBR,
    BIRTH
  };

enum							e_itemtype
  {
    NONE = -1,
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    VALID
  };

enum							e_actualstate
  {
    CHILLING = 0,
    HELPING,
    LEADING,
    COMING,
    INCANTATING
  };

class							Correspondances
{
public:
  Correspondances();
  ~Correspondances();

  std::string						getItemName(e_itemtype const& item);
  e_itemtype						getItemFromString(std::string const& item);
  bool							isReciepeFull(std::vector<unsigned int> const& reciepe, int _level);
  int							getNbrPeopleFromLevel(int level);
  e_msgtype						getCommandFromString(std::string const& cmd);
  e_msgtype						getToken(std::string const& cmd);
  unsigned int						getQuantityRequired(e_itemtype item, unsigned int lvl);
  const std::vector<std::string>&			getDirTab(int const pos) const;
  bool							isInReciepe(std::vector<unsigned int> const& reciepe, unsigned int _level);


private:
  std::vector<int>					_peopleRequired;
  std::map<e_itemtype, std::string>			_itemMap;
  std::vector<std::vector<unsigned int> >		_reciepeList;
  std::map<std::string, e_msgtype>			_sendMsgMap;
  std::map<e_msgtype, std::regex>			_recvMsgMap;
  std::vector<std::vector<std::string> >		_dirTab;
};

#endif /* !CORRESPONDANCES_H_ */
