//
// Commands.cpp for zappy in /home/bouca-_d/rendu/Zappy/Graphic
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:19:12 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:19:14 2015 Dany Bouca Nova
//

#include "Commands.hh"

Commands::Commands(SafeQueue<Event>* safeEvents)
  : _safeEvents(safeEvents),
    _sizeXMap(-1),
    _sizeYMap(-1)
{
  _commandsMap[std::make_pair<std::string, int>("msz", 2)] = &Commands::mszCommand;
  _commandsMap[std::make_pair<std::string, int>("bct", 9)] = &Commands::bctCommand;
  _commandsMap[std::make_pair<std::string, int>("tna", 1)] = &Commands::tnaCommand;
  _commandsMap[std::make_pair<std::string, int>("pnw", 6)] = &Commands::pnwCommand;
  _commandsMap[std::make_pair<std::string, int>("ppo", 4)] = &Commands::ppoCommand;
  _commandsMap[std::make_pair<std::string, int>("plv", 2)] = &Commands::plvCommand;
  _commandsMap[std::make_pair<std::string, int>("pin", 10)] = &Commands::pinCommand;
  _commandsMap[std::make_pair<std::string, int>("pex", 1)] = &Commands::pexCommand;
  _commandsMap[std::make_pair<std::string, int>("pbc", 2)] = &Commands::pbcCommand;
  _commandsMap[std::make_pair<std::string, int>("pic", VARIABLE_ARGS)] = &Commands::picCommand;
  _commandsMap[std::make_pair<std::string, int>("pie", 3)] = &Commands::pieCommand;
  _commandsMap[std::make_pair<std::string, int>("pfk", 1)] = &Commands::pfkCommand;
  _commandsMap[std::make_pair<std::string, int>("pdr", 2)] = &Commands::pdrCommand;
  _commandsMap[std::make_pair<std::string, int>("pgt", 2)] = &Commands::pgtCommand;
  _commandsMap[std::make_pair<std::string, int>("pdi", 1)] = &Commands::pdiCommand;
  _commandsMap[std::make_pair<std::string, int>("enw", 4)] = &Commands::enwCommand;
  _commandsMap[std::make_pair<std::string, int>("eht", 1)] = &Commands::ehtCommand;
  _commandsMap[std::make_pair<std::string, int>("ebo", 1)] = &Commands::eboCommand;
  _commandsMap[std::make_pair<std::string, int>("edi", 1)] = &Commands::ediCommand;
  _commandsMap[std::make_pair<std::string, int>("sgt", 1)] = &Commands::sgtCommand;
  _commandsMap[std::make_pair<std::string, int>("seg", 1)] = &Commands::segCommand;
  _commandsMap[std::make_pair<std::string, int>("smg", 1)] = &Commands::smgCommand;
  _commandsMap[std::make_pair<std::string, int>("suc", 0)] = &Commands::sucCommand;
  _commandsMap[std::make_pair<std::string, int>("spb", 0)] = &Commands::spbCommand;
}

Commands::~Commands()
{
}

int				Commands::isValid(std::deque<std::string> *command)
{
  std::map<std::pair<std::string, int>, commandsPtr>::iterator	it;

  for (it = _commandsMap.begin(); it != _commandsMap.end(); ++it)
    {
      if (command->front() == it->first.first
	  && it->first.second != VARIABLE_ARGS
	  &&  static_cast<int>(command->size()) == it->first.second + 1)
	return (command->size() - 1);
      if (command->front() == it->first.first
	  && it->first.second == VARIABLE_ARGS)
	return (-1);
    }
  return (-2);
}

bool				Commands::parseSingleCommand(std::string const& args)
{
  int				sizeArg;

  _line.parseString(args);
  if ((sizeArg = isValid(_line.getCommand())) == -2)
    return (false);
  (this->*_commandsMap[std::make_pair<std::string, int>(_line.getCommand()->front(),
							sizeArg)])(_line.getCommand());
  return (true);
}

bool				Commands::parseAllCommands(std::string const& orders)
{
  size_t			pos = 0;
  size_t			found;

  while ((found = orders.find("\n", pos)) != std::string::npos)
    {
      if (!parseSingleCommand(orders.substr(pos, found - pos)))
	{
	  pos = found + 1;
	  continue ;
	}
      pos = found + 1;
    }
  return (true);
}

