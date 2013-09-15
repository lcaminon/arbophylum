//
// Graph.hh for arbrePhilo in /home/lcaminon/Documents/projets/arbrePhilo
// 
// Made by Loic Caminondo
// Email   <loic@caminondo.fr>
// 
// Started on  Thu Sep 12 09:31:01 2013 Loic Caminondo
// Last update Sun Sep 15 23:20:28 2013 Loic Caminondo
//

#ifndef			GRAPH_HH
#define			GRAPH_HH

#include		<vector>
#include		"Singleton.hh"
#include		"Entity.hh"

class			Entity;

class			Graph : public Singleton<Graph>
{
  Entity *_target;
  std::vector<std::vector<Entity*> > _entities;

  void saveToFile(std::string str);
  void saveToImage();
  void replaceEntity();
public:
  Graph();
  ~Graph();
  void newTree();
  void loadTree(char *filename);
  void draw(sf::RenderWindow &window);
  Entity *addEntity(Entity *father);
  void delEntity(Entity *entity);
  void moveToUp(Entity *entity);
  void gestEvent(sf::RenderWindow &window, sf::Time time);
};

#endif
