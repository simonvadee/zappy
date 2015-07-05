//
// GameEngine.cpp for zappy in /home/bouca-_d/rendu/Zappy/Graphic
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:11:06 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:31:26 2015 Dany Bouca Nova
//

#include <iostream>
#include <sstream>
#include "GameEngine.hh"
#include "Common.hh"

GameEngine::GameEngine(SafeQueue<Event>* safeEvents)
  : WIDTH(1440.0f),
    HEIGHT(900.0f),
    _endGui(false),
    _safeEvents(safeEvents),
    _followPlayer(false),
    _mapy(0),
    _mapx(0),
    _zoom(500.5f),
    _time(0)
{
  _popInfos.x = -1;
  _popInfos.y = -1;
  _popPlayer.x = -1;
  _popPlayer.y = -1;

  _mapUpdate["bct"] = &GameEngine::manageBct;
  _mapUpdate["tna"] = &GameEngine::manageTna;
  _mapUpdate["pnw"] = &GameEngine::managePnw;
  _mapUpdate["ppo"] = &GameEngine::managePpo;
  _mapUpdate["plv"] = &GameEngine::managePlv;
  _mapUpdate["pin"] = &GameEngine::managePin;
  _mapUpdate["pex"] = NULL;
  _mapUpdate["pbc"] = &GameEngine::managePbc;
  _mapUpdate["pic"] = &GameEngine::managePic;
  _mapUpdate["pie"] = &GameEngine::managePie;
  _mapUpdate["pfk"] = &GameEngine::managePfk;
  _mapUpdate["pdr"] = &GameEngine::managePdr;
  _mapUpdate["pgt"] = &GameEngine::managePgt;
  _mapUpdate["pdi"] = &GameEngine::managePdi;
  _mapUpdate["enw"] = &GameEngine::manageEnw;
  _mapUpdate["ebo"] = &GameEngine::manageEbo;
  _mapUpdate["edi"] = &GameEngine::manageEdi;
  _mapUpdate["sgt"] = &GameEngine::manageSgt;
  _mapUpdate["seg"] = &GameEngine::manageSeg;

  _mapUpdate["eht"] = NULL;
  _mapUpdate["smg"] = NULL;
  _mapUpdate["suc"] = NULL;
  _mapUpdate["spb"] = NULL;
}

GameEngine::~GameEngine()
{
  for (std::size_t y = 0; y < _map.size(); ++y)
    {
      for (size_t x = 0; x < _map[y].size(); ++x)
	delete _map[y][x];
    }
  for (std::size_t i = 0; i != _players.size(); ++i)
    delete _players[i];
  for (std::size_t i = 0; i != _eggs.size(); ++i)
    delete _eggs[i];
  AssetsManager::destroyAssetsManager();
}

