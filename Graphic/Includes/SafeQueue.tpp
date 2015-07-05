//
// SafeQueue.tpp for zappy in /home/bouca-_d/rendu/Zappy/Graphic
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:11:41 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:11:42 2015 Dany Bouca Nova
//

#include "Event.hh"

template <typename T>
SafeQueue<T>::SafeQueue()
  : _isDrawing(false),
    _isRunning(true),
    _timeToSet(0)
{
}

template <typename T>
SafeQueue<T>::~SafeQueue(void)
{
}

template <typename T>
void		SafeQueue<T>::push(T const& value)
{
  ScopedLock	lock(_mutex);

  _queue.push_front(new T(value));
}

template <typename T>
bool		SafeQueue<T>::tryPop(T** value)
{
  ScopedLock	lock(_mutex);

  if (_queue.size() > 0)
    {
      *value = _queue.back();
      _queue.pop_back();
      return (true);
    }
  (void)value;
  return (false);
}

template <typename T>
void		SafeQueue<T>::setDrawing(bool isDrawing)
{
  ScopedLock	lock(_mutex);

  _isDrawing = isDrawing;
}

template <typename T>
bool		SafeQueue<T>::getDrawing()
{
  return _isDrawing;
}

template <typename T>
void		SafeQueue<T>::setRunning(bool isRunning)
{
  ScopedLock	lock(_mutex);

  _isRunning = isRunning;
}

template <typename T>
bool		SafeQueue<T>::getRunning()
{
  return _isRunning;
}

template <typename T>
void		SafeQueue<T>::setTimeToSet(unsigned int time)
{
  ScopedLock	lock(_mutex);

  _timeToSet = time;
}

template <typename T>
unsigned int		SafeQueue<T>::getTimeToSet()
{
  return _timeToSet;
}
