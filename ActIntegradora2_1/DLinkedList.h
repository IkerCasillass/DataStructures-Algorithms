#ifndef _DLINKEDLIST_H_
#define _DLINKEDLIST_H_

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <chrono>
#include <fstream> // ayuda en lectura y escritura de archivo
#include "Registro.h"
#include "DLLNode.h"


template <class T> 
class DLinkedList {
  private:
    DLLNode<T> *head;
    DLLNode<T> *tail;
    int numElements;
  
  public:
    DLinkedList();
    DLinkedList(std::ifstream &archivo); //Constructor con archivo
    DLinkedList(const DLinkedList<T> &other); // Deeply copy
    ~DLinkedList();
    // Getters
    DLLNode<T>* getHead();
    DLLNode<T>* getTail();
    int getNumElements();
    // Setters
    void setHead(DLLNode<T> *_head);
    void setTail(DLLNode<T> *_Tail);
    void setNumElements(int _numElements);
    // Print
    void printList();
    void printListReversed();
    // Add & delete
    void addFirst(T value);
    void addLast(T value);
    bool deleteData(T value);
    bool deleteAt(int position);
    // Update & find
    T getData(int position);
    void updateData(T value, T newValue);  
    void updateAt(int position, T newValue);
    int findData(T value);
    // Reverse
    void invert();
    DLinkedList<T> getReversedSublist(int ini, int fin);
    // Sorting
    void quicksort(DLLNode<T> *low, DLLNode<T> *high, unsigned int &compara, unsigned int &swap);
    void sort(DLinkedList<T> Copy);
    DLLNode<T> * partition(DLLNode<T> *low, DLLNode<T> *high, unsigned int &compara, unsigned int &swap);
    void mergesort(DLLNode<T>* low, DLLNode<T>* high);
    
  
};

// Complejidad O(1)
template <class T> 
DLinkedList<T>::DLinkedList() {
  //std::cout << "---> Creando una lista doblemente ligada vacia: " << this << std::endl;
  head = nullptr;
  tail = nullptr;
  numElements = 0;
}

//Constructor con archivo
template <class T>
DLinkedList<T>::DLinkedList(std::ifstream &archivo) {
  // Inicializar Linked List
  head = nullptr;
  tail = nullptr;
  numElements = 0;

  // Variables para crear los registros
  std::string linea;
  std::string mes;
  std::string dia;
  std::string horas;
  std::string minutos;
  std::string segundos;
  std::string ip;
  std::string puerto;
  std::string error1;
  std::string error2;
  std::string error3;
  std::string error4;
  std::string error5;
  std::string error6;

  //Leer archivo
  if(archivo.is_open()) {

    // Obtener línea de archivo, y almacenar contenido en "linea"
    while (getline(archivo, linea)) {
      
      std::istringstream ss(linea);
      //Obtenemos los datos que estan separados por espacios
      ss>>mes>>dia>>horas>>ip>>error1>>error2>>error3>>error4>>error5>>error6;

      std::string error;
      //Juntamos las palabras del error en una sola cadena

      error = error1 + " " + error2+ " " + error3+ " " + error4+ " " + error5+ " " + error6;

      
      
      //Registro temporal
      Registro registrotemp(mes, dia, horas, "0", "0", ip, puerto, error);

      // Cambiar formato y setear hora
      registrotemp.cambiarFormato(horas, horas, minutos, segundos);

      //Añadiendo los registros a linked list 
      this->addLast(registrotemp);

      //Borrar caracteres del string para nueva cadena de error
      error1 = "";
      error2 = "";
      error3 = "";
      error4 = "";
      error5 = "";
      error6 = "";
    }
  }
}

// Deeply copy
template <class T>
DLinkedList<T>::DLinkedList(const DLinkedList<T> &other){

  if (other.head == NULL) {
        head = NULL;
        tail = NULL;
    
    }
    else {
        //copy all nodes of other to the caller object
        //attach first node to the head of the caller object
        DLLNode<T>* newNode = new DLLNode<T>();
        newNode->data = other.head->data;
        newNode->next = NULL;
        head = tail = newNode;

        //Now deep-copy all the remaining nodes of the Passed linked list object
        DLLNode<T>* PassedItr = other.head->next;
        DLLNode<T>* CallerItr = head;
        while (PassedItr != NULL){
    
            CallerItr->next = new DLLNode<T>();
            CallerItr->next->data = PassedItr->data;
            CallerItr->next->next = NULL;
            CallerItr = CallerItr->next; //move to newly added node
            PassedItr = PassedItr->next; //move one node further
            tail = tail -> next; // Recorrer tail
        }
    }
}

