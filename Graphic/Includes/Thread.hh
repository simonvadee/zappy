//
// Thread.hh for zappy in /home/bouca-_d/rendu/Zappy/Graphic
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:11:23 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:12:26 2015 Dany Bouca Nova
//

#ifndef THREAD_HH_
# define THREAD_HH_

# include <map>
# include <string>
# include <iostream>
# include <pthread.h>
# include <errno.h>
# include "Exceptions.hpp"
# include "AObj.hh"
# include "ScopedLock.hh"
# include "IThread.hh"

template <typename T>
class			Thread : public IThread
{
private :
  e_status			_status;
  T*				_handler;
  pthread_t			_th;
  std::map<int, std::string>	_joinErrors;

public :
  Thread(T* handler);
  virtual ~Thread();
  virtual bool		wait();
  virtual bool		start();
private :
  Thread(Thread const&);
  Thread&	operator=(Thread const&);
};

void*		start_routine(void *);

# include "Thread.tpp"

#endif /* !THREAD_HH_ */
