#ifndef _INCIDENCIA_H_
#define _INCIDENCIA_H_

#include <iostream>

class Incidencia {
  private:
    std::string mes, dia, horas, ip_origen, puerto_origen, ip_destino, puerto_destino, razon, peso_inicial;
    int peso, num_vecinos;

  public:
    unsigned int ip_origen_value, ip_destino_value;

    Incidencia();
    Incidencia(std::string _mes, std::string _dia, std::string _horas, std::string _ip_origen, std::string _ip_destino, std::string _peso, std::string razon);

    ~Incidencia();

    void setMes(std::string);
    void setDia(std::string);
    void setHoras(std::string);
    void setMinutos(std::string);
    void setSegundos(std::string);
    void setIpOrigen(std::string);
    void setIpOrigenValue(unsigned int);
    void setPuertoOrigen(std::string);
    void setIpDestino(std::string);
    void setPuertoDestino(std::string);
    void setPesoInicial(std::string);
    void setPeso(int);
    void setRazon(std::string);
    void setNumVecinos(int);
    void setIpValue(std::string, int n); // string ip y 0 - 1 para conexion origen o destino
    
    std::string getAll();
    std::string getMes();
    std::string getDia();
    std::string getHoras();
    std::string getMinutos();
    std::string getSegundos();
    std::string getIpOrigen();
    std::string getIpDestino();
    unsigned int getIpOrigenValue();
    std::string getPuertoOrigen();
    std::string getPuertoDestino();
    int getPeso();
    int getNumVecinos();
    std::string getPesoInicial();
    std::string getRazon();

    void cambiarFormato(std::string, std::string, std::string);

    // Sobre carga de operadores
    bool operator !=(const Incidencia&);
    bool operator >(const Incidencia&);
    bool operator ==(const Incidencia&);
    bool operator <(const Incidencia&);
    bool operator >=(const Incidencia&);
    bool operator <=(const Incidencia&);


};



#endif //INCIDENCIA.h