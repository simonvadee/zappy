//
// Network.hh for zappy in /home/bouca-_d/rendu/Zappy/Graphic
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:18:00 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:18:04 2015 Dany Bouca Nova
//

#ifndef NETWORK_HH_
# define NETWORK_HH_

# define PROTOCOL	(char *)"TCP"
# define FAIL		-1
# define USAGE		(char *)"./graphic [IP] [PORT]"
# define BUFF_SIZE	4096

# include <pthread.h>
# include <cstdlib>
# include <string>
# include <iostream>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <unistd.h>
# include "Exceptions.hpp"
# include "Commands.hh"
# include "GetLine.hh"
# include "Requests.hh"
# include "SafeQueue.hh"
# include "Event.hh"

class				Network
{
private :
  int				_port;
  int				_socket;
  fd_set			_rfds;
  std::string			_ip;
  struct protoent*		_pe;
  struct sockaddr_in		_sockIn;
  struct timeval		_timeOut;
  GetLine			_entryGetter;
  Requests			_request;
  SafeQueue<Event>*		_safeEvents;
  Commands			_commands;
  std::string			_remain;

public :
  Network(int, char**, SafeQueue<Event>*);
  ~Network();
  void		initConnection();
  void		run();

private :
  bool		checkOptions(int ac, char** av);
  void		sendServer(std::string const&);
  void		receiveFromServer();
  void		parseEntry(std::string&);
  void		checkTime();
};

#endif /* !NETWORK_HH_ */
