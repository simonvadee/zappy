//
// ZappyIa.cpp for zappy in /home/bouca-_d/rendu/Zappy/Client
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:01:45 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:02:36 2015 Dany Bouca Nova
//

#include "ZappyIA.hh"

ZappyIA::ZappyIA(std::deque<std::string> *toSend, std::deque<std::string> *toReceive, Network *network, Correspondances const& table)
  : _level(1),
    _state(CHILLING),
    _oldState(CHILLING),
    _voir(""),
    _network(network),
    _food(0),
    _count(0),
    _toSend(toSend),
    _toReceive(toReceive),
    _table(table)
{
  _randomDir.push_back("");
  _randomDir.push_back("droite");
  _randomDir.push_back("gauche");
  _inventory.push_back(10);
  _inventory.push_back(0);
  _inventory.push_back(0);
  _inventory.push_back(0);
  _inventory.push_back(0);
  _inventory.push_back(0);
  _inventory.push_back(0);

  _objectsDown.push_back(0);
  _objectsDown.push_back(0);
  _objectsDown.push_back(0);
  _objectsDown.push_back(0);
  _objectsDown.push_back(0);
  _objectsDown.push_back(0);
  _objectsDown.push_back(0);
  _objectsDown.push_back(0);
}

ZappyIA::~ZappyIA()
{
}

bool				ZappyIA::init()
{
  try
    {
      _network->initConnection();
    }
  catch (ZappyError::ConnectionFailure e)
    {
      std::cerr << e.what() << std::endl;
      return false;
    }
  return (_network->beginCommunication());
}

bool				ZappyIA::isStateHungry()
{
  return ((_state == COMING && !enoughFood(ENOUGH_FOOD_COMING))
	  || ((_state == LEADING || _state == HELPING || _state == INCANTATING) && !enoughFood(ENOUGH_FOOD_INCANT))
    	  || (_state == CHILLING && !enoughFood(ENOUGH_FOOD)));
}

bool				ZappyIA::trySelect()
{
  try
    {
      _network->selectFds();
    }
  catch (ZappyError::SelectFailure e)
    {
      std::cerr << e.what() << std::endl;
      return false;
    }
  return true;
}

void				ZappyIA::tellMatesToLeave()
{
  if (_state == LEADING || _state == INCANTATING || _state == HELPING)
    {
      pushCommand("broadcast stop helping " + std::to_string(_level));
      if (_state == LEADING)
	pushCommand("broadcast stop coming " + std::to_string(_level));
    }
}

void				ZappyIA::careForHelp()
{
  std::string			help;

  if ((help = refreshMsg(HELP)) != ""
      && (help[help.size() - 1] - 48) == static_cast<char>(_level)
      && enoughFood(ENOUGH_FOOD_COMING))
    _state = COMING;
}

void				ZappyIA::run()
{
  e_itemtype			item;

  if (!init())
    return ;
  pushCommand("fork");
  while (_level < 8)
    {
      _network->setBitfield();
      if (!trySelect())
	return ;
      parseVoir(refreshMsg(VOIR));
      parseInventory(refreshMsg(INVENTAIRE));
      _network->sendRequest();
      if (!informPeople())
	return ;
      if (isStateHungry())
      	{
	  tellMatesToLeave();
	  _state = CHILLING;
      	  seekFood();
	  careForHelp();
      	  continue ;
      	}
      if (manageBroadcasts())
    	continue ;
      if (_state == CHILLING
	  && (item = isItemNeeded(isThereItemHere())) != NONE
	  && pushCommand("prend " + _table.getItemName(item)))
	continue ;
      if (!tryToLevelUp())
    	seekStone();
    }
}

unsigned int			ZappyIA::getQuantity(std::string const& stock)
{
  std::string			ret;

  if (stock.find(' ') == std::string::npos)
    return 0;
  ret = stock.substr(0, stock.find(' '));
  return std::atoi(stock.substr(stock.find(' ') + 1).c_str());
}

