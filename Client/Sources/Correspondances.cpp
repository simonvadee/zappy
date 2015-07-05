//
// Correspondances.cpp for zappy in /home/bouca-_d/rendu/Zappy/Client
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:00:40 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:01:53 2015 Dany Bouca Nova
//

#include "Correspondances.hh"

Correspondances::Correspondances()
{
  std::vector<unsigned int>		fill;
  std::vector<std::string>		dir;

  fill.push_back(0);
  fill.push_back(1);
  fill.push_back(0);
  fill.push_back(0);
  fill.push_back(0);
  fill.push_back(0);
  fill.push_back(0);
  _reciepeList.push_back(fill);
  fill.clear();
  fill.push_back(0);
  fill.push_back(1);
  fill.push_back(1);
  fill.push_back(1);
  fill.push_back(0);
  fill.push_back(0);
  fill.push_back(0);
  _reciepeList.push_back(fill);
  fill.clear();
  fill.push_back(0);
  fill.push_back(2);
  fill.push_back(0);
  fill.push_back(1);
  fill.push_back(0);
  fill.push_back(2);
  fill.push_back(0);
  _reciepeList.push_back(fill);
  fill.clear();
  fill.push_back(0);
  fill.push_back(1);
  fill.push_back(1);
  fill.push_back(2);
  fill.push_back(0);
  fill.push_back(1);
  fill.push_back(0);
  _reciepeList.push_back(fill);
  fill.clear();
  fill.push_back(0);
  fill.push_back(1);
  fill.push_back(2);
  fill.push_back(1);
  fill.push_back(3);
  fill.push_back(0);
  fill.push_back(0);
  _reciepeList.push_back(fill);
  fill.clear();
  fill.push_back(0);
  fill.push_back(1);
  fill.push_back(2);
  fill.push_back(3);
  fill.push_back(0);
  fill.push_back(1);
  fill.push_back(0);
  _reciepeList.push_back(fill);
  fill.clear();
  fill.push_back(0);
  fill.push_back(2);
  fill.push_back(2);
  fill.push_back(2);
  fill.push_back(2);
  fill.push_back(2);
  fill.push_back(1);
  _reciepeList.push_back(fill);

  _itemMap[FOOD] = "nourriture";
  _itemMap[LINEMATE] = "linemate";
  _itemMap[DERAUMERE] = "deraumere";
  _itemMap[SIBUR] = "sibur";
  _itemMap[MENDIANE] = "mendiane";
  _itemMap[PHIRAS] = "phiras";
  _itemMap[THYSTAME] = "thystame";

  _peopleRequired.push_back(1);
  _peopleRequired.push_back(2);
  _peopleRequired.push_back(2);
  _peopleRequired.push_back(4);
  _peopleRequired.push_back(4);
  _peopleRequired.push_back(6);
  _peopleRequired.push_back(6);

  _sendMsgMap["voir"] = VOIR;
  _sendMsgMap["broadcast death"] = CANNOT_FAIL;
  _sendMsgMap["broadcast help"] = CANNOT_FAIL;
  _sendMsgMap["broadcast stop helping"] = CANNOT_FAIL;
  _sendMsgMap["broadcast stop coming"] = CANNOT_FAIL;
  _sendMsgMap["brodcast up"] = CANNOT_FAIL;
  _sendMsgMap["broadcast birth"] = CANNOT_FAIL;
  _sendMsgMap["inventaire"] = INVENTAIRE;
  _sendMsgMap["connect_nbr"] = CONNECT_NBR;
  _sendMsgMap["avance"] = CANNOT_FAIL;
  _sendMsgMap["droite"] = CANNOT_FAIL;
  _sendMsgMap["gauche"] = CANNOT_FAIL;
  _sendMsgMap["prend"] = CAN_FAIL;
  _sendMsgMap["pose"] = CAN_FAIL;
  _sendMsgMap["expulse"] = CAN_FAIL;
  _sendMsgMap["incantation"] = CAN_FAIL;
  _sendMsgMap["fork"] = CANNOT_FAIL;

  _recvMsgMap[VOIR] = "([a-z]+),";
  _recvMsgMap[BIRTH] = "(birth)";
  _recvMsgMap[STOPHELPING] = "(stop helping)";
  _recvMsgMap[HELP] = "(help)";
  _recvMsgMap[STOPCOMING] = "(stop coming)";
  _recvMsgMap[INVENTAIRE] = "(nourriture [0-9]+)";
  _recvMsgMap[CANNOT_FAIL] = "(ok)";
  _recvMsgMap[CAN_FAIL] = "(ko)";
  _recvMsgMap[INCANTATION] = "(elevation en cours)";
  _recvMsgMap[DEATH] = "(mort)";
  _recvMsgMap[UP] = "(niveau actuel :)";
  _recvMsgMap[CONNECT_NBR] = "([0-9]+)";

  dir.push_back("avance");
  _dirTab.push_back(dir);
  dir.push_back("gauche");
  dir.push_back("avance");
  _dirTab.push_back(dir);
  dir.clear();
  dir.push_back("gauche");
  dir.push_back("avance");
  _dirTab.push_back(dir);
  dir.push_back("gauche");
  dir.push_back("avance");
  _dirTab.push_back(dir);
  dir.clear();
  dir.push_back("gauche");
  dir.push_back("gauche");
  dir.push_back("avance");
  _dirTab.push_back(dir);
  dir.clear();
  dir.push_back("droite");
  dir.push_back("avance");
  dir.push_back("droite");
  dir.push_back("avance");
  _dirTab.push_back(dir);
  dir.pop_back();
  dir.pop_back();
  _dirTab.push_back(dir);
  dir.clear();
  dir.push_back("avance");
  dir.push_back("droite");
  dir.push_back("avance");
  _dirTab.push_back(dir);
}

