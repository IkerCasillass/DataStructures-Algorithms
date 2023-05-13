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
    void search();
    // Reverse
    void invert();
    DLinkedList<T> getReversedSublist(int ini, int fin);
    // For sorting
    void quicksort(DLLNode<T> *low, DLLNode<T> *high, unsigned int &compara, unsigned int &swap);
    void sort(DLinkedList<T> Copy);
    DLLNode<T> * partition(DLLNode<T> *low, DLLNode<T> *high, unsigned int &compara, unsigned int &swap);
    void mergeSort(DLLNode<T> *&head, DLLNode<T> *&tail, unsigned int &compara);
    DLLNode<T> *getMiddle(DLLNode<T> *head);
    DLLNode<T> *merge(DLLNode<T> *left, DLLNode<T> *right, unsigned int &compara);
    // Search
    DLLNode<T>* binarySearch(DLLNode<T> *head, T key, unsigned int &compara);
    DLLNode<T>* binarySearch2(DLLNode<T> *head, int value);
    // DLLNode<T>* binarySearch(DLLNode<T> *head, T key, unsigned int &compara);
    DLLNode<T>* middle2(DLLNode<T>* start, DLLNode<T>* last);
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

template <class T>
void DLinkedList<T>::search(){//Comienza la definición de la función search en la clase DLinkedList. La plantilla de clase se utiliza para que la lista pueda contener cualquier tipo de objeto T.
  std::string fecha_inicial, fecha_final, mes, dia, horas, minutos, segundos;
  int indice_inicial = 0, indice_final = 0, rango = 0;
  unsigned int compara = 0;
  DLLNode<Registro>* NodoInicial, *NodoFinal;//Se declaran varias variables utilizadas en la función. Se crean dos cadenas de caracteres para almacenar la fecha inicial y final.
  
  std::cout<<"\n----------------------------------"<<std::endl;
  std::cout<<"--------Busqueda por fecha--------\n"<<std::endl;
  std::cout<<"Ingresa la fecha incial (Mes dd hh:mm:ss): "<<std::endl;
  std::getline(std::cin, fecha_inicial);
  std::cout<<"Ingresa la fecha final (Mes dd hh:mm:ss): "<<std::endl;
  std::getline(std::cin, fecha_final);//Estas líneas imprimen mensajes en la consola para indicar al usuario que se está realizando una búsqueda por fecha y se le solicita que ingrese la fecha inicial y final en el formato especificado (Mes dd hh:mm:ss). Las fechas se leen desde la entrada estándar utilizando getline.

  //convertir a formato deseado
  std::istringstream fi(fecha_inicial);
  fi>>mes>>dia>>horas;

  //Crear Registro_inicial
  Registro Registro_inicial(mes, dia, horas, "0", "0", "", "", "");
  
  Registro_inicial.cambiarFormato(horas, horas, minutos, segundos);

  // NodoInicial = this->binarySearch(head, Registro_inicial, compara);
  NodoInicial = this->binarySearch2(head, Registro_inicial.getFechaHora());
  // Llamada a Binary Search con Registro_inicial.getFechaHora()
  
  // DLinkedList<T> lista;
  // T key;
  // DLLNode<T> *resultado = lista.binarySearch(lista.getHead(), key, compara);

  // NodoInicial = this->binarySearch(head, Registro_inicial.getFechaHora(), compara);

  if(NodoInicial == nullptr){
    std::cout<<"\nLa fecha inicial no se encuentra en el archivo, ingrese un rango valido" <<std::endl;
    exit(0);
  }
  else{
    std::cout<<"\nFecha inicial encontrada en indice " << this->findData(NodoInicial->data) <<std::endl;
  }

  //convertir a formato deseado
  std::istringstream ff(fecha_final);
  ff>>mes>>dia>>horas;

  //Crear Registro_final
  Registro Registro_final(mes, dia, horas, "0", "0", "", "", "");

  Registro_final.cambiarFormato(horas, horas, minutos, segundos);


  NodoFinal = this->binarySearch2(head, Registro_final.getFechaHora());

 
  if(NodoFinal == nullptr){
    std::cout<<"\nLa fecha final no se encuentra en el archivo, ingrese un rango valido" <<std::endl;
    exit(0);
  }
  else{
    std::cout<<"\nFecha final encontrada en indice " << this->findData(NodoFinal->data)<<std::endl;
  }


  // Mostrar datos dentro del rango y guardar en archivo
  rango = findData(NodoFinal->data) - findData(NodoInicial->data);
  std::fstream file; //Crear archivo para escribir
  std::cout<<"\nMostrando " << rango+1 << " Registros:\n" << std::endl;

  if(file) {
    
    file.open("resultado_busqueda.txt", std::ios_base::out);
    
    for(int i=this->findData(NodoInicial->data); i< this->findData(NodoFinal->data); i++){
      // Guardar registros en archivo
      std::string actual = this->getData(i).getAll()<<std::endl;
      file<<actual<<std::endl;
      //Mostrar datos 
      std::cout<<this->getData(i).getAll()<<std::endl; 
    }
  }
  else {
    std::cout << "Error al crear el archivo" << std::endl;
  }
  
} 


