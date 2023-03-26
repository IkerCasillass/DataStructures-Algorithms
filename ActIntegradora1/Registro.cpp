
#include "Registro.h"

//Constructor default
Registro::Registro() {
  mes = "";
  dia = "";
  horas = ""; 
  minutos = ""; 
  segundos = ""; 
  ip = ""; 
  puerto = ""; 
  falla = "";
  fechaHora = 0;
}

//Constructor 
Registro::Registro(std::string _mes, std::string _dia, std::string _horas, std::string _minutos, std::string _segundos, std::string _ip, std::string _puerto, std::string _falla) {
  mes = _mes;
  dia = _dia;
  horas = _horas; 
  minutos = _minutos; 
  segundos = _segundos; 
  ip = _ip; 
  puerto = _puerto; 
  falla = _falla;
  // Almacenar los campos en el struct tm
  dateStruct.tm_hour = std::stoi(horas);
  dateStruct.tm_min = std::stoi(minutos);
  dateStruct.tm_sec = std::stoi(segundos);
  dateStruct.tm_mday = std::stoi(dia);
  // Resolver problemas de compatibilidad Windows
  dateStruct.tm_isdst = 0;
  for (int i = 0; i < (int)meses.size(); i++) {
    if (meses[i] == mes) 
      dateStruct.tm_mon = i;
  }
  dateStruct.tm_year = 2023 - 1900; // Asumimos el año 2023
  // Obtener el Linux timestamp
  // https://cplusplus.com/reference/ctime/mktime/
  fechaHora = mktime(&dateStruct);
}

//setters - getters
void Registro::setIp(std::string _ip) {
  ip = _ip;
}

std::string Registro::getIp(){
  return ip;
}

std::string Registro::getAll() {
  return mes + " " + dia + " " + horas + ":" + minutos + ":" + segundos + " " + ip + ":" + puerto + " " + falla;
}

// Sobrecarga de operadores de comparacion
// Comparacion de objetos de la clase Registro usando el Linux timestamp
bool Registro::operator==(const Registro &other) {
  return this->fechaHora == other.fechaHora;
}

bool Registro::operator!=(const Registro &other) {
  return this->fechaHora != other.fechaHora;
}

bool Registro::operator>=(const Registro &other) {
  return this->fechaHora >= other.fechaHora;
}

bool Registro::operator<=(const Registro &other) {
  return this->fechaHora <= other.fechaHora;
}

bool Registro::operator>(const Registro &other) {
  return this->fechaHora > other.fechaHora;
}

bool Registro::operator<(const Registro &other) {
  return this->fechaHora < other.fechaHora;
}