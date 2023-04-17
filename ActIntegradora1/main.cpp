/** 
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
*
* ------------------------------------
* Equipo 2:
* Iker Casillas  | A01641047
* César Simental | A01641385
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



//Funciones de archivo principal
void cambiarFormato(std::string cadena, std::string &hora, std::string &minuto, std::string &segundo){
  //Separando horas/minutos/segundos
  std::stringstream input_stringstream(cadena);   

  getline(input_stringstream, hora, ':');
  getline(input_stringstream, minuto, ':');
  getline(input_stringstream, segundo, ':');
}

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
      
      std::istringstream ss(linea);
      //Obtenemos los datos que estan separados por espacios
      ss>>mes>>dia>>horas>>ip>>error1>>error2>>error3>>error4>>error5>>error6;

      cambiarFormato(horas, horas, minutos, segundos);

      std::string error;
      //Juntamos las palabras del error en una sola cadena
      error = error1 + " " + error2+ " " + error3+ " " + error4+ " " + error5+ " " + error6;

      //Registro temporal
      Registro registrotemp(mes, dia, horas, minutos, segundos, ip, puerto, error);

      //Añadiendo los registros al vector
      listaRegistros.push_back(registrotemp);

      //Borrar caracteres del string para nueva cadena de error
      error1 = "";
      error2 = "";
      error3 = "";
      error4 = "";
      error5 = "";
      error6 = "";
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


  std::cout <<"\n-- InsertionSort -- (aprox 85 +- 10s)"<<std::endl;
  startTime = std::chrono::high_resolution_clock::now(); //Iniciar tiempo
  sortObj.insertionSort(listaRegistros2, size, comparaciones, swaps); //Ordenar por insertion sort
  endTime = std::chrono::high_resolution_clock::now(); //Termina tiempo ejecucion
  totalTime = endTime - startTime;

  std::cout<<"comparaciones: "<<comparaciones <<std::endl;
  std::cout<<"swaps: "<<swaps <<std::endl;
  std::cout<<"Tiempo de ejecucion en ms: " << totalTime/std::chrono::milliseconds(1)<<std::endl;

  return listaRegistros1;
}

void buscar(std::vector<Registro> vectorSorted){
  std::string fecha_inicial, fecha_final, mes, dia, horas, minutos, segundos;
  int compara = 0, indice_inicial = 0, indice_final = 0, rango = 0;
  
  std::cout<<"\n----------------------------------"<<std::endl;
  std::cout<<"--------Busqueda por fecha--------\n"<<std::endl;
  std::cout<<"Ingresa la fecha incial (Mes dd hh:mm:ss): "<<std::endl;
  std::getline(std::cin, fecha_inicial);
  std::cout<<"Ingresa la fecha final (Mes dd hh:mm:ss): "<<std::endl;
  std::getline(std::cin, fecha_final);

  //convertir a formato deseado
  std::istringstream fi(fecha_inicial);
  fi>>mes>>dia>>horas;

  cambiarFormato(horas, horas, minutos, segundos);

  
  //Crear Registro_inicial
  Registro Registro_inicial(mes, dia, horas, minutos, segundos, "", "", "");

  //búsqueda binarysearch
  indice_inicial = Registro_inicial.binarySearch(vectorSorted, Registro_inicial.getFechaHora(), compara);

  if(indice_inicial == -1){
    std::cout<<"\nLa fecha inicial no se encuentra en el archivo, ingrese un rango valido" <<std::endl;
    exit(0);
  }
  else{
    std::cout<<"\nFecha inicial encontrada en indice " << indice_inicial <<std::endl;
  }


  //convertir fecha final a formato deseado
  std::istringstream ff(fecha_final);
  ff>>mes>>dia>>horas;
  cambiarFormato(horas, horas, minutos, segundos);

  //Crear Registro_final
  Registro Registro_final(mes, dia, horas, minutos, segundos, "", "", "");
  
  //búsqueda binarysearch
  indice_final = Registro_final.binarySearch(vectorSorted, Registro_final.getFechaHora(), compara);
  if(indice_final == -1) {
    std::cout<<"La fecha final no se encuentra en el archivo, ingrese un rango valido" <<std::endl;
    exit(0);
  }
  else{
    std::cout<<"Fecha final encontrada en indice " << indice_final <<std::endl;
  }

  //Mostrar datos
  rango = indice_final - indice_inicial;
  std::cout<<"\nMostrando " << rango+1 << " Registros:\n" << std::endl;
  for(int i=indice_inicial; i<indice_final+1; i++){
    std::cout<<vectorSorted[i].getAll()<<std::endl;
  }
}

int main() {

    int size = 0;
    std::ifstream bitacora("bitacora.txt"); //archivo a leer
    std::vector<Registro> listaOrdenada;
  
    Bitacora bitacora1(bitacora);
    std::cout << "Bitacora creada\n" <<std::endl;
    std::cout << bitacora1.getTexto()[0].getAll() <<std::endl;

    size = bitacora1.getTexto().size();
    listaOrdenada = bitacora1.ordenar(bitacora1.getTexto(), size);

    bitacora1.buscar(listaOrdenada);
    std::cout<<"\n";

    // std::cout<<"10 primeros registros: " <<std::endl;
    // for(int i=0; i < 10; i++){
    //   std::cout<< listaOrdenada[i].getAll() <<std::endl;
    // }
    
  
    
 /* unsigned int comparaciones, swaps;
  int size;
  std::vector<Registro> listaRegistros, listaOrdenada;

  listaRegistros = leerDatos(listaRegistros);
  size = listaRegistros.size();

  listaOrdenada = Ordenar(listaRegistros, size);

  //lista ordenada a archivo
  std::fstream file;
  
    file.open("bitacora_ordenada.txt",std::ios_base::out);
 
    for(int i=0;i<listaOrdenada.size();i++)
    {
        std::string actual = listaOrdenada[i].getAll();
        file<<actual<<std::endl; 
    }
    file.close();
  
  buscar(listaOrdenada);
  */
  
  return 0;
  
}
