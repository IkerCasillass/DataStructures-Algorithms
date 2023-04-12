/**
 * Ejemplo que implementa una lista ligada con head y tail
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

#include "LinkedList.h"
#include <iostream>

int main() {
  LinkedList<int> miLista;
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
  
  // ------ TAREA ------
  std::cout << "\n------- Métodos de tarea -------\n" << std::endl;
  // updateData

  std::cout << "updateData 13 to 14:" << std::endl;
  miLista.printList();
  miLista.updateData(13, 14);
  miLista.printList();
  std::cout << std::endl;
  
  
  // updateAt

  std::cout << "updateDataAt 3 to 7:" << std::endl;
  miLista.printList();
  miLista.updateAt(3, 7);
  miLista.printList();
  std::cout << std::endl;

  // findData
  std::cout << "findData 11:" << std::endl;
  std::cout << "Elemento encontrado en la posicion ["<<miLista.findData(11) <<"]" << std::endl;

  // findMiddleElement
  std::cout << "\nfindMiddleElement():" <<std::endl;

  try {
    // Guardar variable de template
    auto elementos = miLista.findMiddleElement();
    std::cout << "Middle Element(s): " << elementos[0];
    if(elementos.size() == 2){
     std::cout << " " << elementos[1] << std::endl << "\n";
    }
  } catch (std::out_of_range &e) {
    std::cout << "Error: " << e.what() << std::endl;
  }

  std::cout<<"Deeply copy: " <<std::endl;
  LinkedList<int> nueva_lista(miLista);
  nueva_lista.printList();
  std::cout << "Lista copiada exitosamente\n"<<std::endl;
  return 0;
}