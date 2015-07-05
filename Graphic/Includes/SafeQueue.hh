//
// SafeQueue.hh for zappy in /home/bouca-_d/rendu/Zappy/Graphic
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:18:22 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:18:23 2015 Dany Bouca Nova
//

#ifndef SAFEQUEUE_HH_
# define SAFEQUEUE_HH_

# include <cstdlib>
# include <deque>
# include "Thread.hh"
# include "ScopedLock.hh"
# include "ISafeQueue.hh"

template <typename T>
class			SafeQueue : public ISafeQueue<T>
{
private:
  Mutex			_mutex;
  std::deque<T*>	_queue;
  bool			_isDrawing;
  bool			_isRunning;
  unsigned int		_timeToSet;

public:
  SafeQueue();
  virtual ~SafeQueue(void);
  virtual void		push(T const&);
  virtual bool		tryPop(T**);
  void			setDrawing(bool);
  bool			getDrawing();
  void			setRunning(bool);
  bool			getRunning();
  void			setTimeToSet(unsigned int);
  unsigned int		getTimeToSet();
};

# include "SafeQueue.tpp"

#endif /* !SAFEQUEUE_HH_ */
