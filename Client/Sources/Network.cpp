//
// Network.cpp for zappy in /home/bouca-_d/rendu/Zappy/Client
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:01:36 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:01:37 2015 Dany Bouca Nova
//

#include "Network.hh"

Network::Network(std::deque<std::string>  *send, std::deque<std::string> *recv, Correspondances const& data)
  : _hostname("localhost"), _teamname(""), _port(0), _toSend(send), _toReceive(recv), _database(data)
{
}

Network::~Network()
{
  endConnection();
}

bool				Network::initConnection()
{
  struct sockaddr_in            s_in;
  struct hostent                *host;

  if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    throw ZappyError::ConnectionFailure(errno, "Could not create socket");
  else if (!(host = gethostbyname(_hostname.c_str())))
    throw ZappyError::ConnectionFailure(errno, "Could not get resolve host '" + _hostname);
  s_in.sin_addr = *(struct in_addr *)host->h_addr;
  s_in.sin_port = htons(_port);
  s_in.sin_family = AF_INET;
  if (connect(_socket, (struct sockaddr *)&s_in, sizeof(struct sockaddr)) == -1)
    throw ZappyError::ConnectionFailure(errno, "Could not process connection to server");
  return true;
}

void				Network::endConnection()
{
  close(_socket);
}

void				Network::setPort(int value)
{
  _port = value;
}

bool				Network::checkArgs()
{
  if (_teamname == "" || _port == 0)
    {
      std::cerr << "A team name and a port must at least be given in parameters" << std::endl;
      return false;
    }
  return true;
}

bool				Network::beginCommunication()
{
  char				buff[512];
  std::string		name = _teamname + '\n';

  memset(buff, 0, 512);
  recv(_socket, buff, 10, 0);
  std::cout << buff;
  send(_socket, name.c_str(), name.size(), 0);
  memset(buff, 0, 512);
  recv(_socket, buff, 512, 0);
  std::cout << buff;
  return true;
}

void				Network::setHostname(std::string const& value)
{
  _hostname = value;
}

void				Network::setTeamname(std::string const& value)
{
  _teamname = value;
}

void				Network::setBitfield()
{
  FD_ZERO(&_bitfield);
  FD_SET(_socket, &_bitfield);
}

bool				Network::sendRequest()
{
  std::string			ret;

  while (_toSend->size())
    {
      ret = _toSend->back();
      _toSend->pop_back();
      ret += '\n';
      send(_socket, ret.c_str(), ret.size(), 0);
    }
  return true;
}

void				Network::tokenize(std::string& buff)
{
  std::string			add;

  add = std::to_string((int)_database.getToken(buff));
  if (add.size() < 2)
    add.insert(0, 1, '0');
  add.append(1, ' ');
  add.append(buff);
  buff = add;
}


void				Network::getResponse()
{
  std::string			buff;
  std::string			response;
  char				tmp[512];
  size_t			pos = 0;
  size_t			begin = 0;

  memset(tmp, 0, 512);
  while (recv(_socket, tmp, 510, 0))
    {
      buff += tmp;
      if (buff.find("\n") != std::string::npos)
	{
	  while ((pos = buff.find("\n", begin)) != std::string::npos)
	    {
	      response = buff.substr(begin, pos - begin);
	      response[response.size()] = 0;
	      tokenize(response);
	      _toReceive->push_front(response);
	      begin = pos + 1;
	    }
	  break;
	}
      memset(tmp, 0, 512);
    }
}

bool				Network::selectFds()
{
  _timeout.tv_sec = 1;
  _timeout.tv_usec = 0;
  if (select(_socket + 1, &_bitfield, NULL, NULL, &_timeout) == -1)
    throw ZappyError::SelectFailure(errno, "Select failure\n");
  if (FD_ISSET(_socket, &_bitfield))
    getResponse();
  return true;
}
