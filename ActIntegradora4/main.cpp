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
#include "MaxHeap.h"
#include "Incidencia.h"
#include "Graph.h"

int main() { 
  // std::stringstream inputInfo;
  // inputInfo << std::cin.rdbuf(); 
  // Construye un grafo a partir de la consola usando
  // representacion de Lista de adyacencia
  std::ifstream bitacora("bitacoraGrafos.txt"); // archivo a leer
  
  Graph g1(bitacora);

  // Incidencia prueba;

  // prueba.setIpValue("36.29.138.97", 0);

  // std::cout << prueba.getIpOrigenValue();

  return 0; 
}