bool			GameEngine::initialize()
{
  _window.create(sf::VideoMode(WIDTH, HEIGHT),"-!> Zappy <!-");

  AssetsManager::instanciateAssetsManager();
  _food = AssetsManager::getFood();
  _linemate = AssetsManager::getLinemate();
  _deraumere = AssetsManager::getDeraumere();
  _sibur = AssetsManager::getSibur();
  _mendiane = AssetsManager::getMendiane();
  _phiras = AssetsManager::getPhiras();
  _thystame = AssetsManager::getThystame();
  _egg = AssetsManager::getEgg();
  _loading = AssetsManager::getLoading();
  _grass1 = AssetsManager::getGrassFirst();
  _grass2 = AssetsManager::getGrassSecond();
  _background = AssetsManager::getBackground();
  _minus = AssetsManager::getMinus();
  _plus = AssetsManager::getPlus();
  _font = AssetsManager::getFont();
  _backPopup = AssetsManager::getPopup();
  _player = AssetsManager::getPlayer();
  _star = AssetsManager::getStar();
  _dialog = AssetsManager::getDialog();
  _end = AssetsManager::getGameOver();

  _text.setFont(*_font);
  _text.setCharacterSize(35);
  _plus->setPosition(sf::Vector2f(817, 2));
  _minus->setPosition(sf::Vector2f(770, 2));

  _spriteCorresp[GRASSONE] = _grass1;
  _spriteCorresp[GRASSTWO] = _grass2;
  _spriteCorresp[SFOOD] = _food;
  _spriteCorresp[SLINEMATE] = _linemate;
  _spriteCorresp[SDERAUMERE] = _deraumere;
  _spriteCorresp[SSIBUR] = _sibur;
  _spriteCorresp[SMENDIANE] = _mendiane;
  _spriteCorresp[SPHIRAS] = _phiras;
  _spriteCorresp[STHYSTAME] = _thystame;
  _spriteCorresp[EGGS] = _egg;
  _spriteCorresp[DIALOG] = _dialog;
  _spriteCorresp[PLAYER] = _player;
  _spriteCorresp[STAR] = _star;
  _spriteCorresp[STAR]->setScale(sf::Vector2f(0.05f, 0.05f));

  _spriteCorresp[PLAYER]->setOrigin(sf::Vector2f(45 / 2, 55 / 2));
  _spriteCorresp[PLAYER]->setScale(sf::Vector2f(4.0f, 4.0f));

  _intRects.push_back(sf::IntRect(15, 10, 45, 55));
  _intRects.push_back(sf::IntRect(15, 200, 45, 55));
  _intRects.push_back(sf::IntRect(15, 140, 45, 55));
  _intRects.push_back(sf::IntRect(15, 70, 45, 55));
  _intRects.push_back(sf::IntRect(260, 10, 55, 55));
  _intRects.push_back(sf::IntRect(260, 200, 55, 55));
  _intRects.push_back(sf::IntRect(260, 140, 55, 55));
  _intRects.push_back(sf::IntRect(260, 70, 55, 55));
  _intRects.push_back(sf::IntRect(145, 10, 45, 55));
  _intRects.push_back(sf::IntRect(145, 200, 45, 55));
  _intRects.push_back(sf::IntRect(145, 140, 45, 55));
  _intRects.push_back(sf::IntRect(145, 70, 45, 55));
  return (true);
}

bool			GameEngine::waitMsz()
{
  Event			*tmp = NULL;

  while (_safeEvents->getRunning()
	 && _safeEvents->getDrawing()
	 && !_safeEvents->tryPop(&tmp));
  if (tmp == NULL || tmp->getCommandType() != "msz")
    return exitThread();
  _mapx = static_cast<float>(tmp->getX());
  _mapy = static_cast<float>(tmp->getY());
  delete tmp;
  initBoard();
  return true;
}

bool			GameEngine::exitThread()
{
  _safeEvents->setDrawing(false);
  if (_window.isOpen())
    _window.close();
  return false;
}

void			GameEngine::initBoard()
{
  for (float y = 0.0f; y < _mapy; ++y)
    {
      std::vector<t_cube *>	vec;

      for (float x = 0.0f; x < _mapy; ++x)
	{
	  t_cube *cube = new t_cube();

	  cube->food = 0;
	  cube->linemate = 0;
	  cube->deraumere = 0;
	  cube->sibur = 0;
	  cube->mendiane = 0;
	  cube->phiras = 0;
	  cube->thystame = 0;
	  cube->eggs = 0;
	  cube->type = static_cast<e_type>(rand() % 2);
	  cube->pos.x = x * 256;
	  cube->pos.y = y * 256;
	  vec.push_back(cube);
	}
      _map.push_back(vec);
    }
}

void			GameEngine::manageKeyboard(const sf::Keyboard::Key &code)
{
  if (code == sf::Keyboard::Space)
    {
      if (_followPlayer)
      	_followPlayer = false;
      else
      	_followPlayer = true;
    }
  else if (code == sf::Keyboard::Down)
    _draw.y += 40;
  else if (code == sf::Keyboard::Up)
    _draw.y -= 40;
  else if (code == sf::Keyboard::Left)
    _draw.x -= 40;
  else if (code == sf::Keyboard::Right)
    _draw.x += 40;
}

bool			GameEngine::checkButton(const sf::Vector2i &pos, int x, int y,
						int width, int height)
{
  return ((pos.x >= x && pos.x <= width) && (pos.y >= y && pos.y <= height));
}

