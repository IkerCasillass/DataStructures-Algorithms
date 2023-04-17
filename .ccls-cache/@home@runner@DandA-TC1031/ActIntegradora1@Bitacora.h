#include <iostream>
#include <chrono>
#include <fstream> // ayuda en lectura y escritura de archivo
#include <sstream> // facilita separar el string
#include <stdlib.h> //exit
#include "Registro.h"

class Bitacora {

private:
  std::vector<Registro> texto;


public:
Bitacora();
Bitacora(std::ifstream &archivo);

void setTexto(std::vector<Registro> _texto);

std::vector<Registro> getTexto();

void buscar(std::vector<Registro> vectorSorted);
std::vector<Registro> ordenar(const std::vector<Registro> &listaRegistros, int size);
void imprimir();





};