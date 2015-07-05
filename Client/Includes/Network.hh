//
// Network.hh for zappy in /home/bouca-_d/rendu/Zappy/Client
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:01:01 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:02:56 2015 Dany Bouca Nova
//

#ifndef NETWORK_HH_
# define NETWORK_HH_

# include "INetwork.hh"
# include "Correspondances.hh"

class				Network : public INetwork {

public:
  Network(std::deque<std::string> *send, std::deque<std::string> *recv, Correspondances const& data);
  ~Network();

  void				setHostname(std::string const& value);
  void				setTeamname(std::string const& value);
  void				setPort(int value);
  bool				checkArgs();

public:

  bool				initConnection();
  void				endConnection();

  bool				beginCommunication();
  void				setBitfield();
  bool				sendRequest();
  void				getResponse();
  bool				selectFds();

  void				tokenize(std::string& buff);
private:

  struct timeval		_timeout;
  fd_set			_bitfield;
  int				_socket;
  std::string			_hostname;
  std::string			_teamname;
  int				_port;
  std::deque<std::string>	*_toSend;
  std::deque<std::string>	*_toReceive;
  Correspondances		_database;
};

#endif /* !NETWORK_HH_ */
