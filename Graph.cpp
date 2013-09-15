//
// Graph.cpp for arbrePhilo in /home/lcaminon/Documents/projets/arbrePhilo
// 
// Made by Loic Caminondo
// Email   <loic@caminondo.fr>
// 
// Started on  Thu Sep 12 20:46:04 2013 Loic Caminondo
// Last update Mon Sep 16 00:57:32 2013 Loic Caminondo
//

#include		<algorithm>
#include		<fstream>
#include		<iostream>
#include		<cstdlib>
#include		<ctime>
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

  std::cout << "New tree." << std::endl;
  tmp.push_back(new Entity(NULL));
  _entities.push_back(tmp);
  (*tmp.begin())->setPos(sf::Vector2<float>(100, 100));
  replaceEntity();
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
  if (!file.good())
    {
      newTree();
      return;
    }
  std::cout << "Load tree." << std::endl;
  file >> x;
  if (x <= 0)
    {
      std::cout << "Fail." << std::endl;
      newTree();
      return;
    }
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
  replaceEntity();
}

void			Graph::saveToFile(std::string str = "saves/save-")
{
  time_t timer = time(NULL);
  str = str + ctime(&timer);
  std::replace(str.begin(), str.end(), ' ', '-');
  str.erase (str.end()-1);
  std::ofstream file((str + ".tree").c_str(), std::ofstream::out | std::ofstream::trunc);

  std::cout << "Save to file ..." << std::endl;
  file << _entities.size() << "\r";
  for(std::vector<std::vector<Entity*> >::iterator i = _entities.begin(); i != _entities.end();++i)
    {
      file << (*i).size() << "\r";
      for(std::vector<Entity*>::iterator j = (*i).begin(); j != (*i).end();++j)
	file << *(*j);
    }
  file.close();
}

void			Graph::saveToImage()
{
  time_t timer = time(NULL);
  std::string str("shots/shot-");
  str = str + ctime(&timer);
  std::replace(str.begin(), str.end(), ' ', '-');
  str.erase (str.end()-1);
  sf::RenderTexture	texture;
  int height;
  int width;

  replaceEntity();
  height = width = 0;
  for(std::vector<std::vector<Entity*> >::iterator i = _entities.begin(); i != _entities.end();++i)
    {
      for(std::vector<Entity*>::iterator j = (*i).begin(); j != (*i).end();++j)
	{
	  sf::Vector2<float> vect;

	  vect = (*j)->getBotRight();
	  if (height < vect.y)
	    height = vect.y;
	  if (width < vect.x)
	    width = vect.x;
	}
    }  
  texture.create(width, height);
  texture.clear(sf::Color::White);
  for(std::vector<std::vector<Entity*> >::iterator i = _entities.begin(); i != _entities.end();++i)
    {
      for(std::vector<Entity*>::iterator j = (*i).begin(); j != (*i).end();++j)
	{
	  (*j)->draw(texture);
	}
    }
  texture.display();
  std::cout << texture.getTexture().copyToImage().getSize().x << " " << texture.getTexture().copyToImage().getSize().y << std::endl;
  texture.getTexture().copyToImage().saveToFile((str + ".jpg").c_str());
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
	  replaceEntity();
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
	  replaceEntity();
	}
    }
}
