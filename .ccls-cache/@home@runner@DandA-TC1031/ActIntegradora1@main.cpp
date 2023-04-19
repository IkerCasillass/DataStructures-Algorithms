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
#include "AlgorithmSort.h"
#include "AlgorithmSort.cpp" // Incluir cpp arregla linking error
#include "Bitacora.h"

int main() {
    int size = 0;
  
    std::ifstream bitacora("bitacora.txt"); //archivo a leer

    if(bitacora){
       std::vector<Registro> listaOrdenada;
  
      Bitacora Bitacora1(bitacora);
      std::cout << "Bitacora creada\n" <<std::endl;
  
      size = Bitacora1.getTexto().size();
      listaOrdenada = Bitacora1.ordenar(Bitacora1.getTexto(), size);
  
      Bitacora1.buscar(listaOrdenada);
      std::cout<<"\n";
  
      // Lista ordenada a archivo
      std::fstream file; //Crear archivo para escribir

      if(file){
        file.open("bitacora_ordenada.txt",std::ios_base::out);
     
        for(int i=0;i<(int)listaOrdenada.size();i++)
        {
            std::string actual = listaOrdenada[i].getAll();
            file<<actual<<std::endl; 
        }
        file.close();
      }
      
    }
    else {
      std::cout<< "Error al leer el archivo" <<std::endl;
    }
  
   
  

    
  
  return 0;
  
}
