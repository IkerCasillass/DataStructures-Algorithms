/*
  compilar:
    g++ -std=c++17 -Wall *.cpp

  ejecutar:
    ./a.out
*/

#include "Lista.h"
#include <iostream>

int main() {
  std::cout << "\nTemplate example!\n\n";

  Lista<int> listaInt; // lista de ints

  // agregar valores a la lista
  for (int i = 1; i <= 6; i++)
    if (!listaInt.insert(i * 10))
      std::cout << "no se pudo insertar el elemento en: " << i << std::endl;
  // imprime la lista
  listaInt.print();

  //getData

  std::cout << "\nFuncion get Data (posicion 3): " <<std::endl;
  std::cout << listaInt.getData(3) <<std::endl;

  std::cout << "\nCurrent size: " <<std::endl;
  std::cout <<listaInt.getCurrentSize() <<std::endl;

  std::cout <<"\nMetodo Erase: " <<std::endl;
listaInt.erase();  
  
  return 0;
}
