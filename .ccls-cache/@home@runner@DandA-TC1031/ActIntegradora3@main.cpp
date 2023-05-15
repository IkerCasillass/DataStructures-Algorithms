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
#include "MaxHeap.h"
#include "IP.h"


int main() { 
  std::string hora, minuto, segundo, ip, puerto;
  int maxCapacity = 17000;
  MaxHeap<IP> HeapIps(maxCapacity); // Heap con informacion de ip
  
  std::ifstream bitacora("bitacoraHeap.txt"); //archivo a leer
    if(bitacora){
      MaxHeap<Registro> Inicial(bitacora, maxCapacity);
      std::cout<< Inicial.getCurrentSize() <<std::endl;
      std::vector<Registro> sortedIP;
      for(int i = 0; Inicial.getCurrentSize(); i++){
        sortedIP.push_back(Inicial.getTop());
        Inicial.pop();
      }

      
      std::cout << "Valor de la ip en los registros ordenados:\n" << std::endl;
      for(int i = 0; i < 50; i++){
        std::cout<< sortedIP[i].getIp_value() << std::endl;
      }

      

      
      
    }
    else {
      std::cout<< "Error al leer el archivo" <<std::endl;
    }    


  
  return 0; 
}