//Binary Search
//Referencia.- GeeksforGeeks. (2023). Binary Search on Singly Linked List. GeeksforGeeks. https://www.geeksforgeeks.org/binary-search-on-singly-linked-list/
template <class T>
DLLNode<T>* DLinkedList<T>::binarySearch(DLLNode<T> *head, T key, unsigned int &compara){//La definicion de la funcion de busqueda binaria, la cual toma tres argumentos, un puntero, la clave y una variable de referencia, para devolver un puntero con la clave.
  if (!head || head->data.getFechaHora() == key.getFechaHora()){//Se comprueba si el puntero al primer nodo es nulo o si la clave se encuentra en el primer nodo.
    return head;
  }
  DLLNode<T> *left = nullptr, *right = nullptr;//Inicializa dos punteros, left y right.
  DLLNode<T> *mid = head;//Inicializa un puntero mid.
  while(mid){
    compara++;//Incrementa el numero de comparaciones. 
    if(mid->data.getFechaHora() < key.getFechaHora()){//Compara la clave de busqueda con la clave almacenada en el nodo mid, si la clave es mayor que la clave del nodo actual se mueve a la derecha de la lista. 
      left = mid;//Se establece el puntero izquierdo en mid si la clave es menor o igual en el nodo actual.
      mid = mid->next;
    }
    else{
      right = mid;
      mid = mid->prev;
    }
  }
  if(left){
    return binarySearch(left, key, compara);//Si el puntero izq. no es nulo se llama la funcion de busqueda binaria con el puntero izquierdo. 
  }
  else if (right){
    return binarySearch(right , key, compara);
  }
  else{
    return nullptr;
  }
}

//Otro metodo de Binary Search

template <class T>
DLLNode<T>* DLinkedList<T>::binarySearch2(DLLNode<T>* head, int value) {//Se define una función llamada binarySearch2 que toma como argumentos un puntero a un nodo de la lista doblemente enlazada y un valor entero a buscar en la lista.
    DLLNode<T>* start = head;//Se crea un puntero llamado start que apunta al nodo de la lista pasado como argumento.
    DLLNode<T>* last = nullptr;//Se crea un puntero llamado last que inicialmente apunta a nullptr.

    do {
        DLLNode<T>* mid = middle2(start, last);

        if (!mid){
          std::cout<<"Returned null" <<std::endl;// Si mid es nullptr, se imprime un mensaje de depuración que indica que se ha devuelto un valor nullptr.
          return nullptr;
        }
            

        if (mid->data.getFechaHora() == value){// Se verifica si el valor del nodo medio mid es igual al valor buscado value.
          std::cout <<"Returned mid" <<std::endl;//Si el valor de mid es igual a value, se imprime un mensaje de depuración que indica que se ha devuelto el nodo medio mid.
          return mid;
        }
            
        else if (mid->data.getFechaHora() < value)// Si el valor del nodo medio mid es menor que el valor buscado value.
            start = mid->next;
        else
            last = mid;
    } while (last == nullptr || last != start);// Se cierra el bucle do-while, que se repetirá mientras last sea nullptr o last y start no apunten al mismo nodo.

    return nullptr;
}





// DLLNode<Registro> *indice_inicial = lista_enlazada.binarySearch(lista_enlazada.getHead(), Registro_inicial, compara);
//   if(!indice_inicial){
//     std::cout << "Ingrese rango valido" << std::endl;
//     exit(0);
//   }
//   else{
//     int posicion = 0;
//     DLLNode<Registro> *temp = lista_enlazada.getHead();
//     while(temp != indice_inicial){
//       posicion++;
//       temp = temp->next;
//     }
//     std::cout << "Se encuentra en la posicion: " << posicion << std::endl;
//   }

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

  comparaciones = swaps = 0;
  
  std::cout <<"---- Merge Sort ----"<<std::endl;
   auto head2 = Copy.getHead();
  auto tail2 = Copy.getTail();
  
  startTime = std::chrono::high_resolution_clock::now(); //Iniciar tiempo
  mergeSort(head2, tail2, comparaciones); //LLamar merge sort
  endTime = std::chrono::high_resolution_clock::now(); //Termina tiempo ejecucion
  totalTime = endTime - startTime;
  std::cout<<"comparaciones: "<<comparaciones <<std::endl;
  std::cout<<"Tiempo de ejecucion en ms: " << totalTime/std::chrono::milliseconds(1)<<std::endl;


  // std::cout<<"\n10 primeros registros de lista ordenada por merge sort:\n" <<std::endl;
  
  // for(int i=0; i<10; i++) {
  //   std::cout << Copy.getData(i).getAll() << std::endl;
  // }

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

    ixfin = ixini; /* Igualamos el final al inicio para iniciar nuestras iteraciones desde ahi */

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


