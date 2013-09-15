//
// Ressources.hh for arbrePhilo in /home/lcaminon/Documents/projets/arbrePhilo
// 
// Made by Loic Caminondo
// Email   <loic@caminondo.fr>
// 
// Started on  Thu Sep 12 09:16:11 2013 Loic Caminondo
// Last update Fri Sep 13 14:19:40 2013 Loic Caminondo
//

#ifndef				RESSOURCES_HH
#define				RESSOURCES_HH

#include			<SFML/Graphics.hpp>
#include			<vector>
#include			<string>
#include			"Singleton.hh"

enum				Type
  {
    PLUS,
    MINUS
  };

class				Ressources : public Singleton<Ressources>
{
  sf::Font			_font;
  std::map<Type, sf::Texture*>	_texture;
public:
  Ressources();
  ~Ressources();
  bool load();
  sf::Font *getFont();
  sf::Texture *getTexture(Type type);
};

#endif