bool			GameEngine::checkTime()
{
  sf::Vector2i pos = sf::Mouse::getPosition(_window);

  if (checkButton(pos, 1365, 6, 1435, 53))
    {
      std::cout << "TIME +10 : " << _time << std::endl;
      _time += 10;
      _safeEvents->setTimeToSet(_time);
      return (true);
    }
  else if (checkButton(pos, 1285, 6, 1360, 53))
    {
      std::cout << "TIME -10 : " << _time << std::endl;
      _time = (_time > 10 ? _time - 10 : _time);
      _safeEvents->setTimeToSet(_time);
      return (true);
    }
  return (false);
}

void			GameEngine::manageMouse(const sf::Mouse::Button &click)
{
  sf::Vector2f		pos = _window.mapPixelToCoords(sf::Mouse::getPosition(_window));
  int			x = static_cast<int>(pos.x /= 256);;
  int			y = static_cast<int>(pos.y /= 256);;

  if (checkTime())
    return ;
  if (click == sf::Mouse::Left)
    {
      if (x < _mapx && y < _mapy)
	{
	  _popInfos.x = x;
	  _popInfos.y = y;
	  _pupinfos.restart();
	}
    }
  else if (click == sf::Mouse::Right)
    {
      if (x < _mapx && y < _mapy)
	{
	  _popPlayer.x = x;
	  _popPlayer.y = y;
	  _pupplayer.restart();
	}
    }
}

void					GameEngine::manageWheelMouse(const sf::Event::MouseWheelEvent &wheel)
{
  if (wheel.delta > 0 && _zoom > 0.5f)
    {
      _zoom -= 20;
      _view.setSize(WIDTH / 2 + _zoom, HEIGHT / 2 + _zoom);
    }
  else if (wheel.delta < 0 && _zoom < 5000.f)
    {
      _zoom += 20;
      _view.setSize(WIDTH / 2 + _zoom, HEIGHT / 2 + _zoom);
    }
}

void					GameEngine::manageBct(Event *event)
{
  for (size_t y = 0; y < _map.size(); ++y)
    {
      for (size_t x = 0; x < _map[y].size(); ++x)
	{
	  if (_map[y][x]->pos.x / 256 == static_cast<float>(event->getX())
	      && _map[y][x]->pos.y / 256 == static_cast<float>(event->getY()))
	    {
	      _map[y][x]->eggs = 0;
	      _map[y][x]->food = event->getQuantities(FOOD);
	      _map[y][x]->linemate = event->getQuantities(LINEMATE);
	      _map[y][x]->deraumere = event->getQuantities(DERAUMERE);
	      _map[y][x]->sibur = event->getQuantities(SIBUR);
	      _map[y][x]->mendiane = event->getQuantities(MENDIANE);
	      _map[y][x]->phiras = event->getQuantities(PHIRAS);
	      _map[y][x]->thystame = event->getQuantities(THYSTAME);
	    }
	}
    }
}

void					GameEngine::manageTna(Event *event)
{
  _teams.push_back(event->getTeamName());
  _teamsColors.push_back(sf::Color(255 - (_teamsColors.size() * 150) % 255, 0, 0 + (_teamsColors.size() * 150) % 255));
}

void					GameEngine::managePnw(Event *event)
{
  t_player				*newPlayer = new t_player;

  for (int i = 0; i < 7; ++i)
    newPlayer->inventory.push_back(0);
  newPlayer->id = event->getNbPlayer();
  newPlayer->pos.x = event->getX() * 256 + 128;
  newPlayer->pos.y = event->getY() * 256 + 128;
  newPlayer->O = event->getOrientation();
  newPlayer->teamName = event->getTeamName();
  newPlayer->lvl = event->getLvl();
  newPlayer->incant = false;
  newPlayer->hasToBroadCast = false;
  newPlayer->isBroadcasting = false;
  newPlayer->egg = false;
  _players.push_back(newPlayer);
}

void					GameEngine::moveCameraFollowPlayer(int x, int y)
{
  _view.setCenter(sf::Vector2f(x * 256 + 128, y * 256 + 128 / 2));
}

void					GameEngine::managePpo(Event *event)
{
  std::vector<t_player *>::iterator	it;

  for (it = _players.begin(); it != _players.end(); ++it)
    {
      if ((*it)->id == event->getNbPlayer())
	{
	  if (_followPlayer)
	    moveCameraFollowPlayer(event->getX(), event->getY());
	  (*it)->pos.x = event->getX() * 256 + 128;
	  (*it)->pos.y = event->getY() * 256 + 128;
	  (*it)->O = event->getOrientation();
	}
    }
}

