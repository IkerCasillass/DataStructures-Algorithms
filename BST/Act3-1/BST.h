#ifndef _BST_H_
#define _BST_H_

#include <iostream>
#include "BSTNode.h"
#include "QueueLinkedList.h"

template <class T> 
class BST {
  private:
    BSTNode<T> *root;
    void clearMemory(BSTNode<T> *p);
    BSTNode<T> *insertRecursive(BSTNode<T> *p, T value);
    BSTNode<T> *deleteRecursive(BSTNode<T> *p, T value);
    BSTNode<T> *getSuccessor(BSTNode<T> *p);
    void print2D(BSTNode<T> *p, int space);
    void recursiveInorder(BSTNode<T> *p);
    void recursivePreorder(BSTNode<T> *p);
    void recursivePostorder(BSTNode<T> *p);
    void auxiliarLevelByLevel(BSTNode<T> *p);

  public:
    BST();
    ~BST();
    bool search(T value);
    void insert(T value);
    void deleteNode(T value);
    void print();
    void inorder();
    void preorder();
    void postorder();
    void levelByLevel();
    void visit(int option);
    int height();
    void ancestors(T value);
    int whatLevelAml(T value);

};

// O(1)
template <class T> 
BST<T>::BST() {
  root = nullptr;
}

// O(n)
template <class T> 
BST<T>::~BST() {
  clearMemory(root);
}

// O(n)
template <class T> 
void BST<T>::clearMemory(BSTNode<T> *p) {
  if (p != nullptr) {
    clearMemory(p->left);
    clearMemory(p->right);
    delete p;
    p = nullptr;
  }
}

// O(h) donde h es la altura del BST
template <class T> 
bool BST<T>::search(T value) {
  BSTNode<T> *p = root;
  while (p != nullptr) {
    if (p->data == value)
      return true;
    else
      p = (value < p->data) ? p->left : p->right;
  }
  return false;
}

// O(h) donde h es la altura del BST
template <class T> 
BSTNode<T> * BST<T>::insertRecursive(BSTNode<T> *p, T value) {
  if (p == nullptr)  // El BST esta vacio
    p = new BSTNode<T>(value);
  else if (value < p->data) // insercion a la izquierda
    p->left = insertRecursive(p->left, value);
  else if (value > p->data) // insercion a la derecha
    p->right = insertRecursive(p->right, value);
  else 
    std::cout << "El elemento " << value << " ya existe en el BST" << std::endl;
  return p;
}

// O(h) donde h es la altura del BST
template <class T> 
void BST<T>::insert(T value) {
  root = insertRecursive(root, value);
}

// O(h) donde h es la altura del BST
template <class T> 
BSTNode<T> *BST<T>::getSuccessor(BSTNode<T> *p) {
  BSTNode<T> *current = p;
  while (current && current->left != nullptr) {
    current = current->left;
  }
  return current;
}

// O(h) donde h es la altura del BST
template <class T> 
BSTNode<T> *BST<T>::deleteRecursive(BSTNode<T> *p, T value) {
  BSTNode<T> *current = p;
  // caso base, arbol BST vacio
  if (p == nullptr)
    return p;
  if (value < p->data)
    p->left = deleteRecursive(p->left, value);
  else if (value > p->data)
    p->right = deleteRecursive(p->right, value);
  else { // localizamos el nodo a borrar
    // Caso 1: El nodo a borrar no tiene hijos
    if (p->left == nullptr && p->right == nullptr) {
      delete p;
      p = nullptr;
      return p;
    } // Caso 2: El nodo a borrar solo tiene un hijo
    else if (p->left == nullptr) { // tiene solo hijo derecho
      current = p->right;
      delete p;
      p = nullptr;
      return current;
    } else if (p->right == nullptr) { // tiene solo hijo izquierdo
      current = p->left;
      delete p;
      p = nullptr;
      return current;
    }
    // Caso 3: El nodo a borrar tiene dos hijos
    current = getSuccessor(p->right);
    p->data = current->data;
    p->right = deleteRecursive(p->right, current->data);
  }
  return p;
}

