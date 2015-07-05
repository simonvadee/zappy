//
// IMutex.hh for zappy in /home/bouca-_d/rendu/Zappy/Graphic
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:20:14 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:20:15 2015 Dany Bouca Nova
//

#ifndef IMUTEX_HH_
# define IMUTEX_HH_

# include <pthread.h>

class		IMutex
{
public :
  virtual ~IMutex(void) {}
  virtual void			lock(void) = 0;
  virtual void			unlock(void) = 0;
  virtual bool			trylock(void) = 0;
  virtual pthread_mutex_t*	getMutex(void) = 0;
};

#endif /* !IMUTEX_HH_ */
