//
// Singleton.hh for arbre in /home/lcaminon/Documents/projets/arbrePhilo
// 
// Made by Loic Caminondo
// Email   <loic@caminondo.fr>
// 
// Started on  Thu Sep 12 18:35:10 2013 Loic Caminondo
// Last update Fri Sep 13 00:41:01 2013 Loic Caminondo
//

#ifndef			SINGLETON_HH
#define			SINGLETON_HH

#include		<cstdlib>

template <typename T>
class Singleton
{
protected:
  // Constructeur/destructeur
  Singleton();
  ~Singleton();

public:
  // Interface publique
  static T *getInstance();
  static void kill();

private:
  // Unique instance
  static T *_singleton;
};

template <typename T>
T *Singleton<T>::_singleton = NULL;

#include		"Singleton.tpp"

#endif
