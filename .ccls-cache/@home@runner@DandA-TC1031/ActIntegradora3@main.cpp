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


int main() { 
  std::string hora, minuto, segundo, ip, puerto;
  int maxCapacity = 17000;
  //Registro Reg1("Oct", "09", "10:32:24", "0", "0", "17.11.195.231:6631", "", "Failed password for illegal user guest");

  //Reg1.setIp_value(1032123123);
  //Reg1.cambiarFormato(Reg1.getHoras(), hora, minuto, segundo, Reg1.getIp(), ip, puerto);


  std::ifstream bitacora("bitacoraHeap.txt"); //archivo a leer
    if(bitacora){
      MaxHeap<Registro> Inicial(bitacora, maxCapacity);

      for(int i = 0; i < 10; i++){
        std::cout<< Inicial.getData()[i].getAll() << std::endl;
      }
    }
    else {
      std::cout<< "Error al leer el archivo" <<std::endl;
    }    


  
  return 0; 
}