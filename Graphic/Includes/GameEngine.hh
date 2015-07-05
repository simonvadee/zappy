//
// GameEngine.hh for zappy in /home/bouca-_d/rendu/Zappy/Graphic
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:16:49 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:31:59 2015 Dany Bouca Nova
//

#ifndef GAMEENGINE_HH_
# define GAMEENGINE_HH_

# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>
# include <SFML/Audio/Sound.hpp>
# include <SFML/Audio/SoundBuffer.hpp>
# include <SFML/System/Clock.hpp>

# include <iostream>
# include <vector>
# include <unistd.h>
# include <cstdlib>

# include <algorithm>
# include "Exceptions.hpp"
# include "SafeQueue.hh"
# include "Network.hh"
# include "Event.hh"
# include "Common.hh"
# include "AObj.hh"
# include "Event.hh"
# include "SafeQueue.hh"
# include "AssetsManager.hh"

typedef		enum
  {
    GRASSONE = 0,
    GRASSTWO,
    SFOOD,
    SLINEMATE,
    SDERAUMERE,
    SSIBUR,
    SMENDIANE,
    SPHIRAS,
    STHYSTAME,
    EGGS,
    PLAYER,
    STAR,
    DIALOG
  }		e_type;

typedef struct	s_cube
{
  int		food;
  int		linemate;
  int		deraumere;
  int		sibur;
  int		mendiane;
  int		phiras;
  int		thystame;
  int		eggs;
  e_type	type;
  sf::Vector2f	pos;
}		t_cube;

typedef struct		s_player
{
  int			id;
  sf::Vector2f		pos;
  e_orientation		O;
  std::string		teamName;
  std::string		broadcast;
  bool			hasToBroadCast;
  bool			isBroadcasting;
  int			lvl;
  std::vector<int>	inventory;
  sf::Time		countBroadcast;
  sf::Time		countEgg;
  bool			incant;
  bool			egg;
}			t_player;

typedef struct		s_egg
{
  int			id;
  sf::Vector2f		pos;
}			t_egg;

class					GameEngine : public AObj {

  typedef void				(GameEngine::*_updatePtr)(Event*);

private:
  const float				WIDTH;
  const float				HEIGHT;

  bool					_endGui;
  SafeQueue<Event>*			_safeEvents;
  sf::RenderWindow			_window;
  sf::Event				_event;
  std::vector<std::vector<t_cube *> >	_map;
  std::vector<t_player *>		_players;
  std::vector<t_egg *>			_eggs;
  std::vector<std::string>		_teams;
  std::vector<sf::Color>		_teamsColors;
  std::vector<sf::IntRect>		_intRects;
  std::map<std::string, _updatePtr>	_mapUpdate;
  std::map<int, sf::Sprite*>		_spriteCorresp;

  sf::RectangleShape			*_backPopup;
  sf::Sprite				*_loading;
  sf::Sprite				*_grass1;
  sf::Sprite				*_grass2;
  sf::Sprite				*_background;
  sf::Sprite				*_plus;
  sf::Sprite				*_minus;
  sf::Sprite				*_food;
  sf::Sprite				*_linemate;
  sf::Sprite				*_deraumere;
  sf::Sprite				*_sibur;
  sf::Sprite				*_mendiane;
  sf::Sprite				*_phiras;
  sf::Sprite				*_thystame;
  sf::Sprite				*_egg;
  sf::Sprite				*_player;
  sf::Sprite				*_star;
  sf::Sprite				*_dialog;
  sf::Sprite				*_end;
  sf::Font				*_font;
  sf::Text				_text;

  sf::Clock				_pupplayer;
  sf::Clock				_pupinfos;

  sf::View				_view;
  sf::View				_affText;
  sf::View				_viewback;

  sf::Vector2f				_popInfos;
  sf::Vector2f				_popPlayer;
  sf::Vector2f				_draw;
  bool					_followPlayer;
  float					_mapy;
  float					_mapx;
  float					_zoom;
  size_t				_time;

  bool			initialize();
  bool			update();
  void			draw(sf::Clock const&);

  bool			waitMsz();
  void			manageKeyboard(const sf::Keyboard::Key &);
  bool			checkButton(const sf::Vector2i &, int, int, int, int);
  bool			checkTime();
  void			manageMouse(const sf::Mouse::Button &);
  void			manageWheelMouse(const sf::Event::MouseWheelEvent &);
  bool			exitThread();
  void			initBoard();

  inline unsigned int	Max(int, int) const;
  inline unsigned int	Min(int, int) const;
  void			moveCameraFollowPlayer(int, int);
  bool			isPlayer(const std::size_t &);
  void			drawText(const std::string &, const sf::Vector2f &, const sf::Vector2f &, const sf::Color &);
  void			drawCaseInfos();
  void			initPopup(bool &);
  void			drawPlayerInfos();
  int			getSkin(t_player *, sf::Clock const&);
  void			drawRessource(sf::Vector2f const&, e_type, int, int *);
  void			drawPlayers(sf::Clock const&);
  void			drawAllRessources();
  void			drawLvls(t_player *);
  void			drawBroadCast(sf::Clock const&, t_player *);

  /*
  ** Commands
  */

  bool			loopNetworkEvents();
  void			manageBct(Event *);
  void			manageTna(Event *);
  void			managePnw(Event *);
  void			managePpo(Event *);
  void			managePlv(Event *);
  void			managePin(Event *);
  void			managePbc(Event *);
  void			managePic(Event *);
  void			managePie(Event *);
  void			managePfk(Event *);
  void			managePdr(Event *);
  void			managePgt(Event *);
  void			managePdi(Event *);
  void			manageSeg(Event *);
  void			manageSgt(Event *);
  void			manageEnw(Event *);
  void			manageEbo(Event *);
  void			manageEdi(Event *);

public:
  GameEngine(SafeQueue<Event> *);
  virtual ~GameEngine();
  virtual void		start();
};

#endif /* !GAMEENGINE_HH_ */