void					GameEngine::managePlv(Event *event)
{
  std::vector<t_player *>::iterator	it;

  for (it = _players.begin(); it != _players.end(); ++it)
    {
      if ((*it)->id == event->getNbPlayer())
	(*it)->lvl = event->getLvl();
    }
}

void					GameEngine::managePin(Event *event)
{
  std::vector<t_player *>::iterator	it;

  for (it = _players.begin(); it != _players.end(); ++it)
    {
      if ((*it)->id == event->getNbPlayer())
	{
	  (*it)->pos.x = event->getX() * 256 + 128;
	  (*it)->pos.y = event->getY() * 256 + 128;
	  for (int i = 0; i < 7; ++i)
	    {
	      (*it)->inventory[i] = event->getQuantities(static_cast<e_ressource>(i));
	    }
	}
    }
}

void					GameEngine::managePbc(Event *event)
{
  std::vector<t_player *>::iterator	it;

  for (it = _players.begin(); it != _players.end(); ++it)
    {
      if ((*it)->id == event->getNbPlayer())
	{
	  (*it)->broadcast = event->getMessageBroadcast();
	  (*it)->hasToBroadCast = true;
	  (*it)->isBroadcasting = false;
	}
    }
}

void					GameEngine::managePic(Event *event)
{
  for (unsigned int i = 0; i < _players.size(); ++i)
    {
      if ((_players[i])->id == event->getNbPlayer())
	(_players[i])->incant = true;
    }
}

void					GameEngine::managePie(Event *event)
{
  std::vector<t_player *>::iterator	it;

  for (it = _players.begin(); it != _players.end(); ++it)
    {
      if ((*it)->pos.x == event->getX() * 256 + 128
	  && (*it)->pos.y == event->getY() * 256 + 128)
	(*it)->incant = false;
    }
}

void					GameEngine::managePfk(Event *event)
{
  for (unsigned int i = 0; i < _players.size(); ++i)
    {
      if ((_players[i])->id == event->getNbPlayer())
	{
	  (_players[i])->egg = true;
	  (_players[i])->countEgg = sf::seconds(1.0f);
	}
    }
}

void					GameEngine::manageSeg(Event *event)
{
  std::string				team;

  team = event->getTeamName();
  _window.draw(*_end);
  drawText(team, sf::Vector2f(1.f, 1.f), sf::Vector2f(600, 600), sf::Color::Blue);
  _window.display();
  sleep(2);
  exitThread();
  _endGui = true;
}

void					GameEngine::manageSgt(Event *event)
{
  _time = event->getTime();
}

void					GameEngine::managePdr(Event *event)
{
  std::vector<t_player *>::iterator	it;

  for (it = _players.begin(); it != _players.end(); ++it)
    {
      if ((*it)->id == event->getNbPlayer())
	(*it)->inventory[static_cast<int>(event->getRessourceTaken())] -= 1;
    }
}

void					GameEngine::managePgt(Event *event)
{
  std::vector<t_player *>::iterator	it;

  for (it = _players.begin(); it != _players.end(); ++it)
    {
      if ((*it)->id == event->getNbPlayer())
	(*it)->inventory[static_cast<int>(event->getRessourceTaken())] += 1;
    }
}

void					GameEngine::managePdi(Event *event)
{
  std::vector<t_player *>::iterator	it;

  for (it = _players.begin(); it != _players.end(); ++it)
    {
      if ((*it)->id == event->getNbPlayer())
	{
	  delete (*it);
	  _players.erase(it);
	  break ;
	}
    }
}

void					GameEngine::manageEnw(Event *event)
{
  t_egg					*egg = new t_egg;

  egg->id = event->getNbEgg();
  egg->pos.x = event->getX() * 256;
  egg->pos.y = event->getY() * 256;
  _eggs.push_back(egg);
  for (size_t y = 0; y < _map.size(); ++y)
    {
      for (size_t x = 0; x < _map[y].size(); ++x)
	{
	  if (_map[y][x]->pos.x == egg->pos.x && _map[y][x]->pos.y == egg->pos.y)
	    _map[y][x]->eggs += 1;
	}
    }
}

void					GameEngine::manageEbo(Event *event)
{
  manageEdi(event);
}

