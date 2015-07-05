//
// IZappyIA.hh for zappy in /home/bouca-_d/rendu/Zappy/Client
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:01:06 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:03:00 2015 Dany Bouca Nova
//

#ifndef IZAPPYIA_H_
# define IZAPPYIA_H_

# include <vector>
# include "Network.hh"
# include "Correspondances.hh"

class					IZappyIA {

public:

  virtual ~IZappyIA() {}
  virtual void				run() = 0;

private:

  /*communication avec Network */

  virtual bool				init() = 0;
  virtual bool				trySelect() = 0;
  virtual bool				pushCommand(std::string const&) = 0;
  virtual bool				isInQueue(e_msgtype) = 0;
  virtual const std::string		refreshMsg(e_msgtype) = 0;
  virtual const std::string		getReturn(e_msgtype const) = 0;
  virtual const std::string		getMsgFromCode(e_msgtype) = 0;
  virtual bool				alreadySent(std::string const&) = 0;
  virtual bool				removeFromSent(e_msgtype) = 0;

  /* déplacements */

  virtual void				randomMove() = 0;
  virtual void				goHelp(std::string const&) = 0;
  virtual void				goFind(unsigned int ) = 0;

  /* fonctions parsing de retour sur serveur*/

  virtual void				parseVoir(std::string const&) = 0;
  virtual void				parseInventory(std::string const&) = 0;
  virtual int				peopleOnMySquare() = 0;

  /* fonctions de recherche */

  virtual void				seekFood() = 0;
  virtual void				seekStone() = 0;

  /* algo */

  virtual std::vector<e_itemtype>	isThereItemHere() = 0;
  virtual e_itemtype			isItemNeeded(std::vector<e_itemtype>) = 0;
  virtual bool				isInventoryFull() = 0;
  virtual bool				grabSupItems() = 0;
  virtual bool				dropNeededItems() = 0;
};

#endif /* !IZAPPYIA_H_ */
