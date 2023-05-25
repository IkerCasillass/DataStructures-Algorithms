#ifndef _STACKLINKEDLIST_H_
#define _STACKLINKEDLIST_H_

#include <iostream>
#include <stdexcept>
#include "StackNode.h"
using namespace std;

template <class T>
class StackLinkedList {
  private:
    StackNode<T> *top;
    StackNode<T> *tail;
    int numElements;

  public:
    StackLinkedList();
    ~StackLinkedList();
    int getNumElements();
    void print();
    bool isEmpty();
    void push(T value);
    void pop();
    T getTop();

};


template <class T>
StackLinkedList<T>::StackLinkedList() {
  //std::cout << "---> Creando un Stack vacio: " << this << std::endl;
  top = nullptr;
  tail = nullptr;
  numElements = 0;
}

template<class T>
StackLinkedList<T>::~StackLinkedList() {
  //std::cout << "---> Liberando memoria del Stack: " << this << std::endl;
  StackNode<T> *p, *q;
  p = top;
  while (p != nullptr) {
    q = p->next;
    delete p;
    p = q;
  }
  top = nullptr;
  tail = nullptr;
  numElements = 0;
}

template <class T> 
int StackLinkedList<T>::getNumElements() {
  return numElements;
}

template<class T>
void StackLinkedList<T>::print() {
  StackNode<T> *ptr = top;
  while (ptr != nullptr) {
      std::cout << ptr->data << " ";
      ptr = ptr->next;
  }
  std::cout << std::endl;
}

template <class T> 
bool StackLinkedList<T>::isEmpty() {
  return (top == nullptr);
}

template <class T>
void StackLinkedList<T>::push(T value){ //Define la función push para agregar un elemento a la pila
  StackNode<T> *newNode = new StackNode<T>(value); // Crea un nuevo nodo de StackNode<T> y asigna su valor a la variable newNode
  newNode->next = top; //Establece el siguiente nodo de newNode como el nodo top 
  top = newNode; //Establece el nuevo nodo como la parte superior de la pila.
  numElements++; //Incrementa el contador
}

template <class T>
void StackLinkedList<T>::pop(){ //Define la función pop para eliminar el elemento superior de la pila
  if(isEmpty()){ //Verifica si la pila está vacía
    std::cout << "El Stack esta vacio" << std::endl;
    return;
  }
  StackNode<T> *temp = top; //Crea un puntero temp y lo asigna al nodo superior actual
  top = top->next; //Establece el siguiente nodo de la pila para que sea la superior
  delete temp;
  numElements--; //Decrementa el contador
}

template <class T>
T StackLinkedList<T>::getTop(){ //Define la función getTop para obtener el elemento superior de la pila
  if(isEmpty()){
    throw std::out_of_range("El Stack esta vacio");
  }
  return top->data; //Devuelve el valor de datos del nodo superior de la pila
}


#endif // _STACKLINKEDLIST_H_
