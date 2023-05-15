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
  int maxCapacity = 16810;
  MaxHeap<IP> HeapIps(maxCapacity); // Heap con informacion de ip
  std::vector<Registro> sortedIP;

  
  std::ifstream bitacora("bitacoraHeap.txt"); //archivo a leer
    if(bitacora){
      MaxHeap<Registro> Inicial(bitacora, maxCapacity); // Creamos MaxHeap<Registro>
      
      
      // Guardar los elementos ordenados en un vector usando heapsort
      for(int i = 0; Inicial.getCurrentSize(); i++){ 
        sortedIP.push_back(Inicial.getTop());
        // Eliminamos del Heap                                            
        Inicial.pop();
      }

      // Ciclo recorre elementos del vector y almacena datos en Heap<IP>
      int cont = 1;
      int j = 1;
      
      while(j < (int)sortedIP.size()){
        if (sortedIP[j] == sortedIP[j-1]) {
          cont++;
        }
        else {
          //--------Insertar en Heap<IP> ---------
          
          // Crear Ip temporal con direccion y # acceso - valor ip
          IP IPtemp(sortedIP[j].getIp(), cont, sortedIP[j].getIp_value());
          // Insertar
          HeapIps.push(IPtemp);
          // Resetear contador
          cont = 1;
        }
        j++;
      }


      std::cout<< "Numero de IPS: " << HeapIps.getCurrentSize() << std::endl;
      for(int i = 0; i < 50; i++){
        std::cout<< HeapIps.getData()[i].getIp_value() << ":" << HeapIps.getData()[i].getAccess_num() << std::endl;
      }

    }
    else {
      std::cout<< "Error al leer el archivo" <<std::endl;
    }    


  
  return 0; 
}