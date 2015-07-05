//
// ScopedLock.cpp for zappy in /home/bouca-_d/rendu/Zappy/Graphic
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:10:40 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:10:41 2015 Dany Bouca Nova
//

#include "ScopedLock.hh"

ScopedLock::ScopedLock(Mutex &mutex)
  : _mutex(mutex)
{
  _mutex.lock();
}

ScopedLock::~ScopedLock()
{
  _mutex.unlock();
}
