#include "OpenHash.h"
#include <iostream>

/** 
*  HASHING ABIERTO
*
* Compilacion para debug:  
*    g++ -std=c++17 -g -o main *.cpp 
* Ejecucion con valgrind:
*    nix-env -iA nixpkgs.valgrind
*    valgrind --leak-check=full ./main
*
* Compilacion para ejecucion:  
*  g++ -std=c++17 -Wall -O3 -o main *.cpp
*    
* Ejecucion:
*    ./main

*
* ------------------------------------
* Equipo 2:
* Iker Casillas  | A01641047
* César Simental | A01641385
* Arturo Sánchez | A01275427
* */

// Nota: Utilizamos las estructura de datos <<list>> y <<pair>> del STL de c++,
// Por lo que no se necesita clase HashNode.h ni LinkedList.h


int main(){

  std::cout << "Hash Table Example!\n";
  OpenHash<int, std::string> myHashTable(7);

  std::cout << "Table current size: " << myHashTable.getNumElements() << std::endl;

   try {
    std::cout << "Add (50, Hello)" << std::endl;
    myHashTable.add(50, "Hello");
    std::cout << "Add (700, World)" << std::endl;
    myHashTable.add(700, "World");
    std::cout << "Add (85, Collision element 1)" << std::endl;
    myHashTable.add(85, "Collision element 1");
    std::cout << "Add (86, Collision element 2)" << std::endl;
    myHashTable.add(86, "Collision element 2");
  }
  catch (std::out_of_range &e) {
    std::cout << "Error: " << e.what() << std::endl << "No se modifico la Tabla Hash" << std::endl;
  }
  catch (...) {
    std::cout << "Error desconocido, no se modifico la Tabla Hash" << std::endl;
  }
  std::cout << "Table current size: " << myHashTable.getNumElements() << std::endl;
  myHashTable.print();
  std::cout << std::endl;
  
  std::cout << "Find 51: " << std::endl;
  std::cout<< myHashTable.find(51) << std::endl;

  std::cout << "Find 50: " << std::endl;
  std::cout<< myHashTable.find(50) << std::endl;
  
  std::cout << "Find 86: " << std::endl;
  std::cout<< myHashTable.find(86) << std::endl;
  
  std::cout << "Remove 85: " << std::endl;
  myHashTable.remove(85);
  std::cout << "Table current size: " << myHashTable.getNumElements() << std::endl;
  myHashTable.print();
  std::cout << std::endl;

  return 0;
}