void				ZappyIA::checkState()
{
  if (_oldState == INCANTATING
      && _state == INCANTATING)
    {
      _state = CHILLING;
      pushCommand("broadcast stop coming " + std::to_string(_level));
      pushCommand("broadcast stop helping " + std::to_string(_level));
    }
  _oldState = _state;
}

void				ZappyIA::parseInventory(std::string const& inventaire)
{
  std::string			parse;
  unsigned int			idx = 0;
  size_t			begin = 0;

  unsigned int			tmp;

  if (inventaire == "")
    {
      if (alreadySent("inventaire"))
	{
	  if (_count++ > 25)
	    {
	      removeFromSent(INVENTAIRE);
	      pushCommand("inventaire");
	      _count = 0;
	    }
	}
      else
	{
	  pushCommand("inventaire");
	  _count = 0;
	}
      return ;
    }
  for (size_t pos = inventaire.find(',', 0); pos != std::string::npos; pos = (inventaire.find(',', pos + 1) == std::string::npos ? inventaire.find('}', pos + 1) : inventaire.find(',', pos + 1)))
    {
      parse = inventaire.substr(begin, pos - begin);
      if (parse[0] == '{')
	parse.erase(0, 1);
      if (idx == FOOD && !(tmp = getQuantity(parse)))
	break ;
      _inventory[idx++] = getQuantity(parse);
      begin = pos + 1;
    }
  std::cout << "STATE = " << _state << ", food = " << _inventory[FOOD] << ", level = " << _level << std::endl;
  checkState();
}

void				ZappyIA::checkIfMessageReturning()
{
  if (_food == 0 && _inventory[0] != 0)
    _food = _inventory[0];
  else if (_inventory[0] != 0 && _food == _inventory[0] + 3)
    {
      removeFromSent(VOIR);
      pushCommand("voir");
      _food = 0;
    }
}

void				ZappyIA::parseVoir(std::string const& voir)
{
  if (voir == "")
    {
      if (alreadySent("voir"))
	checkIfMessageReturning();
      else
	{
	  _food = 0;
	 pushCommand("voir");
	}
    }
  _voir = voir;
  emptyObjectsDown();
  if (!_voir.empty())
    createObjectsDown(_voir.substr(0, _voir.find(",")));
}

bool				ZappyIA::pushCommand(std::string const& command)
{
  if (_toSend->size() >= 10 || alreadySent(command))
    return false;
  _toSend->push_front(command);
  _sent.push_back(command);
  return true;
}

bool				ZappyIA::isInQueue(e_msgtype const command)
{
  for (std::deque<std::string>::iterator it = _toReceive->begin(); it != _toReceive->end(); ++it)
    if (std::atoi(it->substr(0, 2).c_str()) == command)
      return true;
  return false;
}

const std::string		ZappyIA::getMsgFromCode(e_msgtype const command)
{
  std::string			ret;

  for (std::deque<std::string>::iterator it = _toReceive->begin(); it != _toReceive->end(); ++it)
    {
      if (std::atoi(it->substr(0, 2).c_str()) == command)
	{
	  it->erase(0, 3);
	  ret = *it;
	  _toReceive->erase(it);
	  return ret;
	}
    }
  return "";
}

const std::string		ZappyIA::getReturn(e_msgtype const command)
{
  std::string			ret;

  ret = getMsgFromCode(command);
  if (ret != "")
    {
      if (command != HELP && command != STOPHELPING && command != STOPCOMING
	  && !removeFromSent(_table.getToken(ret)))
	lookForSuccess();
    }
  return ret;
}

bool				ZappyIA::alreadySent(std::string const& command)
{
  for (std::deque<std::string>::iterator it = _sent.begin(); it != _sent.end(); ++it)
    {
      if (it->find(command) != std::string::npos)
	return true;
    }
  return false;
}

void				ZappyIA::randomMove()
{
  std::string			direction;

  for (unsigned int i = 0; i != _level + 1; ++i)
    {
      direction = _randomDir[rand() % 3];
      if (direction != "")
	pushCommand(direction);
      pushCommand("avance");
    }
}

