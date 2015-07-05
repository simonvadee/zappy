//
// Thread.tpp for zappy in /home/bouca-_d/rendu/Zappy/Graphic
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:19:07 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:19:08 2015 Dany Bouca Nova
//

template <typename T>
Thread<T>::Thread(T* handler)
  : _status(WAITING), _handler(handler)
{
  _joinErrors[ESRCH] = "Aucun thread : ne correspond pas à celui passé en argument";
  _joinErrors[EINVAL] = "Le thread a été détaché ou un autre thread attend déjà\
 la fin du même thread.";
  _joinErrors[EDEADLK] = "Le thread passé en argument correspond au thread appelant.";
}

template <typename T>
Thread<T>::~Thread()
{
}

template <typename T>
bool					Thread<T>::wait()
{
  int					ret;
  std::map<int, std::string>::iterator	it;

  if (_status == RUNNING)
    {
      ret = pthread_join(_th, NULL);
      _status = DEAD;
      if ((it = _joinErrors.find(ret)) != _joinErrors.end())
	std::cerr << it->second << std::endl;
      return (true);
    }
  return (false);
}

template <typename T>
bool		Thread<T>::start()
{
  if (!pthread_create(&_th, NULL, &start_routine, (void *)_handler))
    {
      _status = RUNNING;
      return (true);
    }
  return (false);
}
