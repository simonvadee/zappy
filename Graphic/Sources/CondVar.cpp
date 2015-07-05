//
// CondVar.cpp for zappy in /home/bouca-_d/rendu/Zappy/Graphic
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:11:12 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:12:31 2015 Dany Bouca Nova
//

#include "CondVar.hh"

CondVar::CondVar(Mutex *mutex)
  : _mutex(mutex)
{
  pthread_cond_init(&_cond, NULL);
}

CondVar::~CondVar()
{
}

void		CondVar::wait(void)
{
  pthread_cond_wait(&_cond, _mutex->getMutex());
}

void		CondVar::signal(void)
{
  if (pthread_cond_signal(&_cond))
    throw std::exception();
}

void		CondVar::broadcast(void)
{
  if (pthread_cond_broadcast(&_cond))
    throw std::exception();
}