// Complejidad O(n)
template <class T> 
DLinkedList<T>::~DLinkedList() {
  //std::cout << "---> Liberando memoria de la lista doblemente ligada: " << this << std::endl;
  DLLNode<T> *p, *q;
  p = head;
  while (p != nullptr) {
    q = p->next;
    delete p;
    p = q;
  }
  head = nullptr;
  tail = nullptr;
  numElements = 0;
}

template <class T>
void DLinkedList<T>::setHead(DLLNode<T> *_head){
  head = _head;
}

template<class T>
void DLinkedList<T>::setTail(DLLNode<T> *_tail) {
  tail = _tail;
}

template <class T>

void DLinkedList<T>::setNumElements(int _numElements) {
  numElements = _numElements;
}


// Complejidad O(1)
template <class T> 
int DLinkedList<T>::getNumElements() { 
  return numElements; 
}

template <class T>
DLLNode<T>* DLinkedList<T>::getHead(){
  return head;
}
    
template <class T>
DLLNode<T>* DLinkedList<T>::getTail(){
  return tail;
}

// Complejidad O(n)
template <class T> 
void DLinkedList<T>::printList() {
  DLLNode<T> *ptr = head;
  while (ptr != nullptr) {
    std::cout << ptr->data << " ";
    ptr = ptr->next;
  }
  std::cout << std::endl;
}

// Complejidad O(n)
template <class T> 
void DLinkedList<T>::printListReversed() {
  DLLNode<T> *ptr = tail;
  while (ptr != nullptr) {
    std::cout << ptr->data << " ";
    ptr = ptr->prev;
  }
  std::cout << std::endl;
}

// Complejidad O(1)
template <class T>
void DLinkedList<T>::addFirst(T value) {
  // 1. crear un newNode
  DLLNode<T> *newNode = new DLLNode<T>(value);
  // Si la lista esta vacia
  if (head == nullptr && tail == nullptr) {
    head = newNode;
    tail = newNode;
  }
  else {
    // 2. apuntar newNode->next a donde esta head
    newNode->next = head;
    // 3. apuntar head->prev al newNode
    head->prev = newNode;
    // 3. Actualizar head para apuntar al newNode
    head = newNode;
  }
  numElements++;  
}

// Complejidad O(1)
template <class T>
void DLinkedList<T>::addLast(T value) {
  // La lista esta vacia
  if (head == nullptr && tail == nullptr)
    addFirst(value);
  else {
    // 1. crear un newNode
    DLLNode<T> *newNode = new DLLNode<T>(value);
    // 2. apuntar tail->next a newNode
    tail->next = newNode;
    newNode->prev = tail;
    // 3. actualizar tail para apuntar al newNode
    tail = newNode;
    numElements++;
  }
}

// Complejidad O(n)
template <class T>
bool DLinkedList<T>::deleteData(T value) {
  // La lista esta vacia
  if (head == nullptr && tail == nullptr)
    return false;
  else {
    DLLNode<T> *p = head;
    DLLNode<T> *previous = nullptr;
    while (p != nullptr && p->data != value) {
      previous = p;
      p = p->next;
    }
    // si no existe value en la lista
    if (p == nullptr)
      return false;
    // si debo borrar el primer elemento de la lista
    if (p != nullptr && p == head) {
      head = p->next;
      if (head == nullptr) // habia solo un nodo en la lista
        tail = nullptr;
      else
        head->prev = nullptr;
    } else if (p->next == nullptr) { // debo borrar el ultimo nodo 
      previous->next = nullptr;
      tail = previous;
    } else { // debo borrar cualquier otro nodo
      previous->next = p->next;
      p->next->prev = previous;
    }
    delete p;
    p = nullptr;
    numElements--;
    return true;
  }
}

