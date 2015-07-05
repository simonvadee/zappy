//
// CondVar.hh for zappy in /home/bouca-_d/rendu/Zappy/Graphic
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:16:21 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:16:33 2015 Dany Bouca Nova
//

#ifndef CONDVAR_HH_
# define CONDVAR_HH_

# include <pthread.h>
# include <exception>
# include "Mutex.hh"
# include "ICondVar.hh"

class			CondVar : public ICondVar
{
private:
  Mutex*		_mutex;
  pthread_cond_t	_cond;

public:
  CondVar(Mutex* mutex);
  ~CondVar();
  virtual void		wait(void);
  virtual void		signal(void);
  virtual void		broadcast(void);
};

#endif /* !CONDVAR_HH_ */