void				ZappyIA::goHelp(std::string const& msg)
{
  int				pos;
  std::vector<std::string>	dir;

  if (msg.size() <= 8)
    return ;
  else if (!(pos = std::atoi(msg.substr(8, 1).c_str())))
    return ;
  dir = _table.getDirTab(pos - 1);
  for (std::vector<std::string>::iterator it = dir.begin(); it != dir.end(); ++it)
    pushCommand(*it);
}

void				ZappyIA::goFind(unsigned int const dest)
{
  unsigned int			pos = 0;
  unsigned int			stage = 0;
  std::string			dir;

  if (dest == 0)
    return ;
  while ((pos + stage) < dest)
    {
      if (!pushCommand("avance"))
	return ;
      ++stage;
      pos += (stage * 2);
    }
  if (pos == dest)
    return ;
  dir = (pos > dest ? "gauche" : "droite");
  if (!pushCommand(dir))
    return ;
  while (pos != dest)
    {
      if (!pushCommand("avance"))
	return ;
      pos = (dir == "gauche" ? pos - 1 : pos + 1);
    }
}

bool				ZappyIA::lookForSuccess()
{
  for (std::deque<std::string>::iterator it = _sent.begin(); it != _sent.end(); ++it)
    {
      if (_table.getCommandFromString(*it) == CAN_FAIL)
  	{
	  _sent.erase(it);
	  return true;
  	}
    }
  return false;
}

bool				ZappyIA::removeFromSent(e_msgtype const msg)
{
  for (std::deque<std::string>::iterator it = _sent.begin(); it != _sent.end(); ++it)
    {
      if (_table.getCommandFromString(*it) == msg)
  	{
  	  _sent.erase(it);
	  return true;
  	}
    }
  return false;
}

bool				ZappyIA::informPeople()
{
  while (getReturn(CANNOT_FAIL) != ""
	 && getReturn(CAN_FAIL) != "");
  if (getReturn(CONNECT_NBR) != "")
    removeFromSent(INVENTAIRE);
  if (getReturn(INCANTATION) != "")
    {
      std::cout << "received : elevation en cours" << std::endl;
      if (_state == COMING && !alreadySent("avance"))
      	_state = HELPING;
    }
  if (getReturn(UP) != "")
    {
      ++_level;
      pushCommand("fork");
      std::cout << "I just UP LEVEL " << _level << std::endl;
      _state = CHILLING;
    }
  if (getReturn(DEATH) != "")
    return false ;
  return true;
}

bool				ZappyIA::manageHelp(std::string const& help)
{
  if ((help[help.size() - 1] - 48) == static_cast<char>(_level))
    {
      if (help.size() > 8 && help[8] == 48)
	_state = HELPING;
      else
	{
	  _state = COMING;
	  if (!alreadySent("avance")
	      && !alreadySent("gauche")
	      && !alreadySent("droite"))
	    goHelp(help);
	}
      return true;
    }
  return false;
}

const std::string		ZappyIA::refreshMsg(e_msgtype msg)
{
  std::string			ret = "";
  std::string			tmp;

  ret = getReturn(msg);
  while (getReturn(msg) != "");
  return ret;
}

bool				ZappyIA::manageBroadcasts()
{
  std::string			help;

  if ((((_state == COMING && (help = refreshMsg(STOPCOMING)) != ""))
       || ((_state == HELPING || _state == LEADING) && (help = refreshMsg(STOPHELPING)) != ""))
      && ((help[help.size() - 1] - 48) == static_cast<char>(_level)))
    {
      if (help.size() > 8 && help[8] != 48)
	{
	  _state = CHILLING;
	  return true;
	}
    }
  if (_state != INCANTATING && _state != HELPING && _state != LEADING
      && (help = refreshMsg(HELP)) != "")
    return manageHelp(help);
  return _state == HELPING || _state == INCANTATING || _state == COMING;
}

