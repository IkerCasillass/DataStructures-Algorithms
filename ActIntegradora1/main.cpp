/** 
* Ejemplo que implementa objetos de la clase Registro
* que contienen una fecha-hora convertida a Linux timestamp
* para realizar comparaciones (sobrecarga de operadores)
*
* Compilacion para debug:  
*    g++ -std=c++17 -g -o main *.cpp 
* Ejecucion con valgrind:
*    nix-env -iA nixpkgs.valgrind
*    valgrind --leak-check=full ./main
*
* Compilacion para ejecucion:  
*    g++ -std=c++17 -O3 -o main *.cpp 
* Ejecucion:
*    ./main
**/
#include <iostream>
#include "Registro.h"

int main() {
  // Crear objetos de la clase Registro (un renglon de la bitacora)
  Registro a("Jan", "01", "00", "01", "02", "1.1.1.1", "123", "Falla 1");
  Registro b("Feb", "04", "00", "01", "02", "1.1.1.3", "1234", "Falla 2");
  Registro c("Dec", "01", "00", "01", "02", "1.1.1.1", "123", "Falla 1");

  Registro key("Jan", "01", "00", "01", "02", "", "", "");
  std::cout << "Key " << std::endl;
  std::cout << key.getAll() << std::endl;

  
  std::vector<Registro> listaRegistros;
  listaRegistros.push_back(a);
  listaRegistros.push_back(b);
  listaRegistros.push_back(c);
  
  // Comparacion de dos objetos de la clase registro
  // gracias a la sobrecarga de operadores de comparacion
  if (listaRegistros[0] < listaRegistros[1]) std::cout << "a es menor que b" << std::endl;
  if (listaRegistros[0] == listaRegistros[2]) std::cout << "a es igual a c" << std::endl;

  
  for (int i = 0; i < (int)listaRegistros.size(); i++) {
    if (key == listaRegistros[i]) {
      std::cout << "found in " << i << std::endl;
      std::cout << listaRegistros[i].getAll() << std::endl;
    }
  }
  
  return 0;
  
}
