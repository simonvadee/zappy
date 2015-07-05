//
// ScopedLock.hh for zappy in /home/bouca-_d/rendu/Zappy/Graphic
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:18:35 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:18:54 2015 Dany Bouca Nova
//

#ifndef SCOPEDLOCK_HH
# define SCOPEDLOCK_HH

# include "Mutex.hh"

class		ScopedLock
{
private :
  Mutex		&_mutex;

public :
  ScopedLock(Mutex &mutex);
  ~ScopedLock();
private :
  ScopedLock&	operator=(ScopedLock const&);
  ScopedLock(ScopedLock const&);
};

#endif /* !SCOPEDLOCK_HH */
