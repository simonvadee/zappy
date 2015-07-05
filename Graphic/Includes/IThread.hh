//
// IThread.hh for zappy in /home/bouca-_d/rendu/Zappy/Graphic
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:14:14 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:14:29 2015 Dany Bouca Nova
//

#ifndef ITHREAD_HH_
# define ITHREAD_HH_

# include <pthread.h>

class		IThread
{
public :
  typedef enum
    {
      WAITING = 1,
      RUNNING,
      DEAD
    }		e_status;

  virtual ~IThread() {}
  virtual bool		wait() = 0;
  virtual bool		start() = 0;
};

#endif /* !ITHREAD_HH_ */
