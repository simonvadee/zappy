//
// AssetsManager.cpp for zappy in /home/bouca-_d/rendu/Zappy/Graphic
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:11:18 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:11:18 2015 Dany Bouca Nova
//

#include "AssetsManager.hh"
#include <SFML/Graphics/Texture.hpp>

AssetsManager*	AssetsManager::_assetsManager = NULL;

AssetsManager::AssetsManager()
{
  _texLoading = new sf::Texture();
  _texFirst = new sf::Texture();
  _texSecond = new sf::Texture();
  _texBackground = new sf::Texture();
  _texPlus = new sf::Texture();
  _texMinus = new sf::Texture();
  _texFood = new sf::Texture();
  _texLinemate = new sf::Texture();
  _texDeraumere = new sf::Texture();
  _texSibur = new sf::Texture();
  _texMendiane = new sf::Texture();
  _texPhiras = new sf::Texture();
  _texThystame = new sf::Texture();
  _texEgg = new sf::Texture();
  _texPlayer = new sf::Texture();
  _texStar = new sf::Texture();
  _texDialog = new sf::Texture();
  _texGameOver = new sf::Texture();

  _food = new sf::Sprite();
  _linemate = new sf::Sprite();
  _deraumere = new sf::Sprite();
  _sibur = new sf::Sprite();
  _mendiane = new sf::Sprite();
  _phiras = new sf::Sprite();
  _thystame = new sf::Sprite();
  _egg = new sf::Sprite();
  _loading = new sf::Sprite();
  _grassFirst = new sf::Sprite();
  _grassSecond = new sf::Sprite();
  _background = new sf::Sprite();
  _plus = new sf::Sprite();
  _minus = new sf::Sprite();
  _player = new sf::Sprite();
  _star = new sf::Sprite();
  _dialog = new sf::Sprite();
  _gameOver = new sf::Sprite();

  _font = new sf::Font();
  _popup = new sf::RectangleShape();

  if (!(_texLoading->loadFromFile("./Graphic/Resources/loading.jpg")) ||
      !(_texFirst->loadFromFile("./Graphic/Resources/grass1.jpg")) ||
      !(_texSecond->loadFromFile("./Graphic/Resources/grass2.jpg")) ||
      !(_texBackground->loadFromFile("./Graphic/Resources/background.png")) ||
      !(_texPlus->loadFromFile("./Graphic/Resources/plus.png")) ||
      !(_texMinus->loadFromFile("./Graphic/Resources/minus.png")) ||
      !(_texFood->loadFromFile("./Graphic/Resources/food.png")) ||
      !(_texLinemate->loadFromFile("./Graphic/Resources/linemate.png")) ||
      !(_texDeraumere->loadFromFile("./Graphic/Resources/deraumere.png")) ||
      !(_texSibur->loadFromFile("./Graphic/Resources/sibur.png")) ||
      !(_texMendiane->loadFromFile("./Graphic/Resources/mendiane.png")) ||
      !(_texPhiras->loadFromFile("./Graphic/Resources/phiras.png")) ||
      !(_texThystame->loadFromFile("./Graphic/Resources/thystame.png")) ||
      !(_texEgg->loadFromFile("./Graphic/Resources/egg.png")) ||
      !(_texPlayer->loadFromFile("./Graphic/Resources/character.png")) ||
      !(_texStar->loadFromFile("./Graphic/Resources/star.png")) ||
      !(_texDialog->loadFromFile("./Graphic/Resources/bulle-texte.png")) ||
      !(_texGameOver->loadFromFile("./Graphic/Resources/end.png")) ||
      !(_font->loadFromFile("./Graphic/Resources/28DaysLater.ttf")))
    throw ZappyError::InitError("zappy_gui : Error to load ressources");

  _texMinus->setSmooth(true);
  _texPlus->setSmooth(true);

  _popup->setSize(sf::Vector2f(950, 900 / 5));
  _plus->setScale(sf::Vector2f(0.5, 0.5));
  _minus->setScale(sf::Vector2f(0.5, 0.5));
  _popup->setFillColor(sf::Color(0, 0, 0, 128));

  _loading->setTexture(*_texLoading);
  _grassFirst->setTexture(*_texFirst);
  _grassSecond->setTexture(*_texSecond);
  _background->setTexture(*_texBackground);
  _plus->setTexture(*_texPlus);
  _minus->setTexture(*_texMinus);
  _food->setTexture(*_texFood);
  _linemate->setTexture(*_texLinemate);
  _deraumere->setTexture(*_texDeraumere);
  _sibur->setTexture(*_texSibur);
  _mendiane->setTexture(*_texMendiane);
  _phiras->setTexture(*_texPhiras);
  _thystame->setTexture(*_texThystame);
  _egg->setTexture(*_texEgg);
  _player->setTexture(*_texPlayer);
  _star->setTexture(*_texStar);
  _dialog->setTexture(*_texDialog);
  _gameOver->setTexture(*_texGameOver);
}

