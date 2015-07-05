//
// Mutex.hh for zappy in /home/bouca-_d/rendu/Zappy/Graphic
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:12:44 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:13:00 2015 Dany Bouca Nova
//

#ifndef MUTEX_HH_
# define MUTEX_HH_

# include <string>
# include <iostream>
# include "IMutex.hh"

class			Mutex : public IMutex
{
private :
  pthread_mutex_t		_mutex;
public :
  Mutex();
  virtual ~Mutex(void);
  virtual void			lock(void);
  virtual void			unlock(void);
  virtual bool			trylock(void);
  virtual pthread_mutex_t*	getMutex(void);
private :
  Mutex&	operator=(Mutex const& other);
  Mutex(Mutex const& other);
};

#endif /* !MUTEX_HH_ */