template <class T>
void DLinkedList<T>::mergeSort(DLLNode<T> *&head, DLLNode<T> *&tail, unsigned int &compara) {//Definicion de la funcion mergeSort que tiene de parametro de plantilla T, tomando dos punteros de tipo DLLNode, siendo head y tail.
    if (!head || !head->next) {
        return;
    }//Se verifica si la lista esta vacia o si tiene solo un elemento, si la condicion se cumple la funcion sale de la funcion ya que no se debe ordenar nada. 
    DLLNode<T> *mid = getMiddle(head);//Se devuelve un puntero.
    DLLNode<T> *midNext = mid->next;
    if (midNext) {
      midNext->prev = nullptr;
    }//Este bloque se inicializa con el siguiente nodo despues del nodo mid y se verifica si midNext es valido, de ser asi se establece el puntero prev del nodo midNexty como nullptr. 
    mid->next = nullptr;
    mergeSort(head, mid, compara);
    mergeSort(midNext, tail, compara);//Se llama recursivamente a la funcion mergeSort para ordenar las dos mitades de la lista. 
    DLLNode<T> *merged = merge(head, midNext, compara);
    while (merged->prev) {
        merged = merged->prev;
    }
    head = merged;
    while (merged->next) {
        merged = merged->next;
    }
    tail = merged;//El puntero merged se inicializa con el resultado de merge que se combina las dod mitades ordenadas de la lista en una sola lista ordenada. 
}

/*
template <class T> 
void DLinkedList<T>::mergeSort(DLLNode<T> *&head, DLLNode<T> *&tail, unsigned int &compara){
if(!head ||!head->next){
return;
}
DLLNode<T> *mid = getMiddle(head);
if(mid){
DLLNode<T> *midNext = mid->next;
if(midNext){
midNext->prev = nullptr
}
mid->next = nullptr;
mergeSort(head, mid, compara);
mergeSort(midNext, tail, compara);
DLLNode<T> *merged = merge(head, midNext, compara);
if(merged){
while(merged->prev){
merged = merged->prev;
}
head = merged;
while (merged->next){
merged = merged->next
}
tail = merged;
}
}
}
*/




template <class T>//Se declara la plantilla de clase para poder utilizar cualquier tipo de datos en la lista doblemente ligada.
DLLNode<T> *DLinkedList<T>::merge(DLLNode<T> *left, DLLNode<T> *right, unsigned int &compara) {// La funcion merge toma dos nodos left y right y un entero por referencia y se devuelve un puntero a 
    if (!left) {
        return right;// Si el nodo izq. es nulo la funcion devuelve el nodo derecho. 
    }
    if (!right) {
        return left;// Si el nodo derecho es nulo se devuelve el nodo izq.
    }
    DLLNode<T> *mergedHead = nullptr;// Se crea un puntero a DLLNode llamado mergedHead y se inicializa como nulo.
    compara++;
    if (left->data <= right->data) {
        mergedHead = left;
        mergedHead->next = merge(left->next, right, compara);//Si el valor del dato en el nodo izquierdo es menor o igual que el valor del dato en el nodo derecho, se establece mergedHead en el nodo izq.
    } else {
        mergedHead = right;
        mergedHead->next = merge(left, right->next, compara);//Si el valor del dato en el nodo izquierdo es mayor que el valor del dato en el nodo derecho, se establece mergedHead en el nodo derecho. Se llama a la función merge recursivamente con left y right->next como parámetros, y el resultado se asigna al puntero "next" del nodo mergedHead.
    }
    mergedHead->next->prev = mergedHead;
    return mergedHead;//Se devuelve el puntero que apunta al nodo inicial. 
}
//Otro metodo del merge
/*
template <class T>
DLLNode<T>* DLinkedList<T>::merge(DLLNode<T>* left, DLLNode<T>* right, unsigned int& compara) {
    if (!left) {
        return right;
    }
    if (!right) {
        return left;
    }

    DLLNode<T>* mergedHead = nullptr;
    compara++;
    if (left->data <= right->data) {
        mergedHead = left;
        mergedHead->next = merge(left->next, right, compara);
    } else {
        mergedHead = right;
        mergedHead->next = merge(left, right->next, compara);
    }

    if (mergedHead->next) {
        mergedHead->next->prev = mergedHead;
    }
    return mergedHead;
}
*/

template <class T>
DLLNode<T> *DLinkedList<T>::getMiddle(DLLNode<T> *head) {
    DLLNode<T> *slow = head;
    DLLNode<T> *fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
//Otro metodo del middle
template <class T>
DLLNode<T>* DLinkedList<T>::middle2(DLLNode<T>* start, DLLNode<T>* last) {
    if (!start)
        return nullptr;

    DLLNode<T>* slow = start;
    DLLNode<T>* fast = start->next;

    while (fast != last && fast != nullptr) {
        fast = fast->next;
        if (fast != last && fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    return slow;
}


#endif // _DLINKEDLIST_H_
