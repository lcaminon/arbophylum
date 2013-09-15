//
// Singleton.cpp for arbre in /home/lcaminon/Documents/projets/arbrePhilo
// 
// Made by Loic Caminondo
// Email   <loic@caminondo.fr>
// 
// Started on  Thu Sep 12 18:36:26 2013 Loic Caminondo
// Last update Thu Sep 12 23:42:09 2013 Loic Caminondo
//

#include		"Singleton.hh"

template <typename T>
Singleton<T>::Singleton()
{
}

template <typename T>
Singleton<T>::~Singleton()
{
}

template <typename T>
T *Singleton<T>::getInstance()
{
  if (NULL == _singleton)
    _singleton = new T;
  return (static_cast<T*> (_singleton));
}

template <typename T>
void Singleton<T>::kill()
{
  if (NULL != _singleton)
    {
      delete _singleton;
      _singleton = NULL;
    }
}