void			Commands::checkPosValidity(int x, int y)
{
  if (_sizeXMap < 0 || _sizeYMap < 0)
    throw ZappyError::PositionsError("Msz is not set properly");
  if (x >= _sizeXMap || x < 0
      || y >= _sizeYMap || y < 0)
    throw ZappyError::PositionsError("All positions must be between 0 and maxX or maxY (see Msz)");
}

void			Commands::checkOrientationValidity(int o)
{
  if (o < 1 || o > 4)
    throw ZappyError::OrientationError("Orientation must be between 1 and 4");
}

void			Commands::checkResourcesValidity(int resource, int nb)
{
  if (resource < 0 || resource > 6)
    throw ZappyError::ResourceError("Resource Type must be between 0 and 6");
  if (nb < 0)
    throw ZappyError::ResourceError("Resource Number must be positive");
}

void			Commands::mszCommand(std::deque<std::string>* command)
{
  Event			event("msz");

  _sizeXMap = std::atoi((*command)[1].c_str());
  _sizeYMap = std::atoi((*command)[2].c_str());
  checkPosValidity(0, 0);
  event.setXY(std::atoi((*command)[1].c_str()), std::atoi((*command)[2].c_str()));
  _safeEvents->push(event);
}

void			Commands::bctCommand(std::deque<std::string>* command)
{
  Event			event("bct");

  checkPosValidity(std::atoi((*command)[1].c_str()), std::atoi((*command)[2].c_str()));
  event.setXY(std::atoi((*command)[1].c_str()), std::atoi((*command)[2].c_str()));
  for (unsigned int i = 3; i < command->size(); ++i)
    {
      checkResourcesValidity(i - 3, std::atoi((*command)[i].c_str()));
      event.setQuantities(static_cast<e_ressource>(i - 3), std::atoi((*command)[i].c_str()));
    }
  _safeEvents->push(event);
}

void			Commands::tnaCommand(std::deque<std::string>* command)
{
  Event			event("tna");

  event.setTeamName((*command)[1]);
  _safeEvents->push(event);
}

void			Commands::pnwCommand(std::deque<std::string>* command)
{
  Event			event("pnw");

  event.setNbPlayer(std::atoi((*command)[1].c_str()));
  checkPosValidity(std::atoi((*command)[2].c_str()), std::atoi((*command)[3].c_str()));
  event.setXY(std::atoi((*command)[2].c_str()), std::atoi((*command)[3].c_str()));
  checkOrientationValidity(std::atoi((*command)[4].c_str()));
  event.setOrientation(static_cast<e_orientation>(std::atoi((*command)[4].c_str())));
  event.setLvl(std::atoi((*command)[5].c_str()));
  event.setTeamName((*command)[6]);
  _safeEvents->push(event);
}

void			Commands::ppoCommand(std::deque<std::string>* command)
{
  Event			event("ppo");

  event.setNbPlayer(std::atoi((*command)[1].c_str()));
  checkPosValidity(std::atoi((*command)[2].c_str()), std::atoi((*command)[3].c_str()));
  event.setXY(std::atoi((*command)[2].c_str()), std::atoi((*command)[3].c_str()));
  checkOrientationValidity(std::atoi((*command)[4].c_str()));
  event.setOrientation(static_cast<e_orientation>(std::atoi((*command)[4].c_str())));
  _safeEvents->push(event);
}

void			Commands::plvCommand(std::deque<std::string>* command)
{
  Event			event("plv");

  event.setNbPlayer(std::atoi((*command)[1].c_str()));
  event.setLvl(std::atoi((*command)[2].c_str()));
  _safeEvents->push(event);
}

void			Commands::pinCommand(std::deque<std::string>* command)
{
  Event			event("pin");

  event.setNbPlayer(std::atoi((*command)[1].c_str()));
  checkPosValidity(std::atoi((*command)[2].c_str()), std::atoi((*command)[3].c_str()));
  event.setXY(std::atoi((*command)[2].c_str()), std::atoi((*command)[3].c_str()));
  for (unsigned int i = 4; i < command->size(); ++i)
    {
      checkResourcesValidity(i - 4, std::atoi((*command)[i].c_str()));
      event.setQuantities(static_cast<e_ressource>(i - 4), std::atoi((*command)[i].c_str()));
    }
  _safeEvents->push(event);
}

void			Commands::pexCommand(std::deque<std::string>* command)
{
  Event			event("pex");

  event.setNbPlayer(std::atoi((*command)[1].c_str()));
  _safeEvents->push(event);
}

