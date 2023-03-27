/** 
* Ejemplo que implementa objetos de la clase Registro
* que contienen una fecha-hora convertida a Linux timestamp
* para realizar comparaciones (sobrecarga de operadores)
*
* Compilacion para debug:  
*    g++ -std=c++17 -g -o main *.cpp 
* Ejecucion con valgrind:
*    nix-env -iA nixpkgs.valgrind
*    valgrind --leak-check=full ./main
*
* Compilacion para ejecucion:  
*    g++ -std=c++17 -O3 -o main *.cpp 
* Ejecucion:
*    ./main



* Equipo 2:
* Iker Casillas  | A01641047
* César Simental | A01641385
**/
#include <iostream>
#include "Registro.h"
#include <fstream> // ayuda en lectura de archivo
#include <sstream> // facilita separar el string
#include "AlgorithmSort.h"
#include<chrono>
//Funciones de archivo principal
 

std::vector<Registro> leerDatos(std::vector<Registro> &listaRegistros){
  //Pasamos vector por referencia para modificarlo
  
  std::string linea;
  std::string mes;
  std::string dia;
  std::string horas;
  std::string minutos;
  std::string segundos;
  std::string ip;
  std::string puerto;
  std::string error1;
  std::string error2;
  std::string error3;
  std::string error4;
  std::string error5;
  std::string error6;
  int i = 0;
  //Registro registrotemp;
  std::ifstream bitacora("bitacora.txt"); //archivo a leer


  //Leer archivo
  if(bitacora.is_open()) {

  
    // Obtener línea de archivo, y almacenar contenido en "linea"
    while (getline(bitacora, linea)) {
      
      // Los agregamos al vector de registros
      std::istringstream ss(linea);
      ss>>mes>>dia>>horas>>ip>>error1>>error2>>error3>>error4>>error5>>error6;

      //Separando horas/minutos/segundos
      std::stringstream input_stringstream(horas);   

      getline(input_stringstream, horas, ':');
      getline(input_stringstream, minutos, ':');
      getline(input_stringstream, segundos, ':');

      
      std::string error;
      error = error1 + " " + error2+ " " + error3+ " " + error4+ " " + error5+ " " + error6;

      //Registro temporal
      Registro registrotemp(mes, dia, horas, minutos, segundos, ip, puerto, error);
      

      
      listaRegistros.push_back(registrotemp);
  }

  }
  return listaRegistros;
}

std::vector<Registro> Ordenar(std::vector<Registro> &listaRegistros, int size){
  unsigned int comparaciones, swaps;
  std::vector<Registro> listaRegistros1, listaRegistros2;
  listaRegistros1 = listaRegistros;
  listaRegistros2 = listaRegistros;

  AlgorithmSort<Registro>sortObj;
  std::cout <<"\nOrdenando lista...\n"<<std::endl;
  std::cout <<"---- Quicksort ----"<<std::endl;
  comparaciones = swaps = 0;
  auto startTime = std::chrono::high_resolution_clock::now(); //Iniciar tiempo
  sortObj.quickSort(listaRegistros1, 0, size-1, comparaciones, swaps); //Ordenar con quicksort
  auto endTime = std::chrono::high_resolution_clock::now(); //Termina tiempo ejecucion
  auto totalTime = endTime - startTime;

  std::cout<<"comparaciones: "<<comparaciones <<std::endl;
  std::cout<<"swaps: "<<swaps <<std::endl;
  std::cout<<"Tiempo de ejecucion en ms: " << totalTime/std::chrono::milliseconds(1)<<std::endl;


  std::cout <<"\n-- InsertionSort -- (aprox 85 +- 8s)"<<std::endl;
  startTime = std::chrono::high_resolution_clock::now(); //Iniciar tiempo
  sortObj.insertionSort(listaRegistros2, size, comparaciones, swaps); //Ordenar por insertion sort
  endTime = std::chrono::high_resolution_clock::now(); //Termina tiempo ejecucion
  totalTime = endTime - startTime;

  std::cout<<"comparaciones: "<<comparaciones <<std::endl;
  std::cout<<"swaps: "<<swaps <<std::endl;
  std::cout<<"Tiempo de ejecucion en ms: " << totalTime/std::chrono::milliseconds(1)<<std::endl;


  return listaRegistros1;
}

int main() {

  unsigned int comparaciones, swaps;
  int size;
  std::vector<Registro> listaRegistros, listaOrdenada;

  listaRegistros = leerDatos(listaRegistros);
  size = listaRegistros.size();

  listaOrdenada = Ordenar(listaRegistros, size);


  
  // Comparacion de dos objetos de la clase registro
  // gracias a la sobrecarga de operadores de comparacion
  
  /*if (listaRegistros[0] < listaRegistros[1]) std::cout << "a es menor que b" << std::endl;
  if (listaRegistros[0] == listaRegistros[2]) std::cout << "a es igual a c" << std::endl;

  
  for (int i = 0; i < (int)listaRegistros.size(); i++) {
    if (key == listaRegistros[i]) {
      std::cout << "found in " << i << std::endl;
      std::cout << listaRegistros[i].getAll() << std::endl;
    }
  }*/
  
  return 0;
  
}
