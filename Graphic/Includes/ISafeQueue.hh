//
// ISafeQueue.hh for zappy in /home/bouca-_d/rendu/Zappy/Graphic
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:17:25 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:17:43 2015 Dany Bouca Nova
//

#ifndef ISAFEQUEUE_HH_
# define ISAFEQUEUE_HH_

template <typename T>
class			ISafeQueue
{
public:
  virtual ~ISafeQueue(void) {}
  virtual void		push(T const& value) = 0;
  virtual bool		tryPop(T** value) = 0;
};

#endif /* !ISAFEQUEUE_HH_ */
