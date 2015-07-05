//
// INetwork.hh for zappy in /home/bouca-_d/rendu/Zappy/Client
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:01:18 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:03:15 2015 Dany Bouca Nova
//

#ifndef INETWORK_HH_
# define INETWORK_HH_

# include <iostream>
# include <cstdlib>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/socket.h>
# include <sys/select.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <netdb.h>
# include "Exceptions.hpp"

class			INetwork {

public:
  virtual ~INetwork() {}

private:
  virtual bool		initConnection() = 0;
  virtual void		endConnection() = 0;

  virtual void		setPort(int value) = 0;
  virtual void		setHostname(std::string const& value) = 0;
  virtual void		setTeamname(std::string const& value) = 0;
  virtual bool		checkArgs() = 0;

  virtual void		setBitfield() = 0;
  virtual bool		sendRequest() = 0;
  virtual void		getResponse() = 0;
  virtual bool		selectFds() = 0;
};

#endif /* !INETWORK_HH_ */