// Complejidad O(n)
template <class T>
bool DLinkedList<T>::deleteAt(int position) {
  if (position < 0 || position >= numElements) {
    throw std::out_of_range("Indice fuera de rango");
  } else if (position == 0) {
    DLLNode<T> *p = head;
    // si la lista contiene un solo nodo
    if (head != nullptr && head->next == nullptr) {
      head = nullptr;
      tail = nullptr;
    } else {
      head = p->next;
      head->prev = nullptr; // cambio
    }
    delete p;
    p = nullptr;
    numElements--;
    return true;
  } else { // borrar cualquier otro elemento de la lista
    DLLNode<T> *p = head;
    DLLNode<T> *previous = nullptr;
    int index = 0;
    // buscar el indice del elemento a borrar
    while (index != position) {
      previous = p;
      p = p->next;
      index++;
    }
    // si debo borrar el ultimo elemento
    if (p->next == nullptr) {
      previous->next = nullptr;
      tail = previous;
    }
    else { // borrar cualquier otro nodo
      previous->next = p->next;
      p->next->prev = previous; // cambio
    }
    delete p;
    p = nullptr;
    numElements--;
    return true;
  }
}

// Complejidad O(n)
template <class T> T 
DLinkedList<T>::getData(int position) {
  if (position < 0 || position >= numElements) {
    throw std::out_of_range("Indice fuera de rango");
  } else {
    if (position == 0) { // si es el primero de la lista
      return head->data;
    }
    // debemos buscar el elemento
    DLLNode<T> *p = head;
    int index = 0;
    // buscar el indice del elemento a borrar
    while (p != nullptr) {
      if (index == position)
        return p->data;
      p = p->next;
      index++;
    }
    return {};
  }
}


// -------------------- TAREA ------------------

// Complejidad O(n)
template <class T> 
void DLinkedList<T>::updateData(T value, T newValue){
   // La lista esta vacia
  if (head == nullptr && tail == nullptr){}
  
  else {
    DLLNode<T> *p = head;
    while (p != nullptr && p->data != value) {
      p = p->next;
    }
    // si no existe value en la lista
    if (p == nullptr){}
    // remplazo el valor anterior por el nuevo
    else p->data = newValue;
  }
}

// Complejidad O(n)
template <class T> 
void DLinkedList<T>::updateAt(int position, T newValue){ // Define la funcion que toma dos argumentos y se esperan elementos de tipo T
  if(position < 0 || position >= numElements){
    throw std::out_of_range("La posicion esta fuera de rango");
  } // Comprueba si la posicion esta dentro del rango de la lista
  else if (position == 0){
    head->data = newValue; // Si la posicion es igual a cero se asigna al nodo "head"
  }
  else if (position == numElements - 1){
    tail->data = newValue; // Si la posición es igual al número de elementos menos uno el nuevo valor se asigna al nodo "tail"
  }
  else{
    DLLNode<T> *p = head;
    int i = 0;
    while (p != nullptr && i < position){
      p = p->next;
      i++;
    }
    p->data =newValue;
  } // Se utiliza el puntero si la posicion esta en otro lugar de la lista para poder recorrerla, la variable i realiza el seguimiento de los recorridos
}

// Complejidad O(n)
template <class T> 
int DLinkedList<T>::findData(T value){
  int indice = 0;
  
  // La lista esta vacia
  if (head == nullptr && tail == nullptr){
    return -1;
  }
  
  else {
    DLLNode<T> *p = head;
    while (p != nullptr && p->data != value) {
      p = p->next;
      indice++;
    }
    // si no existe value en la lista
    if (p == nullptr){
      return -1;
    }
  }
  return indice;
}

// Complejidad O(n)
template <class T> 
void DLinkedList<T>::invert(){
  // Si la lista no está vacía
  if(head != nullptr && tail != nullptr){ 
    
    DLLNode<T> *current = head;
    DLLNode<T> *temp = nullptr; // Auxiliar

    // Asignamos tail para comenzar a invertir la lista
    tail = head;
    // Mientras no se haya recorrido la lista completa
    while (current != nullptr) { 
      // Invertimos punteros
      temp = current->prev;
      current->prev = current->next;
      current->next = temp;
      // Avanzamos posicion
      current = current->prev; 
  }
  // Asignamos nuevo head
  head = temp->prev; 
  }
  
}

