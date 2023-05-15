#include <iostream>
#include "Registro.h"
class IP {
  private:
    int access_num;
    unsigned int ip_value;
    std::string access_info;

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
int IP::getAccess_num(){
  return access_num;
}
std::string IP::getAccess_info(){
  return access_info;
}
unsigned int IP::getIp_value(){
  return ip_value;
}

// Sobrecarga de operadores
bool IP::operator==(const IP &other) {
  return this->ip_value == other.ip_value;
}

bool IP::operator!=(const IP &other) {
  return this->ip_value != other.ip_value;
}

bool IP::operator>=(const IP &other) {
  return this->ip_value >= other.ip_value;
}

bool IP::operator<=(const IP &other) {
  return this->ip_value <= other.ip_value;
}

bool IP::operator>(const IP &other) {
  return this->ip_value > other.ip_value;
}

bool IP::operator<(const IP &other) {
  return this->ip_value < other.ip_value;
}
