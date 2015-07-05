//
// Exceptions.hpp for zappy in /home/bouca-_d/rendu/Zappy/Client
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:01:09 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:01:10 2015 Dany Bouca Nova
//
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
  class		ConnectionFailure : public std::exception
  {
  public :
    ConnectionFailure(int error, std::string const& message) throw()
      : _error(error), _message(message) {}
    virtual ~ConnectionFailure() throw() {}
    virtual const char*	what() const throw()
    {
      std::string	tmp(strerror(_error));

      tmp += " " + _message;
      return _message.c_str();
    }
  private :
    int		_error;
    std::string	_message;
  };

class		SelectFailure : public std::exception
{
public :
  SelectFailure(int error, std::string const& message) throw()
    : _error(error), _message(message) {}
  virtual ~SelectFailure() throw() {}
  virtual const char*	what() const throw()
  {
    std::string	tmp(strerror(_error));

    tmp += " " + _message;
    return _message.c_str();
  }
private :
  int		_error;
  std::string	_message;
};

};

#endif /* !EXCEPTIONS_HH_ */
