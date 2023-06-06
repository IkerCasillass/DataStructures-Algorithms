#ifndef __OPENHASH_H_
#define __OPENHASH_H_

#include <iostream>
#include <vector>
#include <stdexcept>
#include <list>

template<class K, class T>
class OpenHash {
  private:
    //Paginas de consulta para std::list (funciona como linked list)
    // https://www.geeksforgeeks.org/list-cpp-stl/
    // https://cplusplus.com/reference/list/list/

    std::vector<std::list<std::pair<K, T>>> table; 
    int numElements;
    int maxSize; 
    

  public:
    OpenHash(int selectedMaxSize);
    int getHashIndex(K keyVal);
    int getNumElements();
    void print();
    void add(K keyVal, T value);
    T find(K keyVal);
    void remove(K keyVal);
    T getDataAt(int index); // para find
 

};

template<class K, class T>
OpenHash<K, T>::OpenHash(int selectedMaxSize) {
  maxSize = selectedMaxSize;
  numElements = 0;
  table = std::vector<std::list<std::pair<K, T>>> (maxSize); 
}

template<class K, class T>
int OpenHash<K, T>::getHashIndex(K keyVal) {
  return keyVal % maxSize;
}

template<class K, class T>
int OpenHash<K, T>::getNumElements() {
  return numElements;
}

template<class K, class T>
T OpenHash<K, T>::getDataAt(int index) {
  
  int hashVal = getHashIndex(index); 
  
  std::list<std::pair<K, T>>& lista = table[hashVal];

  // Si el indice es valido
  if(index >= 0 && index <(int)lista.size()){
    
    // Definir iterador
    auto it = lista.begin();
    // Avanzar iterador
    std::advance(it, index); 
    // Acceder a data
    T data = it->second;
    
    return data;
  }
  else {
    return "Indice no valido";
  }
}

// Complejidad max O(n)
template<class K, class T>
void OpenHash<K,T>::print() {
  std::cout << "Content of the hash table: " << std::endl;
  for (int i = 0; i < maxSize; i++) {
    if (table[i].size() > 0){

      for(auto& celda : table[i]){
        std::cout<< "(" << celda.first << ", " <<celda.second << ")";
      }

    }
  }
}

// Complejidad max O(n)
template<class K, class T>
void OpenHash<K,T>::add(K keyVal, T value) {
  if (numElements == maxSize) {
    throw std::out_of_range("Hash Table is full");
  }
  // Compute the index of the table using a key and a hash function
  int hashVal = getHashIndex(keyVal); 

  //emplace_front permite insertar ambos elementos
  table[hashVal].emplace_front(keyVal , value);
  numElements++;
  }

// Complejidad O(n)
template<class K, class T>
T OpenHash<K,T>::find(K keyVal) {

  int hashVal = getHashIndex(keyVal); 

  std::list<std::pair<K, T>> &lista = table[hashVal]; 

  int ix = 0;

  for(auto celda = lista.begin(); celda != lista.end(); celda++){
    if (celda->first == keyVal) {
      // Se encontro el elemento, salimos del ciclo
      break; // Salir de la funcion
    }
    ix++;
  }

  // if(ix >=0){}

  // std::cout<< "Result index: "<< ix << std::endl;
  return this->getDataAt(ix);

}

// Complejidad max O(n)
template<class K, class T>
void OpenHash<K,T>::remove(K value) {
  
  int hashVal = getHashIndex(value);
  
  std::list<std::pair<K, T>> &lista = table[hashVal]; 

  //Iterador celda
  for(auto celda = lista.begin(); celda != lista.end(); celda++){
    if (celda->first == value) {
      lista.erase(celda);
      numElements--;
      break; // Salir de la funcion
    }
  }
}


#endif // __HASH_TABLE_H_



