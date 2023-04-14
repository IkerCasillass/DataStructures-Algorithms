#ifndef _DLINKEDLIST_H_
#define _DLINKEDLIST_H_

#include <iostream>
#include <stdexcept>
#include "DLLNode.h"

template <class T> 
class DLinkedList {
  private:
    DLLNode<T> *head;
    DLLNode<T> *tail;
    int numElements;
  
  public:
    DLinkedList();
    ~DLinkedList();
    int getNumElements();
    void printList();
    void printListReversed();
    void addFirst(T value);
    void addLast(T value);
    bool deleteData(T value);
    bool deleteAt(int position);
    T getData(int position);
    void updateData(T value, T newValue);  
    void updateAt(int position, T newValue);
    int findData(T value);
    void invert();
    void sort();
    DLinkedList<T> getReversedSublist(int ini, int fin);
    
    // TO-DO
    //void updateData(T value, T newValue);
    //void updateAt(int position, T newValue);
    //int findData(T value);
    //void invert();
    //void sort();
    //DLinkedList<T> getReversedSublist(int ini, int fin);
  
};

// Complejidad O(1)
template <class T> 
DLinkedList<T>::DLinkedList() {
  //std::cout << "---> Creando una lista doblemente ligada vacia: " << this << std::endl;
  head = nullptr;
  tail = nullptr;
  numElements = 0;
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

// Complejidad O(1)
template <class T> 
int DLinkedList<T>::getNumElements() { 
  return numElements; 
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

template <class T> 
void DLinkedList<T>::updateAt(int position, T newValue){
  
}

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

template <class T> 
void DLinkedList<T>::invert(){
  if(head != nullptr && tail != nullptr){ // Si la lista no está vacía
    
    DLLNode<T> *current = head;
    DLLNode<T> *temp = nullptr; // Auxiliar

    while (current != nullptr) { // Mientras no se haya recorrido la lista completa
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
void DLinkedList<T>::sort(){
 
}

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
      // addFirst para que la lista quede invertida
      sublista.addFirst(p->data); 
      // Avanzamos
      p = p->next;
      ixfin++;
    }
  }

  return sublista;
}


#endif // _LINKEDLIST_H_