bool				ZappyIA::enoughFood(unsigned int quantity)
{
  return (_inventory[FOOD] > quantity);
}

void				ZappyIA::seekFood()
{
  unsigned int			position = 0;
  size_t			begin = 2;
  std::string			parse;

  if (_voir == "")
    return ;
  for (size_t pos = _voir.find(',', 0); pos != std::string::npos; pos = (_voir.find(',', pos + 1) == std::string::npos ? _voir.find('}', pos + 1) : _voir.find(',', pos + 1)))
    {
      parse = _voir.substr(begin, pos - begin);
      if (parse.find("nourriture") != std::string::npos)
	{
	  goFind(position);
	  pushCommand("prend nourriture");
	  return ;
	}
      begin = pos + 1;
      ++position;
    }
  randomMove();
}

void				ZappyIA::seekStone()
{
  unsigned int			position = 0;
  size_t			begin = 2;
  std::string			parse;

  if (_voir == "")
    return ;
  for (size_t pos = _voir.find(',', 0); pos != std::string::npos; pos = (_voir.find(',', pos + 1) == std::string::npos ? _voir.find('}', pos + 1) : _voir.find(',', pos + 1)))
    {
      parse = _voir.substr(begin, pos - begin);
      parse+= ' ';
      if (stoneINeedIn(position, parse))
	return ;
      begin = pos + 1;
      ++position;
    }
  randomMove();
}

bool				ZappyIA::stoneINeedIn(unsigned int const position, std::string& parse)
{
  std::string			stone;
  size_t			begin = 0;

  if (parse[0] == ' ')
    parse.erase(0, 1);
  for (size_t pos = parse.find(' ', 0); pos != std::string::npos; pos = parse.find(' ', pos + 1))
    {
      stone = parse.substr(begin, pos - begin);
      if (stone != "joueur"
	  && stone != "nourriture"
	  && _table.getQuantityRequired(_table.getItemFromString(stone), _level) >
	  _inventory[_table.getItemFromString(stone)])
	{
	  goFind(position);
	  pushCommand("prend " + stone);
	  return true;
	}
      begin = pos + 1;
    }
  return false;
}

std::vector<e_itemtype>		ZappyIA::isThereItemHere()
{
  std::vector<e_itemtype>		ret;
  std::string				square;
  std::string				parse;
  size_t				wordBegin = 0;

  if (_voir == "" || _voir.find(',') == std::string::npos)
    return ret;
  square = _voir.substr(2, _voir.find(',') - 1);
  for (size_t pos = square.find(' ', 0); pos != std::string::npos; pos = square.find(' ', pos + 1))
    {
      parse = square.substr(wordBegin, pos - wordBegin);
      if (_table.getItemFromString(parse) != NONE)
	ret.push_back(_table.getItemFromString(parse));
      wordBegin = pos + 1;
    }
  return ret;
}

e_itemtype			ZappyIA::isItemNeeded(std::vector<e_itemtype> item)
{
  for (std::vector<e_itemtype>::iterator it = item.begin(); it != item.end(); ++it)
    {
      if ((*it == FOOD && !enoughFood(ENOUGH_FOOD))
      	  || (*it != FOOD && _table.getQuantityRequired(*it, _level) > _inventory[*it]))
	return *it;
    }
  return NONE;
}

bool				ZappyIA::isInventoryFull()
{
  return _table.isReciepeFull(_inventory, _level);
}

int				ZappyIA::peopleOnMySquare()
{
  int				count;
  std::string			parse;

  count = 0;
  if (_voir == "" || _voir.find(',') == std::string::npos)
    return (1);
  parse = _voir.substr(1, _voir.find(',') - 1);
  for (size_t pos = parse.find("joueur", 0); pos != std::string::npos; pos = parse.find("joueur", pos + 1))
    ++count;
  return (count);
}

