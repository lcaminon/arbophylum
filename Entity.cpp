//
// Entity.cpp for arbrePhilo in /home/lcaminon/Documents/projets/arbrePhilo
// 
// Made by Loic Caminondo
// Email   <loic@caminondo.fr>
// 
// Started on  Thu Sep 12 22:34:52 2013 Loic Caminondo
// Last update Mon Sep 16 00:52:49 2013 Loic Caminondo
//

#include		"Graph.hh"
#include		"Ressources.hh"
#include		"Entity.hh"

Entity::Entity(Entity *father)
{
  Ressources *ressources;

  _father = father;
  ressources = Ressources::getInstance();
  _title.setFont(*ressources->getFont());
  _title.setString("Empty title");
  _title.setCharacterSize(20);
  _title.setColor(sf::Color::Black);
  _title.setStyle(sf::Text::Bold);
  _def.setFont(*ressources->getFont());
  _def.setString("Empty definition");
  _def.setCharacterSize(12);
  _def.setColor(sf::Color::Black);
  _def.setStyle(sf::Text::Italic);
  _rect.setFillColor(sf::Color::White);
  _rect.setOutlineColor(sf::Color::Black);
  _rect.setOutlineThickness (1);
  _target = NULL;
  setRect();
  _plus.setTexture(*ressources->getTexture(PLUS));
  _minus.setTexture(*ressources->getTexture(MINUS));
  _line[0].color = sf::Color::Black;
  _line[1].color = sf::Color::Black;
}

Entity::~Entity()
{
  Graph			*graph;

  graph = Graph::getInstance();
  for(std::vector<Entity*>::iterator i = _sons.begin(); i != _sons.end();++i)
    {
      graph->delEntity((*i));
    }
}

sf::Vector2<float>	Entity::getBotRight()
{
  sf::Vector2<float>	vect;

  vect.x = _rect.getGlobalBounds().left + _rect.getGlobalBounds().width;
  vect.y = _rect.getGlobalBounds().top + _rect.getGlobalBounds().height;
  return (vect);
}

void			Entity::write(wchar_t c)
{
  std::wstring tmp;

  tmp = _target->getString();
  if (c == 8)
    {
      if (!tmp.empty())
	tmp.erase(tmp.end() - 1);
    }
  else
    {
      if (c == 13)
	c = 10;
      tmp.push_back(c);
    }
  _target->setString(tmp);
}

void			Entity::setRect()
{
  float			width;
  float			height;

  width = 50;
  _def.setPosition(_title.getGlobalBounds().left + 10, _title.getGlobalBounds().top + _title.getLocalBounds().height + 15);
  if (_title.getLocalBounds().width + 15 > 45 || _def.getLocalBounds().width + 20 > 50)
    if ((width = _title.getLocalBounds().width + 10) < _def.getLocalBounds().width + 20)
      width = _def.getLocalBounds().width + 20;
  height = _title.getLocalBounds().height + _def.getLocalBounds().height + 40;
  _rect.setPosition(_title.getPosition() - sf::Vector2<float>(5, 5));
  _rect.setSize(sf::Vector2<float>(width, height));
  _plus.setPosition(_rect.getGlobalBounds().left, _rect.getGlobalBounds().top + _rect.getGlobalBounds().height);
  _minus.setPosition(_plus.getGlobalBounds().left + _plus.getGlobalBounds().width, _plus.getGlobalBounds().top);
}

void			Entity::draw(sf::RenderTarget &render)
{
  render.draw(_rect);
  if (_target != NULL)
    {
      _rect.setPosition(sf::Vector2<float>(_target->getPosition().x - 3, _target->getPosition().y));
      _rect.setSize(sf::Vector2<float>(_target->getLocalBounds().width + 6, _target->getLocalBounds().height + 15));
      render.draw(_rect);
      setRect();
      render.draw(_plus);
      render.draw(_minus);
    }
  render.draw(_title);
  render.draw(_def);
  if (_father != NULL)
    {
      _line[0].position = sf::Vector2<float>(_rect.getGlobalBounds().left, _rect.getGlobalBounds().top + _rect.getGlobalBounds().height / 2);
      _line[1].position = _father->getAnchor();
      render.draw(_line, 2, sf::Lines);
    }
}

void			Entity::setPos(sf::Vector2<float> pos)
{
  _title.setPosition(pos);
  setRect();
}

int			Entity::getPos()
{
  if (_father == NULL)
    return (0);
  return (_father->getPos() + 1);
}

int			Entity::getHeight()
{
  int			height;

  height = _rect.getGlobalBounds().height; 
  if (_plus.getGlobalBounds().height > _minus.getGlobalBounds().height)
    height += _plus.getGlobalBounds().height;
  else
    height += _minus.getGlobalBounds().height;
  return (height);
}

int			Entity::getWidth()
{
  return (_rect.getGlobalBounds().width);
}

State			Entity::inside(sf::Vector2<float> pos)
{
  Graph			*graph;
  sf::Rect<float>	rect;

  graph = Graph::getInstance();
  rect = _rect.getGlobalBounds();
  if (rect.contains(pos))
    {
      if (pos.y < rect.top + rect.height / 2)
	_target = &_title;
      else
	_target = &_def;
      return (INSIDE);
    }
  if (_plus.getGlobalBounds().contains(pos))
    {
      _sons.push_back(graph->addEntity(this));
      return (INSIDE);
    }
  else if (_minus.getGlobalBounds().contains(pos))
    return (KILLME);
  _target = NULL;
  return (OUTSIDE);
}

void			Entity::addSon(Entity *son)
{
}

void			Entity::delSon(Entity *son)
{
}

void			Entity::newFather(Entity *father)
{
}

sf::Vector2<float>	Entity::getAnchor()
{
  sf::Rect<float>	rect;

  rect = _rect.getGlobalBounds();
  return (sf::Vector2<float>(rect.left + rect.width, rect.top + rect.height / 2));
}

void			Entity::serialize(std::ostream& out) const
{
  out << this << "\r";
  out << _father << "\r";
  out << static_cast<std::string>(_title.getString()) << "\r";
  out << static_cast<std::string>(_def.getString()) << "\r";
}

void			Entity::deserialize(std::istream& in)
{
  std::string		title;
  std::string		def;

  in.ignore(1, '\r');
  std::getline(in, title, '\r');
  std::getline(in, def, '\r');
  _title.setString(title);
  _def.setString(def);
}

std::ostream&		operator<<(std::ostream& out, const Entity& entity)
{
  entity.serialize(out);
  return (out);
}
