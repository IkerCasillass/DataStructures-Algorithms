#include "Registro.h"
#include "AlgorithmSort.h"
#include <sstream>

// Constructor default
Registro::Registro() {
  mes = "";
  dia = "";
  horas = "0";
  minutos = "0";
  segundos = "0";
  ip = "";
  puerto = "";
  falla = "";
  fechaHora = 0;
}

// Constructor
Registro::Registro(std::string _mes, std::string _dia, std::string _horas,
                   std::string _minutos, std::string _segundos, std::string _ip,
                   std::string _puerto, std::string _falla) {
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

// Setters
void Registro::setMes(std::string _mes) { mes = _mes; }
void Registro::setDia(std::string _dia) { dia = _dia; }
void Registro::setHoras(std::string _horas) { horas = _horas; }
void Registro::setMinutos(std::string _minutos) { minutos = _minutos; }
void Registro::setSegundos(std::string _segundos) { segundos = _segundos; }
void Registro::setIp(std::string _ip) { ip = _ip; }
void Registro::setPuerto(std::string _puerto) { puerto = _puerto; }
void Registro::setFalla(std::string _falla) { falla = _falla; }

// Getters
std::string Registro::getMes() { return mes; }
std::string Registro::getDia() { return dia; }
std::string Registro::getHoras() { return horas; }
std::string Registro::getMinutos() { return minutos; }
std::string Registro::getSegundos() { return segundos; }
std::string Registro::getIp() { return ip; }
std::string Registro::getPuerto() { return puerto; }
std::string Registro::getFalla() { return falla; }
time_t Registro::getFechaHora(){ return fechaHora; }

std::string Registro::getAll() {
  return mes + " " + dia + " " + horas + ":" + minutos + ":" + segundos + " " +
         ip + ":" + puerto + " " + falla;
}

//Otros
int Registro::binarySearch(std::vector<Registro> &vectorSorted, int key, int &compara){
  int low = 0;
  int high = vectorSorted.size() - 1;
  int mid = 0;
  compara = 0;
  while (low <= high) {
    mid = low + (high - low) / 2;
    compara++;
    if (key == vectorSorted[mid].getFechaHora())
      return mid;
    else if (key < vectorSorted[mid].getFechaHora())
      high = mid - 1;
    else
      low = mid + 1;
  }
  return -1;
}

//aaaaaaa

void Registro::cambiarFormato(std::string cadena, std::string &hora, std::string &minuto, std::string &segundo){
  
  //Separando horas/minutos/segundos
  std::stringstream input_stringstream(cadena);   

  getline(input_stringstream, hora, ':');
  getline(input_stringstream, minuto, ':');
  getline(input_stringstream, segundo, ':');

  this->setHoras(hora);
  this->setMinutos(minuto);
  this->setSegundos(segundo);

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