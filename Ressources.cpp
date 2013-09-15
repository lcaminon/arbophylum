//
// Ressources.cpp for arbrePhilo in /home/lcaminon/Documents/projets/arbrePhilo
// 
// Made by Loic Caminondo
// Email   <loic@caminondo.fr>
// 
// Started on  Fri Sep 13 12:41:32 2013 Loic Caminondo
// Last update Fri Sep 13 20:05:40 2013 Loic Caminondo
//

#include		<iostream>
#include		"Ressources.hh"

Ressources::Ressources()
{
}

Ressources::~Ressources()
{
  delete _texture[PLUS];
  delete _texture[MINUS];
  std::cout << "Ressources free." << std::endl;
}

bool			Ressources::load()
{
    if (!_font.loadFromFile("ressources/VerilySerifMono.otf"))
    {
      std::cerr << "Loading font failure." << std::endl;
      return (false);
    }
    _texture[PLUS] = new sf::Texture;
    _texture[MINUS] = new sf::Texture;
    if (!_texture[PLUS]->loadFromFile("ressources/plus.png"))
      {
	std::cerr << "Loading plus.png failure." << std::endl;
	return (false);
      }
    if (!_texture[MINUS]->loadFromFile("ressources/moins.jpg"))
      {
	std::cerr << "Loading moins.jpg failure." << std::endl;
	return (false);
      }
    std::cout << "Loading ressources success !" << std::endl;
    return (true);
}

sf::Font		*Ressources::getFont()
{
  return (&_font);
}

sf::Texture		*Ressources::getTexture(Type type)
{
  return (_texture[type]);
}
