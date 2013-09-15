//
// Entity.hh for arbrePhilo in /home/lcaminon/Documents/projets/arbrePhilo
// 
// Made by Loic Caminondo
// Email   <loic@caminondo.fr>
// 
// Started on  Thu Sep 12 08:56:53 2013 Loic Caminondo
// Last update Sun Sep 15 22:20:40 2013 Loic Caminondo
//

#ifndef			ENTITY_HH
#define			ENTITY_HH

#include		<SFML/Graphics.hpp>
#include		<SFML/System.hpp>
#include		<iostream>
#include		<fstream>
#include		<vector>
#include		"Graph.hh"

class			Graph;

enum			State
  {
    INSIDE,
    OUTSIDE,
    KILLME
  };

class			Entity
{
  sf::Vertex		_line[2];
  sf::RectangleShape	_rect;
  sf::Sprite		_plus;
  sf::Sprite		_minus;
  sf::Text		_title;
  sf::Text		_def;
  sf::Text		*_target;
  Graph			*_graph;
  int			_pos;
  Entity		*_father;
  std::vector<Entity*>	_sons;

  void setRect();
public:
  Entity(Entity *father);
  ~Entity();
  void draw(sf::RenderWindow &window);
  void setPos(sf::Vector2<float> pos);
  int getPos();
  int getHeight();
  int getWidth();
  State inside(sf::Vector2<float> pos);
  void addSon(Entity *son);
  void delSon(Entity *son);
  void newFather(Entity *father);
  void write(wchar_t c);
  sf::Vector2<float> getAnchor();
  void serialize(std::ostream& out) const;
  void deserialize(std::istream& in);
};

std::ostream& operator<<(std::ostream& out, const Entity& entity);

#endif
