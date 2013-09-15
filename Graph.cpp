//
// Graph.cpp for arbrePhilo in /home/lcaminon/Documents/projets/arbrePhilo
// 
// Made by Loic Caminondo
// Email   <loic@caminondo.fr>
// 
// Started on  Thu Sep 12 20:46:04 2013 Loic Caminondo
// Last update Sun Sep 15 22:38:40 2013 Loic Caminondo
//

#include		<fstream>
#include		<iostream>
#include		<cstdlib>
#include		"Graph.hh"

Graph::Graph()
{
  _target = NULL;
}

Graph::~Graph()
{
  for(std::vector<std::vector<Entity*> >::iterator i = _entities.begin(); i != _entities.end();++i)
    {
      for(std::vector<Entity*>::iterator j = (*i).begin(); j != (*i).end();++j)
	{
	  delete *j;
	}
    }
}

void			Graph::newTree()
{
  std::vector<Entity*> tmp;

  tmp.push_back(new Entity(NULL));
  _entities.push_back(tmp);
  (*tmp.begin())->setPos(sf::Vector2<float>(100, 100));
}

void			Graph::loadTree(char *filename)
{
  int x;
  int y;
  void *tmpaddr;
  void *tmpfather;
  std::map<void *, Entity *> readdr;
  std::ifstream file(filename, std::ifstream::in);

  readdr[NULL] = NULL;
  file >> x;
  _entities.resize(x);
  x = -1;
  while (++x < _entities.size())
    {
      file >> y;
      _entities[x].resize(y);
      y = -1;
      while (++y < _entities[x].size())
	{
	  file >> tmpaddr;
	  file >> tmpfather;
	  _entities[x][y] = readdr[tmpaddr] = new Entity(readdr[tmpfather]);
	  _entities[x][y]->deserialize(file);
	}
    }
}

void			Graph::saveToFile()
{
  std::ofstream		file("saves/save.tree", std::ofstream::out);

  file << _entities.size() << "\r";
  for(std::vector<std::vector<Entity*> >::iterator i = _entities.begin(); i != _entities.end();++i)
    {
      file << (*i).size() << "\r";
      for(std::vector<Entity*>::iterator j = (*i).begin(); j != (*i).end();++j)
	file << *(*j);
    }
}

void			Graph::saveToImage()
{
  
}

void			Graph::replaceEntity()
{
  int			width;
  int			heightTotal;

  width = heightTotal = 0;
  for(std::vector<std::vector<Entity*> >::iterator i = _entities.begin(); i != _entities.end();++i)
    {
      int		heightLocal;

      heightLocal = 0;
      for(std::vector<Entity*>::iterator j = (*i).begin(); j != (*i).end();++j)
	{
	  heightLocal += (*j)->getHeight();
	}
      if (heightLocal > heightTotal)
	heightTotal = heightLocal;
    }
  for(std::vector<std::vector<Entity*> >::iterator i = _entities.begin(); i != _entities.end();++i)
    {
      int		height;
      int		heightLocal;
      int		widthLocal;

      widthLocal = heightLocal = 0;
      for(std::vector<Entity*>::iterator j = (*i).begin(); j != (*i).end();++j)
	{
	  heightLocal += (*j)->getHeight();
	  if ((*j)->getWidth() > widthLocal)
	    widthLocal = (*j)->getWidth();
	}
      height = heightLocal = (heightTotal - heightLocal) / ((*i).size() + 1);
      for(std::vector<Entity*>::iterator j = (*i).begin(); j != (*i).end();++j)
	{
	  (*j)->setPos(sf::Vector2<float>(width, height));
	  height += (*j)->getHeight() + heightLocal;
	}
      width += widthLocal + 100; // 100 = valeur pour les lignes
    }
}

void			Graph::draw(sf::RenderWindow &window)
{
  replaceEntity();
  for(std::vector<std::vector<Entity*> >::iterator i = _entities.begin(); i != _entities.end();++i)
    {
      for(std::vector<Entity*>::iterator j = (*i).begin(); j != (*i).end();++j)
	{
	  (*j)->draw(window);
	}
    }
}

Entity			*Graph::addEntity(Entity *father)
{
  int			pos;
  Entity		*entity;

  entity = new Entity(father);
  pos = father->getPos() + 1;
  if (pos == _entities.size())
    {
      std::vector<Entity*> tmp;
      _entities.push_back(tmp);
    }
  _entities[pos].push_back(entity);
  return (entity);
}

void			Graph::delEntity(Entity *entity)
{
  for(std::vector<std::vector<Entity*> >::iterator i = _entities.begin(); i != _entities.end();++i)
    {
      for(std::vector<Entity*>::iterator j = (*i).begin(); j != (*i).end();++j)
	{
	  if (*j == entity)
	    {
	      (*i).erase(j);
	      if ((*i).empty())
		_entities.erase(i);
	      delete entity;
	      return;
	    }
	}
    }
  delete entity;
}

void			Graph::moveToUp(Entity *entity)
{
}

void			Graph::gestEvent(sf::RenderWindow &window, sf::Time time)
{
  sf::Event event;
  sf::View view;

  view = window.getView();
  view.move((-sf::Keyboard::isKeyPressed(sf::Keyboard::Left) + sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) * time.asSeconds() * 1000, (-sf::Keyboard::isKeyPressed(sf::Keyboard::Up) + sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) * time.asSeconds() * 1000);
  window.setView(view);
  while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Resized)
	{
	  sf::View view;

	  view = window.getView();
	  view.setSize(event.size.width, event.size.height);
	  window.setView(view);
	}
      if (event.type == sf::Event::Closed)
	window.close();
      if (event.type == sf::Event::TextEntered)
      	{
	  if (_target != NULL)
	    _target->write(event.text.unicode);
      	}
      
      if (event.type == sf::Event::KeyPressed)
	{
	  if (event.key.code == sf::Keyboard::Escape)
	    window.close();
	  if (event.key.code == sf::Keyboard::F1)
	    saveToFile();
	  if (event.key.code == sf::Keyboard::F2)
	    saveToImage();
	}
      if (event.type == sf::Event::MouseButtonPressed)
	{
	  if (event.mouseButton.button == sf::Mouse::Left)
	    {
	      bool inside = false;

	      for(std::vector<std::vector<Entity*> >::iterator i = _entities.begin(); !inside && i != _entities.end();++i)
		{
		  for(std::vector<Entity*>::iterator j = (*i).begin(); !inside && j != (*i).end();++j)
		    {
		      State state;

		      state = (*j)->inside(window.mapPixelToCoords(sf::Vector2<int>(event.mouseButton.x, event.mouseButton.y)));
		      if (state == INSIDE)
			{
			  inside = true;
			  _target = *j;
			}
		      else if (state == KILLME)
			{
			  inside = true;
			  delete (*j);
			  (*i).erase(j);
			  if ((*i).empty())
			    _entities.erase(i);
			}
		    }
		}
	      if (!inside)
		_target = NULL;
	    }
	}
    }
}
