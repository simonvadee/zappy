//
// Network.cpp for zappy in /home/bouca-_d/rendu/Zappy/Graphic
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:19:52 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:19:53 2015 Dany Bouca Nova
//

#include "Network.hh"

Network::Network(int ac, char** av, SafeQueue<Event>* safeEvents)
  : _entryGetter(std::cin),
    _safeEvents(safeEvents),
    _commands(safeEvents),
    _remain("")
{
  if (!checkOptions(ac, av))
    throw ZappyError::ArgumentsError(USAGE);
  _timeOut.tv_sec = 3;
  _timeOut.tv_usec = 0;
}

Network::~Network()
{
}

bool		Network::checkOptions(int ac, char** av)
{
  if (ac != 3)
    return false;
  _ip = av[1];
  _port = std::atoi(av[2]);
  return true;
}

void		Network::run()
{
  receiveFromServer();
}

void		Network::parseEntry(std::string &entry)
{
  size_t	pos;

  if ((pos = entry.rfind("\n")) != entry.size() - 1)
    {
      _remain = entry.substr(pos + 1, entry.size());
      entry = entry.substr(0, pos);
    }
}

void			Network::checkTime()
{
  unsigned int		time;
  std::stringstream	ss;

  if ((time =_safeEvents->getTimeToSet()) != 0)
    {
      _safeEvents->setTimeToSet(0);
      ss << "sst " << time << '\n';
      sendServer(ss.str());
    }
}

void		Network::receiveFromServer()
{
  char		buf[BUFF_SIZE];
  std::string	entry;

  _safeEvents->setDrawing(true);
  while (_safeEvents->getDrawing())
    {
      FD_ZERO(&_rfds);
      FD_SET(_socket, &_rfds);
      if (select(_socket + 1, &_rfds, NULL, NULL, &_timeOut) == FAIL)
  	throw ZappyError::SystemError(errno, "Error : Select");
      if (FD_ISSET(_socket, &_rfds))
  	{
  	  bzero(buf, BUFF_SIZE);
	  while (strchr(buf, 10) == NULL)
	    if (recv(_socket, buf, BUFF_SIZE - 1, 0) <= 0)
	      throw ZappyError::SystemError(errno, "Error : Connection Lost");
	  entry = _remain + buf;
	  _remain.clear();
	  parseEntry(entry);
	  _commands.parseAllCommands(entry);
	}
      checkTime();
    }
}

void		Network::initConnection()
{
  std::string	error;

  if (!(_pe = getprotobyname(PROTOCOL)))
    throw ZappyError::SystemError(errno, "Error : GetProto");
  if ((_socket = socket(AF_INET, SOCK_STREAM, _pe->p_proto)) == FAIL)
    throw ZappyError::SystemError(errno, "Error : Socket");
  _sockIn.sin_family = AF_INET;
  _sockIn.sin_port = htons(_port);
  _sockIn.sin_addr.s_addr = inet_addr(_ip.c_str());
  if (connect(_socket, (const struct sockaddr *)&_sockIn, sizeof(_sockIn)) == FAIL)
    {
      if (close(_socket) == FAIL)
	throw ZappyError::SystemError(errno, "Error : Close");
      throw ZappyError::SystemError(errno, "Error : Connect");
    }
  _ip = inet_ntoa(_sockIn.sin_addr);
  sendServer("GRAPHIC\n");
}

void		Network::sendServer(std::string const& response)
{
  if (send(_socket, response.c_str(), response.size(), 0) <= 0)
    throw ZappyError::SystemError(errno, "Error : Send");
}
