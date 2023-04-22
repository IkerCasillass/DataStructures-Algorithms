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
#include "AlgorithmSort.h" // Header file con declaracion de algoritmos utilizados
#include "AlgorithmSort.cpp" // Incluir cpp arregla linking error
#include "Bitacora.h"
#include "DLinkedList.h"

int main() {
  
    DLinkedList<Registro> text; // Linked List que almacena registros
  
    Registro Registro1("Sep", "29", "00:22::36", "0", "0", "960.96.3.29", "5268", "Error");
    Registro Registro2("Sep", "28", "00:22::36", "0", "0", "960.96.3.29", "5268", "Error");

    std::cout << text.getHead() << "\n" << std::endl;

    text.addFirst(Registro1);
    text.addFirst(Registro2);

    std::cout << "Registros agregados en:" << std::endl;

    std::cout << text.getHead() << std::endl;
    std::cout << text.getTail() << std::endl;

    Bitacora Registros; // Bitacora de Registros

    std::cout << "\nBitacora creada\n" << std::endl;

    Registros.setTexto(text);

    

  return 0;

}