template <class T>
DLLNode<T>* DLinkedList<T>::partition(DLLNode<T> *low, DLLNode<T> *high, unsigned int &compara, unsigned int &swap) { // Declara la funcion partition que toma dos punteros a nodos
  T pivot = high->data; // Declara la variable pivot de tipo T e inicializa con el valor de data
  DLLNode<T> *i = low->prev; // Declara el puntero

  for (DLLNode<T> *j = low; j != high; j = j->next) {
    compara++;
    if (j->data <= pivot) {
      i = (i == nullptr) ? low : i->next;
      std::swap(i->data, j->data);
      swap++;
    } // Entra al bucle for que comienza en low y continua hasta high del nodo, en la cada iteracion se evalua el nodo j que sea menor que el valor del pivot.
  }

  i = (i == nullptr) ? low : i->next; // El puntero i se mueve adelante y se intercambian los valores de data entre el nodo i y el j
  std::swap(i->data, high->data);
  swap++;
  return i;
}

template <class T>
void DLinkedList<T>::quicksort(DLLNode<T> *low, DLLNode<T> *high, unsigned int &compara, unsigned int &swap) { // Toma dos argumentos de tipo puntero
  if (low != nullptr && high != nullptr && low != high && low != high->next) { // Comprueba si la sublista es valida y si hay mas de un elemento en ella
    DLLNode<T> *p = partition(low, high, compara, swap); // Esta linea sirve para la division de la sublista y devuelve un puntero nodo
    quicksort(low, p->prev, compara, swap);
    quicksort(p->next, high, compara, swap);
  } // Llama la funcion quicksort para ordenar las dos sub listas creadas por la funcion partition
}

//Complejidad Worst -- O(n^2),  AVG -- O(n log n)
template <class T>
void DLinkedList<T>::sort(DLinkedList<T> Copy) {
  // DLinkedList<Registro> Copia(&this); // Crear copia
  
  unsigned int comparaciones, swaps;
  
  std::cout <<"\nOrdenando lista...\n"<<std::endl;
  std::cout <<"---- Quicksort ----"<<std::endl;
  comparaciones = swaps = 0;
  
  auto startTime = std::chrono::high_resolution_clock::now(); //Iniciar tiempo
  quicksort(head, tail, comparaciones, swaps); //Llamar quicksort
  auto endTime = std::chrono::high_resolution_clock::now(); //Termina tiempo ejecucion
  auto totalTime = endTime - startTime;

  // Estadisticas del ordenamiento
  std::cout<<"comparaciones: "<<comparaciones <<std::endl;
  std::cout<<"swaps: "<<swaps <<std::endl;
  std::cout<<"Tiempo de ejecucion en ms: " << totalTime/std::chrono::milliseconds(1)<<std::endl;

  

  // Agregar llamda a Merge Sort
  // mergesort(Copy.getHead(), Copy.getTail())




}

template <class T>
void DLinkedList<T>::mergesort(DLLNode<T>* low, DLLNode<T>* high){
  if(low == high || low == nullptr || high == nullptr){
    return;
  }
  DLLNode<T>* mid = partition(low, high, compara, swap);
  
}


//Complejidad O(n)
template <class T>  
DLinkedList<T> DLinkedList<T>::getReversedSublist(int ini, int fin){
  int ixini = 0; // inicio
  int ixfin = 0; // fin

  DLinkedList<T> sublista;
  
  // Si la lista no está vacía
  if (head != nullptr && tail != nullptr){
    DLLNode<T> *p = head;
    while (p != nullptr && ixini != ini) {
      p = p->next;
      ixini++;
    }

    ixfin = ixini; /* Igualamos el final al inicio para iniciar nuestras iteraciones desde ahí */

    // Mientras no hayamos llegado al indice final
    while(p!= nullptr && ixfin <= fin) { 
      // addFirst para que la lista quede invertida O(1)
      sublista.addFirst(p->data); 
      // Avanzamos
      p = p->next;
      ixfin++;
    }
  }

  return sublista;
}


#endif // _DLINKEDLIST_H_



