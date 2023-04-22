#include "Bitacora.h"
#include "Registro.h"
#include "AlgorithmSort.h"
#include "AlgorithmSort.cpp"
#include "DLinkedList.h"
#include <sstream>
#include <chrono>


//Constructor default
Bitacora::Bitacora() {
  DLinkedList<Registro> Default;
  texto = Default;
}

// Constructor archivo
Bitacora::Bitacora(std::ifstream &archivo) {

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

  //Leer archivo
  if(archivo.is_open()) {

    // Obtener línea de archivo, y almacenar contenido en "linea"
    while (getline(archivo, linea)) {
      
      std::istringstream ss(linea);
      //Obtenemos los datos que estan separados por espacios
      ss>>mes>>dia>>horas>>ip>>error1>>error2>>error3>>error4>>error5>>error6;

      std::string error;
      //Juntamos las palabras del error en una sola cadena

      error = error1 + " " + error2+ " " + error3+ " " + error4+ " " + error5+ " " + error6;

      
      
      //Registro temporal
      Registro registrotemp(mes, dia, horas, "0", "0", ip, puerto, error);

      // Cambiar formato y setear hora
      registrotemp.cambiarFormato(horas, horas, minutos, segundos);

      
      //Añadiendo los registros al vector
      texto.addLast(registrotemp);

      //Borrar caracteres del string para nueva cadena de error
      error1 = "";
      error2 = "";
      error3 = "";
      error4 = "";
      error5 = "";
      error6 = "";
    }
  }
}

void Bitacora::setTexto(DLinkedList<Registro> _texto){
  texto = _texto;
}

DLinkedList<Registro> Bitacora::getTexto() {
  return texto;
}

//Metodos

void Bitacora::buscar(std::vector<Registro> vectorSorted){
  
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

  //Crear Registro_inicial
  Registro Registro_inicial(mes, dia, horas, "0", "0", "", "", "");
  
  Registro_inicial.cambiarFormato(horas, horas, minutos, segundos);

  
  AlgorithmSort<Registro>sortObj;
  
  // Binary search
  indice_inicial = sortObj.binarySearch(vectorSorted, Registro_inicial.getFechaHora(), compara);

  if(indice_inicial == -1){
    std::cout<<"\nLa fecha inicial no se encuentra en el archivo, ingrese un rango valido" <<std::endl;
    exit(0);
  }
  else{
    std::cout<<"\nFecha inicial encontrada en indice " << indice_inicial <<std::endl;
  }


  //convertir a formato deseado
  std::istringstream ff(fecha_final);
  ff>>mes>>dia>>horas;

  //Crear Registro_final
  Registro Registro_final(mes, dia, horas, "0", "0", "", "", "");
  
  Registro_final.cambiarFormato(horas, horas, minutos, segundos);

   // Busqueda binary search
  indice_final = sortObj.binarySearch(vectorSorted, Registro_final.getFechaHora(), compara);

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

std::vector<Registro> Bitacora::ordenar(const std::vector<Registro> &listaRegistros, int size){
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

void Bitacora::imprimir() {
  
}

