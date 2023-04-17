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
 *
 * Equipo 2:
 * Iker Casillas  | A01641047
 * César Simental | A01641385
 * Arturo Sánchez | A01275427 
 * 
 **/

#include "DLinkedList.h"
#include <iostream>

int main() {
  DLinkedList<int> miLista;
  
  for (int i = 1; i < 6; i++) {
    miLista.addFirst(i);
  }
  for (int i = 10; i < 15; i++) {
    miLista.addLast(i);
  }
  miLista.deleteData(12);
  miLista.deleteData(114);
  miLista.deleteAt(2);

  std::cout << "Mostrando lista:\n" <<std::endl;
  std::cout << "numElements: " << miLista.getNumElements() << std::endl;
  miLista.printList();
  std::cout << std::endl;




  // ------ TAREA ------
  std::cout << "\n------- Métodos de tarea 1 -------\n" << std::endl;
  // findData
  std::cout << "findData 11:" << std::endl;
  std::cout << "Elemento encontrado en la posicion ["<<miLista.findData(11) <<"]" << std::endl;

  std::cout << "\n------- Métodos de tarea 2 -------\n" << std::endl;
  // updateAt
  std::cout << "updateAt :" << std::endl;
  std::cout << "Elemento actualizado "<<std::endl;
  miLista.updateAt(1, 5);
  miLista.printList();


  std::cout << "\n------- Métodos de tarea 3 -------\n" << std::endl;
  std::cout << "Invirtiendo lista:" <<std::endl;
  miLista.invert();
  miLista.printList();

  std::cout << "\nSublista invertida, indices 2:6" <<std::endl;
  
  auto sublista = miLista.getReversedSublist(2, 6);
  sublista.printList();

  std::cout << "\n------- Métodos de tarea 4 -------\n" << std::endl;
  std::cout << "Quick sort:" <<std::endl;
  miLista.printList();
  miLista.sort();
  miLista.printList();
  
  return 0;
}