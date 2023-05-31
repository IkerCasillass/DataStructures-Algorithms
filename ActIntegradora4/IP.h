#ifndef _IP_H_
#define _IP_H_

#include <iostream>
#include "Registro.h"

// Clase para almacenar la información de las ip
class IP {//Declaracion de la clase IP
  private:
    int access_num;//Declara la variable access_num de tipo int
    unsigned int ip_value;//Declara la variable ip_value de tipo unsigned int
    std::string access_info;//Declara la variable access_info de tipo std::string

  public:
  IP();
  IP(std::string, int, unsigned int);
  ~IP();

  int getAccess_num();
  unsigned int getIp_value();
  std::string getAccess_info();

  // Sobre carga de operadores
  bool operator ==(const IP&);
  bool operator !=(const IP&);
  bool operator >(const IP&);
  bool operator <(const IP&);
  bool operator >=(const IP&);
  bool operator <=(const IP&);
  
};

// Constructores
IP::IP(){
  access_num = 0;
}

IP::IP(std:: string _access_info, int _access_num, unsigned int _ip_value){
  access_info = _access_info;
  access_num = _access_num;
  ip_value = _ip_value;
}

//Destructor
IP::~IP(){}


// Getters
int IP::getAccess_num(){//define un método llamado getAccess_num() en la clase IP que devuelve un valor entero
  return access_num;
}
std::string IP::getAccess_info(){//define un método llamado getAccess_info() que devuelve un valor de tipo std::string
  return access_info;
}
unsigned int IP::getIp_value(){//define un método llamado getIp_value() que devuelve un valor entero sin signo
  return ip_value;
}

// Sobrecarga de operadores
bool IP::operator==(const IP &other) {//define la sobrecarga del operador de igualdad (==) para la clase IP
  return this->access_num == other.access_num;
}

bool IP::operator!=(const IP &other) {//define la sobrecarga del operador de desigualdad (!=) para la clase IP
  return this->access_num != other.access_num;
}

bool IP::operator>=(const IP &other) {//define la sobrecarga del operador mayor o igual (>=) para la clase IP
  return this->access_num >= other.access_num;
}

bool IP::operator<=(const IP &other) {//define la sobrecarga del operador menor o igual (<=) para la clase IP
  return this->access_num <= other.access_num;
}

bool IP::operator>(const IP &other) {//define la sobrecarga del operador mayor que (>) para la clase IP
  return this->access_num > other.access_num;
}

bool IP::operator<(const IP &other) {//define la sobrecarga del operador menor que (<) para la clase IP
  return this->access_num < other.access_num;
}

#endif //IP.h