//
// AObj.hh for zappy in /home/bouca-_d/rendu/Zappy/Graphic
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:15:49 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:15:49 2015 Dany Bouca Nova
//

#ifndef AOBJ_H_
# define AOBJ_H_

# include "Mutex.hh"

class AObj {

public:
  AObj() {}
  virtual ~AObj() {}
  virtual void start() = 0;

};

#endif /* !AOBJ_HH */
