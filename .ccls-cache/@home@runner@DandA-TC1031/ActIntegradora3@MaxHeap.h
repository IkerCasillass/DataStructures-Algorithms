    #ifndef _MAXHEAP_H_
#define _MAXHEAP_H_

#include "Registro.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <sstream>
#include <fstream>

template <class T> class MaxHeap {
private:
  // contiene los elementos del heap
  std::vector<T> data;
  std::vector<T> insertedElements;

  // capacidad maxima del heap
  int maxSize;
  // tamano actual del heap
  int currentSize;

  int parent(int k);
  int left(int k);
  int right(int k);

public:
  MaxHeap(int maxCapacity);
  MaxHeap(std::ifstream &archivo, int maxCapacity); // Constructor con archivo
  ~MaxHeap();
  bool isEmpty();
  int getMaxCapacity();
  int getCurrentSize();
  std::vector<T> getData();

  void printHeap();
  void push(T key);
  T getTop();
  void pop();
    // TO-DO
  void heapSort();
  std::vector<T> getInsertedElements();
};


// Constructores

template <class T> 
MaxHeap<T>::MaxHeap(int maxCapacity) {
  maxSize = maxCapacity;
  currentSize = 0;
  data.resize(maxSize);
}

template <class T>
MaxHeap<T>::MaxHeap(std::ifstream &archivo, int maxCapacity) {
  // Constructor con archivo
  maxSize = maxCapacity;
  currentSize = 0;
  data.resize(maxSize);

  // Variables para crear los registros
  std::string linea;
  std::string mes;
  std::string dia;
  std::string horas;
  std::string minutos;
  std::string segundos;
  std::string ip_puerto;
  std::string ip;
  std::string puerto;
  std::string error1;
  std::string error2;
  std::string error3;
  std::string error4;
  std::string error5;
  std::string error6;

  // Leer archivo
  if (archivo.is_open()) {

    // Obtener línea de archivo, y almacenar contenido en "linea"
    while (getline(archivo, linea)) {

      std::istringstream ss(linea);
      // Obtenemos los datos que estan separados por espacios
      ss >> mes >> dia >> horas >> ip_puerto >> error1 >> error2 >> error3 >> error4 >>
          error5 >> error6;

      std::string error;
      // Juntamos las palabras del error en una sola cadena

      error = error1 + " " + error2 + " " + error3 + " " + error4 + " " +
              error5 + " " + error6;

      // Registro temporal
      Registro registrotemp(mes, dia, horas, "0", "0", ip, "0", error);

      // Cambiar formato y setear hora
      registrotemp.cambiarFormato(horas, horas, minutos, segundos, ip_puerto, ip, puerto);

      // Añadir registros a Binary Heap 
      
      this->push(registrotemp);

      // Borrar caracteres del string para nueva cadena de error
      error1 = "";
      error2 = "";
      error3 = "";
      error4 = "";
      error5 = "";
      error6 = "";
    }
  }
}

// Destructor
template <class T> MaxHeap<T>::~MaxHeap() {
  maxSize = 0;
  currentSize = 0;
  data.clear();
}


// Getters

template <class T> 
int MaxHeap<T>::getMaxCapacity() { return maxSize; }

template <class T>
int MaxHeap<T>::getCurrentSize() { return currentSize; }

template <class T> 
std::vector<T> MaxHeap<T>::getData(){ return data; }


// Metodos

template <class T> 
bool MaxHeap<T>::isEmpty() { return (currentSize <= 0); }


template <class T> 
void MaxHeap<T>::printHeap() {
  std::cout << "Contenido del maxheap:" << std::endl;
  for (int i = 0; i < currentSize; i++) {
    std::cout << data[i] << " ";
  }
  std::cout << std::endl;
}

template <class T>
int MaxHeap<T>::parent(int k) { return (k - 1) / 2; }

template <class T>
int MaxHeap<T>::left(int k) { return (2 * k + 1); }

template <class T>
int MaxHeap<T>::right(int k) { return (2 * k + 2); }

template <class T>
void MaxHeap<T>::push(T key) {
  
  if (currentSize == maxSize) {
    throw std::out_of_range("Overflow: no se puede insertar la llave");
  }
  // Insertamos la nueva llave al final del vector
  int k = currentSize;
  data[k] = key;
  currentSize++;
  // Reparar las propiedades del maxheap si son violadas
  while (k != 0 && data[parent(k)] < data[k]) {
    std::swap(data[k], data[parent(k)]);
    k = parent(k);
  }
}

template <class T>
T MaxHeap<T>::getTop() {
  
  if (isEmpty()) {
    throw std::out_of_range("El heap esta vacio");
    return {};
  }
  return data[0];
}


// Complejidad O(log n)
// Consultado: https://www.geeksforgeeks.org/heap-sort/
template <class T> void MaxHeap<T>::pop() {
  // heap vacio
  if (isEmpty()) {
    throw std::out_of_range("El heap esta vacio");
  }
  // Cambia primer elemento con ultimo
  data[0] = data[currentSize - 1];
  // size -1
  currentSize--;
  int k = 0;
  // Mientras left child tenga un indice valido
  while (left(k) < currentSize) {
    int j = left(k);
    if (right(k) < currentSize && data[right(k)] > data[left(k)]) {
      j = right(k);
    }

    if (data[k] >= data[j]) {
      // Max heap ya esta acomodado
      break;
    }
    std::swap(data[k], data[j]);
    k = j;
  }
}

template <class T>
std::vector<T> MaxHeap<T>::getInsertedElements(){
  return insertedElements;
}

template <class T> void MaxHeap<T>::heapSort() {
  // heap vacio
  if (isEmpty()) {
    throw std::out_of_range("El heap esta vacio");
  }
  // Cambia primer elemento con ultimo
  data[0] = data[currentSize - 1];
  // size -1
  //currentSize--;
  int k = 0;
  // Mientras left child tenga un indice valido
  while (left(k) < currentSize) {
    int j = left(k);
    if (right(k) < currentSize && data[right(k)] > data[left(k)]) {
      j = right(k);
    }

    if (data[k] >= data[j]) {
      // Max heap ya esta acomodado
      break;
    }
    std::swap(data[k], data[j]);
    k = j;
  }
}

#endif // _MAXHEAP_H_