void			Commands::pbcCommand(std::deque<std::string>* command)
{
  Event			event("pbc");

  event.setNbPlayer(std::atoi((*command)[1].c_str()));
  event.setMessageBroadcast((*command)[2]);
  _safeEvents->push(event);
}

void			Commands::picCommand(std::deque<std::string>* command)
{
  Event			event("pic");

  checkPosValidity(std::atoi((*command)[1].c_str()), std::atoi((*command)[2].c_str()));
  event.setXY(std::atoi((*command)[1].c_str()), std::atoi((*command)[2].c_str()));
  event.setLvl(std::atoi((*command)[3].c_str()));
  event.setNbPlayer(std::atoi((*command)[4].c_str()));
  for (unsigned int i = 5; i < command->size(); ++i)
    event.setNbPlayerIncant(std::atoi((*command)[i].c_str()));
  _safeEvents->push(event);
}

void			Commands::pieCommand(std::deque<std::string>* command)
{
  Event			event("pie");

  checkPosValidity(std::atoi((*command)[1].c_str()), std::atoi((*command)[2].c_str()));
  event.setXY(std::atoi((*command)[1].c_str()), std::atoi((*command)[2].c_str()));
  event.setResultIncant(static_cast<bool>(std::atoi((*command)[3].c_str())));
  _safeEvents->push(event);
}

void			Commands::pfkCommand(std::deque<std::string>* command)
{
  Event			event("pfk");

  event.setNbPlayer(std::atoi((*command)[1].c_str()));
  _safeEvents->push(event);
}

void			Commands::pdrCommand(std::deque<std::string>* command)
{
  Event			event("pdr");

  event.setNbPlayer(std::atoi((*command)[1].c_str()));
  checkResourcesValidity(std::atoi((*command)[2].c_str()), 1);
  event.setRessourceTaken(static_cast<e_ressource>(std::atoi((*command)[2].c_str())));
  _safeEvents->push(event);
}

void			Commands::pgtCommand(std::deque<std::string>* command)
{
  Event			event("pgt");

  event.setNbPlayer(std::atoi((*command)[1].c_str()));
  checkResourcesValidity(std::atoi((*command)[2].c_str()), 1);
  event.setRessourceTaken(static_cast<e_ressource>(std::atoi((*command)[2].c_str())));
  _safeEvents->push(event);
}

void			Commands::pdiCommand(std::deque<std::string>* command)
{
  Event			event("pdi");

  event.setNbPlayer(std::atoi((*command)[1].c_str()));
  _safeEvents->push(event);
}

void			Commands::enwCommand(std::deque<std::string>* command)
{
  Event			event("enw");

  event.setNbEgg(std::atoi((*command)[1].c_str()));
  event.setNbPlayer(std::atoi((*command)[2].c_str()));
  checkPosValidity(std::atoi((*command)[3].c_str()), std::atoi((*command)[4].c_str()));
  event.setXY(std::atoi((*command)[3].c_str()), std::atoi((*command)[4].c_str()));
  _safeEvents->push(event);
}

void			Commands::ehtCommand(std::deque<std::string>* command)
{
  Event			event("eht");

  event.setNbEgg(std::atoi((*command)[1].c_str()));
  _safeEvents->push(event);
}

void			Commands::eboCommand(std::deque<std::string>* command)
{
  Event			event("ebo");

  event.setNbEgg(std::atoi((*command)[1].c_str()));
  _safeEvents->push(event);
}

void			Commands::ediCommand(std::deque<std::string>* command)
{
  Event			event("edi");

  event.setNbEgg(std::atoi((*command)[1].c_str()));
  _safeEvents->push(event);
}

void			Commands::sgtCommand(std::deque<std::string>* command)
{
  Event			event("sgt");

  event.setTime(std::atoi((*command)[1].c_str()));
  _safeEvents->push(event);
}

void			Commands::segCommand(std::deque<std::string>* command)
{
  Event			event("seg");

  event.setTeamName((*command)[1]);
  _safeEvents->push(event);
}

void			Commands::smgCommand(std::deque<std::string>* command)
{
  Event			event("smg");

  event.setMessageBroadcast((*command)[1]);
  _safeEvents->push(event);
}

void			Commands::sucCommand(std::deque<std::string>*)
{
  Event			event("suc");

  _safeEvents->push(event);
}

void			Commands::spbCommand(std::deque<std::string>*)
{
  Event			event("sbp");

  _safeEvents->push(event);
}
