//
// Mutex.cpp for zappy in /home/bouca-_d/rendu/Zappy/Graphic
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:10:52 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:10:54 2015 Dany Bouca Nova
//
//

#include "Mutex.hh"

Mutex::Mutex()
{
  pthread_mutex_init(&_mutex, NULL);
}

Mutex::~Mutex()
{
  pthread_mutex_destroy(&_mutex);
}

void	Mutex::lock()
{
  pthread_mutex_lock(&_mutex);
}

void	Mutex::unlock()
{
  pthread_mutex_unlock(&_mutex);
}

bool	Mutex::trylock()
{
  return (pthread_mutex_trylock(&_mutex) == 0 ? true : false);
}

pthread_mutex_t*	Mutex::getMutex()
{
  return (&_mutex);
}
