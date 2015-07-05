//
// ICondVar.hh for zappy in /home/bouca-_d/rendu/Zappy/Graphic
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:17:00 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:17:17 2015 Dany Bouca Nova
//

#ifndef ICONDVAR_HH_
# define ICONDVAR_HH_

class			ICondVar
{
public:
  virtual void		wait(void) = 0;
  virtual void		signal(void) = 0;
  virtual void		broadcast(void) = 0;
};

#endif /* !ICONDVAR_HH_ */
