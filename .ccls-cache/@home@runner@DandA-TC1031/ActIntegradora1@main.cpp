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

//Funciones de archivo principal
std::vector<Registro> 

leerDatos(std::vector<Registro> &listaRegistros){
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
  Registro registrotemp;
  std::ifstream bitacora("bitacora.txt"); //archivo a leer


  //Leer archivo
  if(bitacora.is_open()) {

  
    // Obtener línea de archivo, y almacenar contenido en "linea"
    while (getline(bitacora, linea)) {
      
      // Los agregamos al vector de registros
      std::istringstream ss(linea);
      ss>>mes>>dia>>horas>>ip>>error1>>error2>>error3>>error4>>error5>>error6;
          
      std::string error;
      error = error1 + " " + error2+ " " + error3+ " " + error4+ " " + error5+ " " + error6;

      //Guardando datos en vector de Registros
      registrotemp.setMes(mes);
      registrotemp.setDia(dia);
      registrotemp.setHoras(horas);
      registrotemp.setMinutos(minutos);
      registrotemp.setSegundos(segundos);
      registrotemp.setHoras(horas);
      registrotemp.setIp(ip);
      registrotemp.setPuerto(puerto);
      registrotemp.setFalla(error);
      listaRegistros.push_back(registrotemp);
      i++;
  }
    
  

  }
  return listaRegistros;
}


int main() {
  // Crear objetos de la clase Registro (un renglon de la bitacora)
  Registro a("Jan", "01", "00", "01", "02", "1.1.1.1", "123", "Falla 1");
  Registro b("Feb", "04", "00", "01", "02", "1.1.1.3", "1234", "Falla 2");
  Registro c("Dec", "01", "00", "01", "02", "1.1.1.1", "123", "Falla 1");

  Registro key("Jan", "01", "00", "01", "02", "", "", "");
  std::cout << "Key " << std::endl;
  std::cout << key.getAll() << std::endl;
  int size;
  std::vector<Registro> listaRegistros;

  listaRegistros = leerDatos(listaRegistros);
  size = listaRegistros.size();
  std::cout<<size<<std::endl;
  
  for(int i = 0; i<3; i++) {
    std::cout <<listaRegistros[i].getAll() << std::endl;
  }
  

  leerDatos.mergeSort():
  /*listaRegistros.push_back(a);
  listaRegistros.push_back(b);
  listaRegistros.push_back(c);*/



  
  

  
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