Correspondances::~Correspondances()
{

}

std::string				Correspondances::getItemName(e_itemtype const& item)
{
  return _itemMap[item];
}

e_itemtype				Correspondances::getItemFromString(std::string const& item)
{
  for (std::map<e_itemtype, std::string>::iterator it = _itemMap.begin(); it != _itemMap.end(); ++it)
    {
      if (it->second == item)
	return it->first;
    }
  return NONE;
}

bool					Correspondances::isReciepeFull(std::vector<unsigned int> const& reciepe, int _level)
{
  std::vector<unsigned int>::iterator	origIt = _reciepeList[_level - 1].begin();

  for (std::vector<unsigned int>::const_iterator testIt = reciepe.begin(); testIt != reciepe.end(); ++testIt)
    {
      if (testIt != reciepe.begin()
	  && *testIt < *origIt)
	return false;
      ++origIt;
    }
  return true;
}

bool					Correspondances::isInReciepe(std::vector<unsigned int> const& reciepe, unsigned int _level)
{
  std::vector<unsigned int>::iterator	origIt = _reciepeList[_level - 1].begin();

  for (std::vector<unsigned int>::const_iterator testIt = reciepe.begin(); testIt != reciepe.end(); ++testIt)
    {
      if (testIt != reciepe.begin()
	  && *testIt < *origIt)
	return false;
      ++origIt;
    }
  return true;
}

int					Correspondances::getNbrPeopleFromLevel(int level)
{
  return _peopleRequired[level - 1];
}

e_msgtype				Correspondances::getCommandFromString(std::string const& cmd)
{
  for (std::map<std::string, e_msgtype>::const_iterator it = _sendMsgMap.begin(); it != _sendMsgMap.end(); ++it)
    {
      if (cmd.find(it->first) == 0)
	return it->second;
    }
  return NOTHING;
}

unsigned int				Correspondances::getQuantityRequired(e_itemtype item, unsigned int lvl)
{
  return _reciepeList[lvl - 1][item];
}

e_msgtype				Correspondances::getToken(std::string const& cmd)
{
  std::smatch		m;

  for (std::map<e_msgtype, std::regex>::const_iterator it = _recvMsgMap.begin(); it != _recvMsgMap.end(); ++it)
    {
      if (std::regex_search(cmd, m, it->second))
	return it->first;
    }
  return NOTHING;
}

const std::vector<std::string>&		Correspondances::getDirTab(int const pos) const
{
  return _dirTab[pos];
}
