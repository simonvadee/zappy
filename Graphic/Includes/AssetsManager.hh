//
// AssetsManager.hh for zappy in /home/bouca-_d/rendu/Zappy/Graphic
//
// Made by Dany Bouca Nova
// Login   <bouca-_d@epitech.net>
//
// Started on  Sun Jul  5 02:15:31 2015 Dany Bouca Nova
// Last update Sun Jul  5 02:15:35 2015 Dany Bouca Nova
//

#ifndef ASSETS_MANAGER_HH
# define ASSETS_MANAGER_HH

# include <iostream>
# include <SFML/Window.hpp>
# include <SFML/Graphics/Sprite.hpp>
# include <SFML/Graphics/RectangleShape.hpp>
# include <SFML/Graphics/Font.hpp>
# include "Exceptions.hpp"

class			AssetsManager {
  /* Pointer to Singleton Instance */
private :
  static AssetsManager*	_assetsManager;

  /* Unique attributes heap allocation */

  sf::Font*		_font;
  sf::RectangleShape*	_popup;

  sf::Sprite*		_loading;
  sf::Sprite*		_grassFirst;
  sf::Sprite*		_grassSecond;
  sf::Sprite*		_background;
  sf::Sprite*		_plus;
  sf::Sprite*		_minus;
  sf::Sprite*		_dialog;
  sf::Sprite*		_gameOver;

  sf::Sprite*		_food;
  sf::Sprite*		_linemate;
  sf::Sprite*		_deraumere;
  sf::Sprite*		_sibur;
  sf::Sprite*		_mendiane;
  sf::Sprite*		_phiras;
  sf::Sprite*		_thystame;
  sf::Sprite*		_egg;
  sf::Sprite*		_player;
  sf::Sprite*		_star;

  sf::Texture*		_texFood;
  sf::Texture*		_texLinemate;
  sf::Texture*		_texDeraumere;
  sf::Texture*		_texSibur;
  sf::Texture*		_texMendiane;
  sf::Texture*		_texPhiras;
  sf::Texture*		_texThystame;
  sf::Texture*		_texEgg;
  sf::Texture*		_texPlayer;
  sf::Texture*		_texStar;
  sf::Texture*		_texDialog;
  sf::Texture*		_texGameOver;

  sf::Texture*		_texLoading;
  sf::Texture*		_texFirst;
  sf::Texture*		_texSecond;
  sf::Texture*		_texBackground;
  sf::Texture*		_texPlus;
  sf::Texture*		_texMinus;

  /* Private Constructors for access in the scope only */
private :
  AssetsManager();
  ~AssetsManager();

  /* Singleton Methods for instanciation and destruction */
public :
  static void			instanciateAssetsManager();
  static void			destroyAssetsManager();

  /* Models Getters */
  static sf::Sprite*		getFood();
  static sf::Sprite*		getLinemate();
  static sf::Sprite*		getDeraumere();
  static sf::Sprite*		getSibur();
  static sf::Sprite*		getMendiane();
  static sf::Sprite*		getPhiras();
  static sf::Sprite*		getThystame();
  static sf::Sprite*		getEgg();

  static sf::RectangleShape*	getPopup();
  static sf::Font*		getFont();
  static sf::Sprite*		getLoading();
  static sf::Sprite*		getGrassFirst();
  static sf::Sprite*		getGrassSecond();
  static sf::Sprite*		getBackground();
  static sf::Sprite*		getPlus();
  static sf::Sprite*		getMinus();
  static sf::Sprite*		getPlayer();
  static sf::Sprite*		getStar();
  static sf::Sprite*		getDialog();
  static sf::Sprite*		getGameOver();
};

#endif /* !ASSETS_MANAGER_HH */
