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
  int maxCapacity = 13371, nodoBoot;
  MaxHeap<Incidencia> HeapIps(maxCapacity); // Heap con informacion de ip
  std::vector<Incidencia> nodosOrigen; // Informacion de nodos
  std::ifstream bitacora("bitacoraGrafos.txt"); // archivo a leer
  Incidencia bootMaster; // Variable para almacenar bootmaster
  

  //Construir grafo
  Graph g1(bitacora, nodosOrigen);
  std::cout << "> Grafo construido" << std::endl;

  // ----- archivo con grados de salida -----
  std::ofstream outputFile("grados_ips.txt");
  if(outputFile.is_open()){
    for(int i = 0; i < g1.getNumNodes(); i++){
      outputFile <<"(" << nodosOrigen[i].getIpOrigen() << "," << nodosOrigen[i].getNumVecinos() << ")" << std::endl;

      // Construir Heap
      HeapIps.push(nodosOrigen[i]);
    }
    outputFile.close();
    std::cout<< "> Archivo con grados de salida construido" <<std::endl;
  }
  else{
    std::cout << "Error con el archivo." << std::endl;
  }

  
  // ---- Archivo de 5 IP con mayor grado de salida ----
  //Complejidad de HeapSort O(n log n)
  std::ofstream outputFile2("mayores_grados_ips.txt");
  if(outputFile2.is_open()){
    outputFile2 << "5 IP con mas grado de salida:" << std::endl;
    for(int i=0; i<5; i++){
      if(i == 0)
        bootMaster = HeapIps.getTop(); // Guardar bootmaster
      
      outputFile2 << HeapIps.getTop().getIpOrigen() << " {" << HeapIps.getTop().getNumVecinos() << "}" << std::endl;
      
      HeapIps.pop();
    }

    std::cout<< "> Archivo con Top 5 IP construido" <<std::endl;
  }

  nodoBoot = g1.getNodeOrder(bootMaster.getIpOrigen());
  
  // Imprimir boot master
  std::cout << "\nIMPRIMIENDO BOOTMASTER:\n" << std::endl;
  std::cout << "Numero de nodo: " << nodoBoot << std::endl;
  std::cout << "Direccion IP: " << bootMaster.getIpOrigen() << std::endl;

  std::cout<<"\nConstruyendo archivo con distancias, puede tardar unos segundos..."<< std::endl;
  g1.dijkstraAlgorithm(nodoBoot);
  std::cout<< "> Archivo de distancias construido" <<std::endl;
  
  return 0; 
}