void					GameEngine::manageEdi(Event *event)
{
   std::vector<t_egg *>::iterator	itEgg;

   for (itEgg = _eggs.begin(); itEgg != _eggs.end(); ++itEgg)
     {
       if ((*itEgg)->id == event->getNbEgg())
	 {
	   for (size_t y = 0; y < _map.size(); ++y)
	     {
	       for (size_t x = 0; x < _map[y].size(); ++x)
		 {
		   if (_map[y][x]->pos.x == (*itEgg)->pos.x && _map[y][x]->pos.y == (*itEgg)->pos.y)
		     _map[y][x]->eggs -= 1;
		 }
	     }
	   delete (*itEgg);
	   _eggs.erase(itEgg);
	   break ;
	 }
     }
}

bool			GameEngine::loopNetworkEvents()
{
  Event			*event = NULL;

  while (_safeEvents->tryPop(&event))
    {
      while (_window.pollEvent(_event))
	{
	  if ((!_safeEvents->getRunning()) || (_event.type == sf::Event::Closed) ||
	      (_event.key.code == sf::Keyboard::Escape))
	    return exitThread();
	}
      if (_mapUpdate[event->getCommandType()] != NULL)
	{
	  (this->*_mapUpdate[event->getCommandType()])(event);
	  delete event;
	}
    }
  return true;
}

bool			GameEngine::update()
{
  if (_endGui || !loopNetworkEvents())
    return false;
  while (_window.pollEvent(_event))
    {
      if (_event.type == sf::Event::KeyPressed)
      	manageKeyboard(_event.key.code);
      else if (_event.type == sf::Event::MouseButtonPressed)
	manageMouse(_event.mouseButton.button);
      else if (_event.type == sf::Event::MouseWheelMoved)
	manageWheelMouse(_event.mouseWheel);
    }
  if ((!_safeEvents->getRunning()) || (_event.type == sf::Event::Closed) ||
      (_event.key.code == sf::Keyboard::Escape))
    exitThread();
  return true;
}

void					GameEngine::start()
{
  sf::Clock				clock;

  try
    {
      if (initialize() == false)
	throw ZappyError::InitError("zappy_gui : initialize Error");
    }
  catch (ZappyError::InitError e)
    {
      std::cerr << e.what() << std::endl;
      exitThread();
      return ;
    }
  _window.draw(*_loading);
  _window.display();
  while (!_safeEvents->getDrawing());
  if (!waitMsz())
    return ;
  usleep(500000);
  _viewback.setViewport(sf::FloatRect(0.f, 0.f, 1.15, 1.15));
  _affText.setViewport(sf::FloatRect(0.05, 0.8, 0.95, 0.95));
  _draw.x = _mapx * 256 / 2;
  _draw.y = _mapy * 256 / 2;
  _view.setCenter(_draw);
  _view.setSize(WIDTH / 2 + _zoom, HEIGHT / 2 + _zoom);
  _pupplayer.restart();
  _pupinfos.restart();
  while (_window.isOpen())
    {
      clock.restart();
      if (!update())
      	return ;
      draw(clock);
    }
}

void					GameEngine::drawRessource(sf::Vector2f const &pos, e_type type,
								  int nb, int *tot)
{
  sf::Vector2f				vec;

  for (int cnt = 0; cnt < nb; ++cnt)
    {
      if (*tot > 16)
	return ;
      vec.x = pos.x + 55 * ((*tot) % 4);
      vec.y = pos.y + 55 * static_cast<int>((*tot) / 4);
      _spriteCorresp[type]->setPosition(vec);
      _window.draw(*_spriteCorresp[type]);
      *tot += 1;
    }
}

inline unsigned int	GameEngine::Max(int a, int b) const
{
  return (std::max(a, b) < 0 ? 0 : std::max(a, b));
}

inline unsigned int	GameEngine::Min(int a, int b) const
{
  return (std::min(a, b) < 0 ? 0 : std::min(a, b));
}

