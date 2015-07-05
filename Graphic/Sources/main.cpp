//
// main.cpp for zappy in /home/bouca-_d/rendu/Zappy/Graphic
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:19:45 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:19:45 2015 Dany Bouca Nova
//

#include "Network.hh"
#include "Exceptions.hpp"
#include "GameEngine.hh"
#include "Thread.hh"
#include "SafeQueue.hh"
#include "Event.hh"

template class			Thread<GameEngine>;
template class			SafeQueue<Event>;

int				main(int ac, char **av)
{
  SafeQueue<Event>*		safeEvents = new SafeQueue<Event>;
  GameEngine			gameEngine(safeEvents);
  Thread<GameEngine>		thGame(&gameEngine);

  try
    {
      Network			network(ac, av, safeEvents);

      network.initConnection();
      thGame.start();
      network.run();
    }
  catch (ZappyError::ArgumentsError e)
    {
      safeEvents->setRunning(false);
      std::cerr << e.what() << std::endl;
    }
  catch (ZappyError::SystemError e)
    {
      safeEvents->setRunning(false);
      std::cerr << e.what() << std::endl;
    }
  catch (ZappyError::PositionsError e)
    {
      safeEvents->setRunning(false);
      std::cerr << e.what() << std::endl;
    }
  catch (ZappyError::OrientationError e)
    {
      safeEvents->setRunning(false);
      std::cerr << e.what() << std::endl;
    }
  catch (ZappyError::ResourceError e)
    {
      safeEvents->setRunning(false);
      std::cerr << e.what() << std::endl;
    }
  thGame.wait();
  return (EXIT_SUCCESS);
}
