//
// ZappyIA.hh for zappy in /home/bouca-_d/rendu/Zappy/Client
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:01:28 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:02:13 2015 Dany Bouca Nova
//

#ifndef ZAPPYIA_H_
# define ZAPPYIA_H_

# include <deque>
# include "Correspondances.hh"
# include "IZappyIA.hh"

# define ENOUGH_FOOD 20
# define ENOUGH_FOOD_COMING 12
# define ENOUGH_FOOD_INCANT 5

class					ZappyIA : public IZappyIA {

public:
  ZappyIA(std::deque<std::string>*, std::deque<std::string>*, Network*, Correspondances const&);
  virtual ~ZappyIA();

  virtual void				run();

private:

  virtual bool				init();
  virtual bool				trySelect();
  virtual bool				pushCommand(std::string const&);
  virtual const std::string		refreshMsg(e_msgtype);
  virtual bool				isInQueue(e_msgtype);
  virtual const std::string		getReturn(e_msgtype);
  virtual bool				alreadySent(std::string const&);
  virtual bool				removeFromSent(e_msgtype);
  virtual const std::string		getMsgFromCode(e_msgtype);

  virtual void				randomMove();
  virtual void				goHelp(std::string const&);
  virtual void				goFind(unsigned int);

  virtual void				parseInventory(std::string const&);
  virtual void				parseVoir(std::string const&);
  virtual int				peopleOnMySquare();

  virtual void				seekFood();
  virtual void				seekStone();

  void					careForHelp();
  bool					validObjectsDown();
  bool					manageHelp(std::string const&);
  unsigned int				getQuantity(std::string const&);
  bool					lookForSuccess();
  bool					stoneINeedIn(unsigned int, std::string&);
  bool					informPeople();
  bool					manageBroadcasts();
  bool					enoughFood(unsigned int);
  std::vector<e_itemtype>		isThereItemHere();
  e_itemtype				isItemNeeded(std::vector<e_itemtype>);
  bool					isInventoryFull();
  bool					makeReciepe();
  const std::string			itemInStock(std::string const&);
  bool					tryToLevelUp();
  void					createObjectsDown(std::string const&);
  void					emptyObjectsDown();
  bool					grabSupItems();
  bool					dropNeededItems();
  bool					enoughPeopleForFood(float);

  bool					isStateHungry();
  void					tellMatesToLeave();
  bool					handleCallPeople(std::string const&);
  void					checkIfMessageReturning();

  void						checkState();

private:

  /* perso attributes*/
  unsigned int					_level;
  e_actualstate					_state;
  e_actualstate					_oldState;
  std::vector<unsigned int>			_inventory;
  std::vector<unsigned int>			_objectsDown;
  std::string					_voir;
  Network					*_network;
  std::vector<std::string>			_randomDir;
  unsigned int					_food;
  unsigned int					_count;
  /* communication */
  std::deque<std::string>			*_toSend;
  std::deque<std::string>			*_toReceive;
  std::deque<std::string>			_sent;

  Correspondances				_table;
};

#endif /* !ZAPPYIA_H_ */