void					GameEngine::drawAllRessources()
{
  int						tot = 0;

  for (size_t y = Max(0, (_draw.y / 256) - 21); y < Min((_draw.y / 256) + 21, _mapy); ++y)
    {
      for (size_t x = Max(0, (_draw.x / 256) - 22); x < Min(_draw.x + 22, _mapx); ++x)
	{
	  tot = 0;
	  _spriteCorresp[_map[y][x]->type]->setPosition(_map[y][x]->pos);
	  _window.draw(*_spriteCorresp[_map[y][x]->type]);
	  drawRessource(_map[y][x]->pos, EGGS, _map[y][x]->eggs, &tot);
	  drawRessource(_map[y][x]->pos, SFOOD, _map[y][x]->food, &tot);
	  drawRessource(_map[y][x]->pos, SLINEMATE, _map[y][x]->linemate, &tot);
	  drawRessource(_map[y][x]->pos, SDERAUMERE, _map[y][x]->deraumere, &tot);
	  drawRessource(_map[y][x]->pos, SSIBUR, _map[y][x]->sibur, &tot);
	  drawRessource(_map[y][x]->pos, SMENDIANE, _map[y][x]->mendiane, &tot);
	  drawRessource(_map[y][x]->pos, SPHIRAS, _map[y][x]->phiras, &tot);
	  drawRessource(_map[y][x]->pos, STHYSTAME, _map[y][x]->thystame, &tot);
	}
    }
}

void					GameEngine::drawLvls(t_player *player)
{
  sf::Vector2f				tmp;

  if (player->incant)
    return ;
  tmp.x = player->pos.x + 30;
  tmp.y = player->pos.y - 128;
  for (int i = 0; i < player->lvl; ++i)
    {
      _spriteCorresp[STAR]->setPosition(tmp);
      _window.draw(*_spriteCorresp[STAR]);
      tmp.y += 30;
    }
}

void					GameEngine::drawBroadCast(sf::Clock const& clock, t_player *player)
{
  sf::Vector2f				vec;

  if (player->hasToBroadCast && !player->isBroadcasting)
    {
      player->countBroadcast = sf::seconds(1.0f);
      player->isBroadcasting = true;
    }
  else if (player->isBroadcasting)
    {
      player->countBroadcast -= clock.getElapsedTime();
      if (player->countBroadcast <= sf::seconds(0.0f))
   	{
   	  player->hasToBroadCast = false;
   	  player->isBroadcasting = false;
   	}
    }
  if (player->hasToBroadCast)
    {
      vec.x = player->pos.x;
      vec.y = player->pos.y - 256;
      _spriteCorresp[DIALOG]->setPosition(vec);
      _window.draw(*_spriteCorresp[DIALOG]);
      vec.x += 60;
      vec.y += 60;
      drawText("***", sf::Vector2f(1.5f, 1.5f), vec, sf::Color::Black);
    }
}

int					GameEngine::getSkin(t_player *player, sf::Clock const& clock)
{
  if (player->incant == true)
    return (static_cast<int>(player->O + 3));
  if (player->egg == true)
    {
      player->countEgg -= clock.getElapsedTime();
      if (player->countEgg <= sf::seconds(0.0f))
	player->egg = false;
      return (static_cast<int>(player->O + 7));
    }
  return (static_cast<int>(player->O - 1));
}

void					GameEngine::drawPlayers(sf::Clock const& clock)
{
  std::vector<t_player *>::iterator	it;
  sf::Vector2f				pos;

  for (it = _players.begin(); it != _players.end(); ++it)
    {
      for (unsigned int i = 0; i < _teams.size(); ++i)
	{
	  if (_teams[i] == (*it)->teamName)
	    _spriteCorresp[PLAYER]->setColor(_teamsColors[i]);
	}
      _spriteCorresp[PLAYER]->setTextureRect(_intRects[getSkin(*it, clock)]);
      _spriteCorresp[PLAYER]->setPosition((*it)->pos);
      _window.draw(*_spriteCorresp[PLAYER]);
      drawLvls(*it);
      drawBroadCast(clock, *it);
    }
}

void					GameEngine::drawText(const std::string &s,
							     const sf::Vector2f &scale,
							     const sf::Vector2f &pos,
							     const sf::Color &color)
{
  _text.setColor(color);
  _text.setPosition(pos);
  _text.setScale(scale);
  _text.setString(s.c_str());
  _window.draw(_text);
}

bool					GameEngine::isPlayer(const std::size_t & i)
{
  return (((_players[i]->pos.x / 256) - 0.5) == _popPlayer.x && ((_players[i]->pos.y / 256) - 0.5) == _popPlayer.y);
}

