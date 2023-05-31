/**
* Ejemplo que implementa la representacion de Grafos (dirigidos ponderados):
* como lista de adyacencia y sus recorridos BFS y DFS.
*
* Compilacion para debug:
*    g++ -std=c++17 -g -o main *.cpp
* Ejecucion con valgrind:
*    nix-env -iA nixpkgs.valgrind
*    valgrind --leak-check=full ./main < TestCases/test01.txt
*
* Compilacion para ejecucion:
     g++ -std=c++17 -Wall -O3 -o main *.cpp
*    g++ -std=c++17 -O3 -o main *.cpp
* Ejecucion:
*    ./main < TestCases/test01.txt
* ------------------------------------
* Equipo 2:
* Iker Casillas  | A01641047
* César Simental | A01641385
* Arturo Sánchez | A01275427
**/

#include "Graph.h"
#include <iostream>
#include <sstream>

int main() {
  std::stringstream inputInfo;
  inputInfo << std::cin.rdbuf();
  // Construye un grafo a partir de la consola usando
  // representacion de Lista de adyacencia
  Graph g1;
  g1.loadDirWeightedGraph(inputInfo);
  g1.print();
  std::cout << std::endl;
  std::cout << std::endl;
  g1.BFS(1);
  g1.DFS(1);

  return 0;
}