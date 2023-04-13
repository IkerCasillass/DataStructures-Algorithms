/**
 * Ejemplo que implementa una lista doblemente ligada con head y tail
 *
 * Compilacion para debug:
 *    g++ -std=c++17 -Wall -g -o main *.cpp
 * Ejecucion con valgrind:
 *    nix-env -iA nixpkgs.valgrind
 *    valgrind --leak-check=full ./main
 *
 * Compilacion para ejecucion:
 *    g++ -std=c++17 -Wall -O3 -o main *.cpp
 * Ejecucion:
 *    ./main
 **/

#include "DLinkedList.h"
#include <iostream>

int main() {
  DLinkedList<int> miLista;
  std::cout << "numElements: " << miLista.getNumElements() << std::endl;
  // addFirst
  std::cout << "Agregando 5 elementos al frente..." << std::endl;
  for (int i = 1; i < 6; i++) {
    miLista.addFirst(i);
  }
  std::cout << "numElements: " << miLista.getNumElements() << std::endl;
  std::cout << "printList: " << std::endl;
  miLista.printList();
  std::cout << std::endl;
  std::cout << "printListReversed: " << std::endl;
  miLista.printListReversed();
  std::cout << std::endl;

  // addLast
  std::cout << "Agregando 5 elementos al final..." << std::endl;
  for (int i = 10; i < 15; i++) {
    miLista.addLast(i);
  }
  std::cout << "numElements: " << miLista.getNumElements() << std::endl;
  std::cout << "printList: " << std::endl;
  miLista.printList();
  std::cout << std::endl;

  // deleteData
  std::cout << "Delete 12: " << std::endl;
  miLista.deleteData(12);
  std::cout << "numElements: " << miLista.getNumElements() << std::endl;
  miLista.printList();
  std::cout << "Delete 5: " << std::endl;
  miLista.deleteData(5);
  std::cout << "numElements: " << miLista.getNumElements() << std::endl;
  miLista.printList();
  std::cout << "Delete 14: " << std::endl;
  miLista.deleteData(14);
  std::cout << "numElements: " << miLista.getNumElements() << std::endl;
  std::cout << "printList: " << std::endl;
  miLista.printList();
  std::cout << "Delete 114: " << std::endl;
  miLista.deleteData(114);
  std::cout << "numElements: " << miLista.getNumElements() << std::endl;
  std::cout << "printList: " << std::endl;
  miLista.printList();
  std::cout << std::endl;

  // DeleteAt puede lanzar una excepcion
  std::cout << "DeleteAt 2: " << std::endl;
  try {
    miLista.deleteAt(2);
  } catch (std::out_of_range &e) {
    std::cout << "Error: " << e.what() << std::endl
              << "No se modifico la lista" << std::endl;
  } catch (...) {
    std::cout << "Error desconocido, no se modifico la lista" << std::endl;
  }
  std::cout << "numElements: " << miLista.getNumElements() << std::endl;
  miLista.printList();
  std::cout << "DeleteAt 19: " << std::endl;
  try {
    miLista.deleteAt(19);
  } catch (std::out_of_range &e) {
    std::cout << "Error: " << e.what() << std::endl
              << "No se modifico la lista" << std::endl;
  } catch (...) {
    std::cout << "Error desconocido, no se modifico la lista" << std::endl;
  }
  std::cout << "numElements: " << miLista.getNumElements() << std::endl;
  miLista.printList();
  std::cout << std::endl;
/*
  // getData
  try {
    std::cout << "getData(3): " << miLista.getData(3) << std::endl;
  } catch (std::out_of_range &e) {
    std::cout << "Error: " << e.what() << std::endl
              << "No se modifico la lista" << std::endl;
  } catch (...) {
    std::cout << "Error desconocido, no se modifico la lista" << std::endl;
  }
  try {
    std::cout << "getData(13): " << miLista.getData(13) << std::endl;
  } catch (std::out_of_range &e) {
    std::cout << "Error: " << e.what() << std::endl
              << "No se modifico la lista" << std::endl;
  } catch (...) {
    std::cout << "Error desconocido, no se modifico la lista" << std::endl;
  }
 */ 
  return 0;
}