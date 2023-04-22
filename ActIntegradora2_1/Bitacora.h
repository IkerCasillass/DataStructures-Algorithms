#ifndef _BITACORA_H_
#define _BITACORA_H_


#include <iostream>
#include <fstream> // ayuda en lectura y escritura de archivo
#include <stdlib.h> //exit
#include "Registro.h"
#include "DLinkedList.h"

class Bitacora {

private:
   DLinkedList<Registro> texto;


public:
Bitacora();
Bitacora(std::ifstream &archivo);

void setTexto(DLinkedList<Registro> _texto);

DLinkedList<Registro> getTexto();

void buscar(std::vector<Registro> vectorSorted);
std::vector<Registro> ordenar(const std::vector<Registro> &listaRegistros, int size);
void imprimir();





};

#endif // _BITACORA_H_