AssetsManager::~AssetsManager()
{
  delete _texFood;
  delete _texLinemate;
  delete _texDeraumere;
  delete _texSibur;
  delete _texMendiane;
  delete _texPhiras;
  delete _texThystame;
  delete _texEgg;
  delete _texPlayer;
  delete _texStar;
  delete _texDialog;
  delete _texGameOver;

  delete _texLoading;
  delete _texFirst;
  delete _texSecond;
  delete _texBackground;
  delete _texPlus;
  delete _texMinus;

  delete _food;
  delete _linemate;
  delete _deraumere;
  delete _sibur;
  delete _mendiane;
  delete _phiras;
  delete _thystame;
  delete _egg;
  delete _player;
  delete _star;
  delete _dialog;
  delete _gameOver;

  delete _loading;
  delete _grassFirst;
  delete _grassSecond;
  delete _background;
  delete _plus;
  delete _minus;

  delete _font;
  delete _popup;
}

void		AssetsManager::instanciateAssetsManager()
{
  if (_assetsManager == NULL)
    _assetsManager = new AssetsManager();
}

void		AssetsManager::destroyAssetsManager()
{
  if (_assetsManager != NULL)
    {
      delete _assetsManager;
      _assetsManager = NULL;
    }
}

sf::Sprite*	AssetsManager::getFood()
{
  return (_assetsManager == NULL ? NULL :_assetsManager->_food);
}

sf::Sprite*	AssetsManager::getLinemate()
{
  return (_assetsManager == NULL ? NULL :_assetsManager->_linemate);
}

sf::Sprite*	AssetsManager::getDeraumere()
{
  return (_assetsManager == NULL ? NULL :_assetsManager->_deraumere);
}

sf::Sprite*	AssetsManager::getSibur()
{
  return (_assetsManager == NULL ? NULL :_assetsManager->_sibur);
}

sf::Sprite*	AssetsManager::getMendiane()
{
  return (_assetsManager == NULL ? NULL :_assetsManager->_mendiane);
}

sf::Sprite*	AssetsManager::getPhiras()
{
  return (_assetsManager == NULL ? NULL :_assetsManager->_phiras);
}

sf::Sprite*	AssetsManager::getThystame()
{
  return (_assetsManager == NULL ? NULL :_assetsManager->_thystame);
}

sf::Sprite*	AssetsManager::getEgg()
{
  return (_assetsManager == NULL ? NULL :_assetsManager->_egg);
}

sf::Sprite*	AssetsManager::getLoading()
{
  return (_assetsManager == NULL ? NULL :_assetsManager->_loading);
}

sf::Sprite*	AssetsManager::getGrassFirst()
{
  return (_assetsManager == NULL ? NULL :_assetsManager->_grassFirst);
}

sf::Sprite*	AssetsManager::getGrassSecond()
{
  return (_assetsManager == NULL ? NULL :_assetsManager->_grassSecond);
}

sf::Sprite*	AssetsManager::getBackground()
{
  return (_assetsManager == NULL ? NULL :_assetsManager->_background);
}

sf::Sprite*	AssetsManager::getPlus()
{
  return (_assetsManager == NULL ? NULL :_assetsManager->_plus);
}

sf::Sprite*	AssetsManager::getMinus()
{
  return (_assetsManager == NULL ? NULL :_assetsManager->_minus);
}

sf::Sprite*	AssetsManager::getPlayer()
{
  return (_assetsManager == NULL ? NULL :_assetsManager->_player);
}

sf::Sprite*	AssetsManager::getStar()
{
  return (_assetsManager == NULL ? NULL :_assetsManager->_star);
}

sf::Sprite*	AssetsManager::getDialog()
{
  return (_assetsManager == NULL ? NULL :_assetsManager->_dialog);
}

sf::Sprite*	AssetsManager::getGameOver()
{
  return (_assetsManager == NULL ? NULL :_assetsManager->_gameOver);
}

sf::Font*	AssetsManager::getFont()
{
  return (_assetsManager == NULL ? NULL :_assetsManager->_font);
}

sf::RectangleShape*	AssetsManager::getPopup()
{
  return (_assetsManager == NULL ? NULL :_assetsManager->_popup);
}