// O(h) donde h es la altura del BST
template <class T> 
void BST<T>::deleteNode(T value) {
  root = deleteRecursive(root, value);
}

// O(n)
template <class T> 
void BST<T>::print2D(BSTNode<T> *root, int space) {
  // Caso base
  if (root == nullptr)
    return;
  // Incrementa la distancia entre niveles
  space += 5;

  // Procesa hijo derecho
  print2D(root->right, space);
  // Imprime el nodo actual despues de los espacios necesarios
  std::cout << std::endl;
  for (int i = 5; i < space; i++)
    std::cout << " ";
  std::cout << root->data << std::endl;
  // Procesa el hijo izquierdo
  print2D(root->left, space);
}

// O(n)
template <class T> 
void BST<T>::print() { 
  print2D(root, 0); 
}

// O(n)
template <class T>
void BST<T>::recursiveInorder(BSTNode<T> *p) {
  if (p != nullptr) {
    recursiveInorder(p->left);
    std::cout << p->data << " ";
    recursiveInorder(p->right);
  }
}

// O(n)
template <class T> 
void BST<T>::inorder() {
  std::cout << "inorder():" << std::endl;
  recursiveInorder(root);
  std::cout << std::endl;
}

// O(n)
template <class T>
void BST<T>::recursivePreorder(BSTNode<T> *p) {
  if (p != nullptr) {
    std::cout << p->data << " ";
    recursivePreorder(p->left);
    recursivePreorder(p->right);
  }
}

// O(n)
template <class T> 
void BST<T>::preorder() {
  std::cout << "preorder():" << std::endl;
  recursivePreorder(root);
  std::cout << std::endl;
}

// O(n)
template <class T>
void BST<T>::recursivePostorder(BSTNode<T> *p) {
  if (p != nullptr) {
    recursivePostorder(p->left);
    recursivePostorder(p->right);
    std::cout << p->data << " ";
  }
}

// O(n)
template <class T> 
void BST<T>::postorder() {
  std::cout << "postorder():" << std::endl;
  recursivePostorder(root);
  std::cout << std::endl;
}

// O(n)
template <class T>
void BST<T>::auxiliarLevelByLevel(BSTNode<T> *p) {
  QueueLinkedList<BSTNode<T> *> fila;
  fila.enqueue(p);
  while (!fila.isEmpty()) {
    BSTNode<T> *q = fila.getFront();
    fila.dequeue();
    std::cout << q->data << " ";
    if (q->left != nullptr)
      fila.enqueue(q->left);
    if (q->right != nullptr)
      fila.enqueue(q->right);
  }
}

// O(n)
template <class T> 
void BST<T>::levelByLevel() {
  std::cout << "levelByLevel():" << std::endl;
  auxiliarLevelByLevel(root);
  std::cout << std::endl;
}

//----------------Tarea--------------------
// TO-DO

// void visit(int option);
template <class T>
void BST<T>::visit(int option){// Define la funcion visit en la clase BST y toma un entero option como parametro.
  switch (option){// Inicia un bloque de instrucciones condicionales en funcion del valor de option
    case 1:// Si option es igual a 1, se ejecuta la funcion inorder()
      inorder();
    case 2:// Si option es igual a 2, se ejecuta la funcion preorder()
      preorder();
      break;// Indica final del bloque
    case 3:// Si option es igual a 3, se ejecuta postorder()
      postorder();
      break;
    case 4://Si option es igual a 4, se ejecuta levelByLevel()
      levelByLevel();
      break;
    default:
      std::cout <<"Opcion invalida"<<std::endl;
      break;
  }
}
//Paszniuk, R. (s. f.). Arboles en C++ – Programación. https://www.programacion.com.py/escritorio/c/arboles-en-c


