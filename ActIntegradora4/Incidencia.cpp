#include "Incidencia.h"
#include <math.h>
#include <sstream>

// Constructor default
Incidencia::Incidencia(){
  mes = "";
  dia = "";
  horas = "0";
  ip_origen = "";
  ip_origen_value = 0;
  puerto_origen = "";
  ip_destino = "";
  puerto_destino =  "";
  peso_inicial = "";
  peso = 0;
  razon = "";
}

// Constructor
Incidencia::Incidencia(std::string _mes, std::string _dia, std::string _horas, std::string _ip_origen, std::string _ip_destino, std::string _peso, std::string _razon){

  mes = _mes;
  dia = _dia;
  horas = _horas;
  ip_origen = _ip_origen;
  // puerto_origen = _puerto_origen;
  ip_destino = _ip_destino;
  // puerto_destino = _puerto_destino;
  peso_inicial = _peso;
  razon = _razon;
}

Incidencia::~Incidencia(){
  
}

// Setters
void Incidencia::setDia(std::string _dia) { dia = _dia; }
void Incidencia::setHoras(std::string _horas) { horas = _horas; }
void Incidencia::setIpOrigen(std::string _ip_origen) { ip_origen = _ip_origen; }
void Incidencia::setIpOrigenValue(unsigned int _ip_origen_value) { ip_origen_value = _ip_origen_value; }
void Incidencia::setIpDestino(std::string _ip_destino) { ip_destino = _ip_destino; }
void Incidencia::setPuertoOrigen(std::string _puerto_origen) { puerto_origen = _puerto_origen; }
void Incidencia::setPuertoDestino(std::string _puerto_destino) { puerto_destino = _puerto_destino; }
void Incidencia::setMes(std::string _mes) { mes = _mes; }

//getters
unsigned int Incidencia::getIpOrigenValue(){ return ip_origen_value; }
std::string Incidencia::getIpOrigen(){ return ip_origen; }
std::string Incidencia::getIpDestino(){ return ip_destino; }
std::string Incidencia::getPuertoOrigen(){return puerto_origen; }
std::string Incidencia::getPuertoDestino() {return puerto_destino; }


// Setter con calculo de valor total de Ip
void Incidencia::setIpValue(std::string _ip_value, int n) { 
  ip_origen = _ip_value;
  
  std::string octeto;

  std::stringstream octetos(_ip_value);
  int cont = 3;
  unsigned int totalValue = 0;

  for(int i=0; i <4; i++) {
    // Separar octetos de direccion ip por delimitador "."
    getline(octetos, octeto, '.');
    
    // Convertir a int 
    int num = stoi(octeto);


    // Elevar valor del octeto a potencia correspondiente
    num *= pow(256, cont);
    // Agregar a suma total
    totalValue += num;
    cont--;
  }

  if(n == 0){
    ///////

    this->setIpOrigenValue(totalValue);
    //ip_origen_value = totalValue;
  }
  else{
    ip_destino_value = totalValue;
  }
    
}

// Separa  ip-puerto
void Incidencia::cambiarFormato(std::string ip_puerto_origen, std::string ip_puerto_destino){


  std::string ip_og, puerto_og, ip_dst,  puerto_dst;
  
  // Separando puerto de ip
  std::stringstream ssip_puerto_og(ip_puerto_origen);
  std::stringstream ssip_puerto_dst(ip_puerto_destino);

  getline(ssip_puerto_og, ip_og, ':');
  getline(ssip_puerto_og, puerto_og, ':');
  getline(ssip_puerto_dst, ip_dst, ':');
  getline(ssip_puerto_dst, puerto_dst, ':');
  
  //Setear puerto e ip
  this->setIpOrigen(ip_og);
  this->setPuertoOrigen(puerto_og);
  this->setIpDestino(ip_dst);
  this->setPuertoDestino(puerto_dst);

  // Transformar y setear ip
  this->setIpValue(ip_og, 0);
  this->setIpValue(ip_dst, 1);
}





// Comparacion de Registro por direccion ip
bool Incidencia::operator==(const Incidencia &other) {
  return this->ip_origen_value == other.ip_origen_value;
}

bool Incidencia::operator!=(const Incidencia &other) {
  return this->ip_origen_value != other.ip_origen_value;
}

bool Incidencia::operator>=(const Incidencia &other) {
  return this->ip_origen_value >= other.ip_origen_value;
}

bool Incidencia::operator<=(const Incidencia &other) {
  return this->ip_origen_value <= other.ip_origen_value;
}

bool Incidencia::operator>(const Incidencia &other) {
  return this->ip_origen_value > other.ip_origen_value;
}

bool Incidencia::operator<(const Incidencia &other) {
  return this->ip_origen_value < other.ip_origen_value;
}