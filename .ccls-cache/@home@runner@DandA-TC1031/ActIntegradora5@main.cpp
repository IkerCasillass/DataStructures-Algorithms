
/*
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

#include <iostream>
#include <chrono>
#include <fstream> // ayuda en lectura y escritura de archivo
#include <sstream> // facilita separar el string
// #include <stdlib.h> //exit
#include "Incidencia.h"
#include "Graph.h"
#include "HashTable.h"
#include "LinkedList.h"
#include <tuple>
#include <typeinfo>


int main(){
  
  std::vector<Incidencia> nodosOrigen; // Informacion de nodos
  std::ifstream bitacora("bitacoraGrafos.txt"); // archivo a leer
  Incidencia bootMaster; // Variable para almacenar bootmaster
  unsigned int colisiones = 0;
  std::string ipUsuario;
  
  std::map<int, std::string> nodosOrdenados;

  HashTable<int, Incidencia> myHashTable;
  myHashTable.setMaxSize(22483);
  
  //Construir grafo -> lista de adyacencia
  Graph g1(bitacora, nodosOrigen);
  std::cout << "> Grafo construido" << std::endl;

  for(int i=0; i<(int)nodosOrigen.size(); i++){
    myHashTable.add(nodosOrigen[i].getIpOrigenValue(), nodosOrigen[i], colisiones);
  }
  
  std::cout<< "> HashTable creada" << std::endl;

  std::cout<< "Total de colisiones durante la insercion: " << colisiones << std::endl;

  std::cout<< "Ingresa la IP que deseas buscar, ejemplo (1.14.27.28): ";
  std::cin >> ipUsuario;

  myHashTable.getIpSummary(ipUsuario, g1);

  return 0;
}