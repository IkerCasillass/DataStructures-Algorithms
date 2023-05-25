#ifndef _REGISTRO_H_
#define _REGISTRO_H_

#include <string>
#include <vector>
// transformar una fecha a numero decimal
#include <ctime>  
#include <iostream>
//incluye las bibliotecas pala la implementacion de la clase registro

//Representar un evento (registro) dentro de la bitacora
class Registro {

  private:
    std::string mes, dia, horas, minutos, segundos, ip, puerto, falla;
    std::vector<std::string> meses = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    // Info struct tm https://cplusplus.com/reference/ctime/tm/
    struct tm dateStruct;
    // Unix timestamp (segundos transcurridos desde el 1 de enero de 1970)
    time_t fechaHora;
    // Valor entero de la direccion ip
    unsigned int ip_value; 

  public:
    Registro();
    Registro(std::string _mes, std::string _dia, std::string _horas, std::string _minutos, std::string _segundos, std::string _ip, std::string _puerto, std::string _falla);
    

    void setMes(std::string);
    void setDia(std::string);
    void setHoras(std::string);
    void setMinutos(std::string);
    void setSegundos(std::string);
    void setIp(std::string);
    void setPuerto(std::string);
    void setIp_value(unsigned int);
    void setIp_value(std::string);
    void setFalla(std::string);
    
    std::string getAll();
    std::string getMes();
    std::string getDia();
    std::string getHoras();
    std::string getMinutos();
    std::string getSegundos();
    std::string getIp();
    std::string getPuerto();
    std::string getFalla();
    unsigned int getIp_value();
    time_t getFechaHora();

    void cambiarFormato(std::string fechahora, std::string &hora, std::string &minuto, std::string &segundo, std::string ip_puerto, std::string &ip, std::string &puerto);

    // Sobre carga de operadores
    bool operator ==(const Registro&);
    bool operator !=(const Registro&);
    bool operator >(const Registro&);
    bool operator <(const Registro&);
    bool operator >=(const Registro&);
    bool operator <=(const Registro&);
    
};



#endif   // _REGISTRO_H_
