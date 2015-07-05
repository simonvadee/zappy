//
// Routine.cpp for zappy in /home/bouca-_d/rendu/Zappy/Graphic
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:19:57 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:19:57 2015 Dany Bouca Nova
//

#include "AObj.hh"

void		*start_routine(void *arg)
{
  AObj		*obj = reinterpret_cast<AObj*>(arg);

  obj->start();
  return (NULL);
}
