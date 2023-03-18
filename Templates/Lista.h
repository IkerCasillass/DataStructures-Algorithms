#ifndef _LISTA_H_
#define _LISTA_H_

#include <iostream>
#include <vector>

const int MAX = 100;

template <class T> class Lista {

private:
  std::vector<T> data;
  int currentSize;

public:
  Lista();
  ~Lista();
  bool insert(T value);
  // TO-DO
  void erase();
  T getData(int indice);
  int getCurrentSize();
  void print();
};

template <class T> Lista<T>::Lista() {
  data.clear();
  currentSize = 0;
}

template <class T> Lista<T>::~Lista() {
  data.clear();
  currentSize = 0;
}

template <class T> bool Lista<T>::insert(T value) {
  if (currentSize < MAX) {
    data.push_back(value);
    currentSize++;
    return true;
  } else
    return false;
}

template <class T> void Lista<T>::print() {
  std::cout << "Contenido de la lista" << std::endl;
  for (int i = 0; i < currentSize; i++) {
    std::cout << "[" << i << "] -- " << data[i] << std::endl;
  }
}

// Metodos tarea

template <class T> void Lista<T>::erase() {
  if (currentSize > 0) {
    std::cout << data[currentSize-1] << std::endl;
    currentSize--;
  }
  else{
    std::cout << "NO HAY ELEMENTOS" << std::endl;
  }
}

template <class T> T Lista<T>::getData(int indice) {
  if (0 <= indice && indice < currentSize) {
    return data[indice];
  }
}

template <class T> int Lista<T>::getCurrentSize() {
  return currentSize;
}

#endif // _LISTA_H_