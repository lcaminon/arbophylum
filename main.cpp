//
// main.cpp for pareil in /home/lcaminon/Documents/projets/pareil
// 
// Made by Loic Caminondo
// Email   <loic@caminondo.fr>
// 
// Started on  Sat Sep  7 16:46:53 2013 Loic Caminondo
// Last update Sun Sep 15 22:26:47 2013 Loic Caminondo
//

#include	<SFML/Graphics.hpp>
#include	<SFML/System.hpp>
#include	<iostream>
#include	"Graph.hh"
#include	"Ressources.hh"

int main(int ac, char **av)
{
  sf::Clock clock;
  Graph *graph;
  Ressources *ressources;
  sf::RenderWindow window(sf::VideoMode(800, 600), L"Arbre Phylogénétique", sf::Style::Default);

  ressources = Ressources::getInstance();
  if (ressources->load())
    {
      graph = Graph::getInstance();
      if (ac != 1)
	graph->loadTree(av[1]);
      else
	graph->newTree();
      while (window.isOpen())
	{
	  graph->gestEvent(window, clock.restart());
	  window.clear(sf::Color::White);
	  graph->draw(window);
	  window.display();
	}
    }
  graph->kill();
  ressources->kill();
  return 0;
}