void					GameEngine::initPopup(bool &init)
{
  sf::Vector2f				tmp(20.f, 20.f);

  _window.setView(_affText);
  _window.draw(*_backPopup);
  for (std::size_t i = 0; i < 6; ++i)
    {
      tmp.y = 5;
      tmp.x = 200 + (i * 90);
      _spriteCorresp[i + 2]->setScale(sf::Vector2f(0.5f, 0.5f));
      _spriteCorresp[i + 2]->setPosition(tmp);
      _window.draw(*_spriteCorresp[i + 2]);
      _spriteCorresp[i + 2]->setScale(sf::Vector2f(1.f, 1.f));
    }
  init = false;
}

void					GameEngine::drawPlayerInfos()
{
  std::stringstream			ss;
  bool					init = true;
  int					stones[6];
  int					draw = 40;

  for (std::size_t i = 0; i != _players.size(); ++i)
    {
      if (isPlayer(i))
      	{
	  if (init)
	    initPopup(init);
	  for (std::size_t j = 0; j != _players[i]->inventory.size(); ++j)
	    stones[j] = _players[i]->inventory[j];
	  ss.str("");
	  ss << _players[i]->teamName << "  " << _players[i]->id;
	  drawText(ss.str(), sf::Vector2f(0.5f, 0.5f), sf::Vector2f(20, draw), sf::Color::White);
	  ss.str("");
	  ss << "\t\t\t\t\t\t\t\t\t\t  " << stones[0] << "\t\t\t\t  " << stones[1] << "\t\t\t\t  "
	     << stones[2] << "\t\t\t\t  " << stones[3] << "\t\t\t\t  " << stones[4] << "\t\t\t\t  "
	     << stones[5] << "\t\t\t\t  " << stones[6];
	  drawText(ss.str(), sf::Vector2f(0.5f, 0.5f), sf::Vector2f(20, draw), sf::Color::White);
	  draw += 20;
      	}
    }
}

void					GameEngine::drawCaseInfos()
{
  std::stringstream			ss;
  sf::Vector2f				tmp;

  _window.setView(_affText);
  _window.draw(*_backPopup);
  for (std::size_t i = 0; i < 8; ++i)
    {
      tmp.y = 10;
      tmp.x = 200 + (i * 90);
      _spriteCorresp[i + 2]->setPosition(tmp);
      _window.draw(*_spriteCorresp[i + 2]);
    }
  ss << "x " << _popInfos.x << "   y " << _popInfos.y;
  drawText(ss.str(), sf::Vector2f(1, 1), sf::Vector2f(20, 20), sf::Color::White);
  ss.str("");
  ss << "INFOS\t\t\t "
     << _map[_popInfos.y][_popInfos.x]->food << "\t\t"
     << _map[_popInfos.y][_popInfos.x]->linemate << "\t\t "
     << _map[_popInfos.y][_popInfos.x]->deraumere << "\t\t"
     << _map[_popInfos.y][_popInfos.x]->sibur << "\t\t"
     << _map[_popInfos.y][_popInfos.x]->mendiane << "\t\t"
     << _map[_popInfos.y][_popInfos.x]->phiras << "\t\t"
     << _map[_popInfos.y][_popInfos.x]->thystame << "\t\t"
     << _map[_popInfos.y][_popInfos.x]->eggs << "\t\t";
  drawText(ss.str(), sf::Vector2f(1, 1), sf::Vector2f(20, 100), sf::Color::White);
}

void					GameEngine::draw(sf::Clock const& clock)
{
  sf::Time				elapsedInfos = _pupinfos.getElapsedTime();
  sf::Time				elapsedPlayer = _pupplayer.getElapsedTime();

  _window.setView(_viewback);
  _window.draw(*_background);

  _view.setCenter(_draw);
  _window.setView(_view);
  drawAllRessources();
  drawPlayers(clock);

  if (_popInfos.x >= 0 && _popInfos.y >= 0 && elapsedInfos.asSeconds() < 3)
    drawCaseInfos();
  if (_popPlayer.x >= 0 && _popPlayer.y >= 0 && elapsedPlayer.asSeconds() < 3)
    drawPlayerInfos();
  _window.setView(_viewback);
  _window.draw(*_plus);
  _window.draw(*_minus);

  _window.setView(_view);
  _window.display();
}
