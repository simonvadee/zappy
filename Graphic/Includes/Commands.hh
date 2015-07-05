//
// Commands.hh for zappy in /home/bouca-_d/rendu/Zappy/Graphic
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:15:59 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:16:09 2015 Dany Bouca Nova
//

#ifndef COMMANDS_HH_
# define COMMANDS_HH_

# include <map>
# include <deque>
# include <cstdlib>
# include "Line.hh"
# include "SafeQueue.hh"
# include "Event.hh"
# include "Common.hh"

# define VARIABLE_ARGS	-1

class			Commands
{
  typedef void		(Commands::*commandsPtr)(std::deque<std::string>* command);

private :
  Line							_line;
  SafeQueue<Event>*					_safeEvents;
  std::map<std::pair<std::string,int>, commandsPtr>	_commandsMap;
  int							_sizeXMap;
  int							_sizeYMap;

private :
  void			checkPosValidity(int, int);
  void			checkOrientationValidity(int);
  void			checkResourcesValidity(int, int);
  int			isValid(std::deque<std::string> *);
  bool			parseSingleCommand(std::string const&);

  void			mszCommand(std::deque<std::string>*);
  void			bctCommand(std::deque<std::string>*);
  void			tnaCommand(std::deque<std::string>*);
  void			pnwCommand(std::deque<std::string>*);
  void			ppoCommand(std::deque<std::string>*);
  void			plvCommand(std::deque<std::string>*);
  void			pinCommand(std::deque<std::string>*);
  void			pexCommand(std::deque<std::string>*);
  void			pbcCommand(std::deque<std::string>*);
  void			picCommand(std::deque<std::string>*);
  void			pieCommand(std::deque<std::string>*);
  void			pfkCommand(std::deque<std::string>*);
  void			pdrCommand(std::deque<std::string>*);
  void			pgtCommand(std::deque<std::string>*);
  void			pdiCommand(std::deque<std::string>*);
  void			enwCommand(std::deque<std::string>*);
  void			ehtCommand(std::deque<std::string>*);
  void			eboCommand(std::deque<std::string>*);
  void			ediCommand(std::deque<std::string>*);
  void			sgtCommand(std::deque<std::string>*);
  void			segCommand(std::deque<std::string>*);
  void			smgCommand(std::deque<std::string>*);
  void			sucCommand(std::deque<std::string>*);
  void			spbCommand(std::deque<std::string>*);

public :
  Commands(SafeQueue<Event>*);
  ~Commands();
  bool			parseAllCommands(std::string const& orders);
};

#endif /* !COMMADS_HH_ */
