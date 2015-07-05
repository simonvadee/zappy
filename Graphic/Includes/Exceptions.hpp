//
// Exceptions.hpp for zappy in /home/bouca-_d/rendu/Zappy/Graphic
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:15:02 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:15:02 2015 Dany Bouca Nova
//

#ifndef EXCEPTIONS_HH_
# define EXCEPTIONS_HH_

# include <exception>
# include <string>
# include <stdio.h>
# include <string.h>
# include <errno.h>

namespace	ZappyError
{
  class		SystemError : public std::exception
  {
  public :
    SystemError(int error, std::string const& message)
      : _error(error), _message(message) {}
    virtual ~SystemError() throw() {}
    virtual const char*	what() const throw()
  {
    std::string	tmp(_message);

    tmp += " ";
    tmp += strerror(errno);
    return tmp.c_str();
  }
  private :
    int		_error;
    std::string	_message;
  };

  class		ArgumentsError : public std::exception
  {
  public :
    ArgumentsError(std::string const& message)
      : _message(message) {}
    virtual ~ArgumentsError() throw() {}
    virtual const char*	what() const throw()
    {
      return _message.c_str();
    }
  private :
    int		_error;
    std::string	_message;
  };

  class		PositionsError : public std::exception
  {
  public :
    PositionsError(std::string const& message)
      : _message(message) {}
    virtual ~PositionsError() throw() {}
    virtual const char*	what() const throw()
    {
      return _message.c_str();
    }
  private :
    int		_error;
    std::string	_message;
  };

  class		OrientationError : public std::exception
  {
  public :
    OrientationError(std::string const& message)
      : _message(message) {}
    virtual ~OrientationError() throw() {}
    virtual const char*	what() const throw()
    {
      return _message.c_str();
    }
  private :
    int		_error;
    std::string	_message;
  };

  class		ResourceError : public std::exception
  {
  public :
    ResourceError(std::string const& message)
      : _message(message) {}
    virtual ~ResourceError() throw() {}
    virtual const char*	what() const throw()
    {
      return _message.c_str();
    }
  private :
    int		_error;
    std::string	_message;
  };

  class		InitError : public std::exception
  {
  public :
    InitError(std::string const& message)
      : _message(message) {}
    virtual ~InitError() throw() {}
    virtual const char*	what() const throw()
    {
      return _message.c_str();
    }
  private :
    int		_error;
    std::string	_message;
  };
};

#endif /* !EXCEPTIONS_HH_ */
