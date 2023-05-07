/** 
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

#include <iostream>
#include <chrono>
#include <fstream> // ayuda en lectura y escritura de archivo
#include <sstream> // facilita separar el string
#include <stdlib.h> //exit
#include "Registro.h"
#include "DLinkedList.h"

int main() {
  
  std::ifstream bitacora("bitacora.txt"); //archivo a leer
    if(bitacora){
  
      DLinkedList<Registro> Texto(bitacora); //Linked list que almacena los registros del archivo de texto
      DLinkedList<Registro> CopiaTexto(Texto);
      std::cout << "\nBitacora creada\n" <<std::endl;
      
      Texto.sort(CopiaTexto); // Aplicando quicksort

      Texto.search();
      std::cout<<"\n";
      
    }
    else {
      std::cout<< "Error al leer el archivo" <<std::endl;
    }    

  return 0;

}