// int height();
template <class T>// Definicion de una plantilla que toma un tipo de dato T como parametro
int Height(BSTNode<T> *p) {// Definicion de la funcion Height que toma un puntero p
  if (p == nullptr) {// Comprueba si el puntero p es nulo, lo que indica que esta vacio
    return -1;// Si esta vacio, se devuelve -1
  } else {
    int leftHeight = Height(p->left);// Si el arbol no esta vacio se llama a la funcion leftHeight
    int rightHeight = Height(p->right);// Se llama la funcion height y almacena su valor en la variable rightHeight
    if (leftHeight > rightHeight) {// La funcion comprueba la altura del subarbol izaquierdo sea mayor
      return leftHeight + 1;// La funcion devuelve la altura del subarbol izquierdo mas 1
    } else {
      return rightHeight + 1;//Si el subarbol derecho es mayor que el izquierdo la funcion devuelve la altura del subarbol derecho mas 1
    }
  }
}


//Calcular la altura de un árbol binario: iterativo y recursivo. (s. f.). https://www.techiedelight.com/es/calculate-height-binary-tree-iterative-recursive/#:~:text=La%20altura%20o%20profundidad%20de,un%20solo%20nodo%20es%201.

template <class T>
int BST<T>::height() { //Devuelve la altura del arbol, llamando la funcion Height con el puntero raiz del arbol como argumento y devuelve la altura del arbol completo
  return Height(root);
}


//Encuentra ancestros de un nodo dado en un árbol binario. (s. f.). https://www.techiedelight.com/es/find-ancestors-of-given-node-binary-tree/


// void ancestors(T value);
template <class T>//Indica la funcion ancestros
void BST<T>::ancestors(T value) {//Se define la funcion para la clase BST con parametro T value
  BSTNode<T> *p = root;// Declara un puntero a un nodo del arbol llamado p
  std::cout << "Ancestros de " << value << ": ";
  while (p != nullptr && p->data != value) {// Bucle while que se ejecuta mientras el puntero no apunte a nulo
    std::cout << p->data << " ";
    p = (value < p->data) ? p->left : p->right;//Actualiza el puntero p para que apunte al hijo izquierdo o derecho del nodo actual mientras el valor especificado sea menor o mayor del valor almacenado
  }
  if (p == nullptr) {// Se comprueba si el puntero apunta a nulo
    std::cout << "El valor " << value << " no se encuentra en el árbol" << std::endl;
    return;
  }
  if (p == root) {// Comprueba si el puntero apunta a la raiz del arbol 
    std::cout << "El valor " << value << " es la raíz del árbol" << std::endl;
    return;
  }
  std::cout << p->data << std::endl;// Se imprime si no se cumple ninguna de las condiciones
}


//Cruz, M. (2018, 5 mayo). Árboles Binarios de Búsqueda en C++ | Recorrido por niveles (Amplitud). Blogueando sobre programacion. https://blog.martincruz.me/2012/11/arboles-binarios-de-busqueda-c.html


// int whatLevelAml(T value);
template <class T>
int BST<T>::whatLevelAml(T value){//Definicion de la funcion que toma un valor de tipo T y devuelve un valor entero
  BSTNode<T> *p = root;//Declara un puntero de tipo BSTNode<T> que apunta a la raiz del arbol
  int level = 0;//Declara una variable entera level inicializada en cero
  while (p != nullptr){//Se ejecuta mientras el puntero no sea nullptr
    if (p->data == value)
      return level;// Se compara el valor almacenado en el nodo al que apunta el puntero con el valor que se busca, si son iguales la funcion devuelve el nivel actual
    else{
      p = (value < p-> data) ? p->left : p->right;
      level++;
    }//Si el valor en el nodo actual es menor que el valor que se busca, se sigue el puntero a la izquierda, de lo contrario se sigue a la derecha y se incrementa el nivel actual en uno
  }
  return -1;
}


//ARBOLES BINARIOS DE BUSQUEDA. (s. f.). https://ccia.ugr.es/~jfv/ed1/c++/cdrom4/paginaWeb/abb.htm

#endif // _BST_H_