const std::string		ZappyIA::itemInStock(std::string const& stock)
{
  std::string			ret;
  int				amount;

  if (stock.find(' ') == std::string::npos)
    return "";
  ret = stock.substr(0, stock.find(' '));
  if (ret == "nourriture")
    return "";
  amount = std::atoi(stock.substr(stock.find(' ') + 1).c_str());
  if (amount > 0)
    return ret;
  else
    return "";
}

bool				ZappyIA::grabSupItems()
{
  for (int i = 1; i < 7; ++i)
    {
      if (_objectsDown[i] > _table.getQuantityRequired(static_cast<e_itemtype>(i), _level))
	{
	  pushCommand("prend " + _table.getItemName(static_cast<e_itemtype>(i)));
	  return false;
	}
    }
  return true;
}

bool				ZappyIA::dropNeededItems()
{
  for (int i = 1; i < 7; ++i)
    {
      if (_objectsDown[i] < _table.getQuantityRequired(static_cast<e_itemtype>(i), _level))
	{
	  pushCommand("pose " + _table.getItemName(static_cast<e_itemtype>(i)));
	  return false;
	}
    }
  return true;
}

bool				ZappyIA::validObjectsDown()
{
  return _objectsDown[VALID];
}

bool				ZappyIA::makeReciepe()
{
  std::cout << "MAKE RECIEPE !!!!!"  << std::endl;
  return (validObjectsDown() && grabSupItems() && dropNeededItems());
}

bool				ZappyIA::enoughPeopleForFood(float p)
{
  return (enoughFood(static_cast<int>(static_cast<float>(ENOUGH_FOOD) * (1 - p))));
}

bool				ZappyIA::handleCallPeople(std::string const& help)
{
  if (!enoughPeopleForFood(static_cast<float>(peopleOnMySquare())
  				   / static_cast<float>(_table.getNbrPeopleFromLevel(_level))))
    {
      _state = CHILLING;
      pushCommand("broadcast stop coming " + std::to_string(_level));
      pushCommand("broadcast stop helping " + std::to_string(_level));
      return true;
    }
  pushCommand(help);
  return true;
}

bool				ZappyIA::tryToLevelUp()
{
  std::string			help = "broadcast help " + std::to_string(_level);

  if (((_state == LEADING) || (_state == CHILLING && isInventoryFull()))
      && enoughFood(ENOUGH_FOOD_INCANT)
      && _voir != "")
    {
      _state = LEADING;
      if (peopleOnMySquare() < _table.getNbrPeopleFromLevel(_level))
	return (handleCallPeople(help));
      if (_level >= 2)
	pushCommand("broadcast stop coming " + std::to_string(_level));
      if (peopleOnMySquare() > _table.getNbrPeopleFromLevel(_level))
     	{
	  pushCommand("broadcast stop helping " + std::to_string(_level));
	  _state = CHILLING;
	  randomMove();
	  return true;
	}
      else
	{
	  if (makeReciepe()
	      && !alreadySent("incantation"))
	    {
	      _state = INCANTATING;
	      pushCommand("incantation");
	    }
	}
      return true;
    }
  return _state == COMING;
}

void				ZappyIA::createObjectsDown(std::string const& toParse)
{
  size_t			pos = 0;
  size_t			lastPos = 2;
  e_itemtype			tmp;

  if (toParse[0] != '{')
    {
      _voir = "";
      return ;
    }
    while ((pos = toParse.find(" ", lastPos)) != std::string::npos)
    {
      if ((tmp = _table.getItemFromString(toParse.substr(lastPos, pos - lastPos))) != NONE)
	_objectsDown[tmp] += 1;
      lastPos = pos + 1;
    }
  if ((tmp = _table.getItemFromString(toParse.substr(lastPos, pos - lastPos))) != NONE)
    _objectsDown[tmp] += 1;
  _objectsDown[VALID] = 1;
}

void				ZappyIA::emptyObjectsDown()
{
  std::vector<unsigned int>::iterator	it;

  for (it = _objectsDown.begin(); it != _objectsDown.end(); ++it)
    *it = 0;
}
