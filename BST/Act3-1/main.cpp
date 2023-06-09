/**
 * Ejemplo que implementa un Binary Search Tree (BST)
 *
 * Compilacion para debug:
 *    g++ -std=c++17 -g -o main *.cpp
 * Ejecucion con valgrind:
 *    nix-env -iA nixpkgs.valgrind
 *    valgrind --leak-check=full ./main
 *
 * Compilacion para ejecucion:
 *    g++ -std=c++17 -O3 -o main *.cpp
 * Ejecucion:
 *    ./main

 Equipo 2:
* Iker Casillas  | A01641047
* César Simental | A01641385
* Arturo Sánchez | A01275427
 **/

#include "BST.h"
#include <iostream>

int main() {
  std::cout << "Ejemplo de un Binary Search Tree (BST)" << std::endl;

  BST<int> myBST;
  std::cout << "Insert: 10, 20, 30, 15, 5, 115, 3, 3" << std::endl;
  myBST.insert(10);
  myBST.insert(20);
  myBST.insert(30);
  myBST.insert(15);
  myBST.insert(5);
  myBST.insert(115);
  myBST.insert(3);
  myBST.insert(3);

  /*
                    10
            5               20
        3             15          30
                                      115
  */
  myBST.print();
  std::cout << std::endl;
  std::cout << "Recorridos del BST " << std::endl;
  myBST.inorder();
  myBST.preorder();
  myBST.postorder();
  myBST.levelByLevel();
  
/*
  std::cout << "search(15) " << std::boolalpha << myBST.search(15) << std::endl;
  std::cout << "search(22) " << std::boolalpha << myBST.search(22) << std::endl;
  std::cout << "search(3) " << std::boolalpha << myBST.search(3) << std::endl;
  std::cout << std::endl;
    
  // Borrar nodo sin hijos
  std::cout << "deleteNode(115) - nodo sin hijo" << std::endl;
  myBST.deleteNode(115);
  myBST.print();
  std::cout << std::endl;

  // Borrar nodo con un hijo
  std::cout << "deleteNode(5) - nodo con un hijo" << std::endl;
  myBST.deleteNode(5);
  myBST.print();
  std::cout << std::endl;

  // Borrar nodo con dos hijos
  std::cout << "deleteNode(20) - nodo con dos hijos" << std::endl;
  myBST.deleteNode(20);
  myBST.print();
  std::cout << std::endl;
*/

  // void visit
  std::cout<<" \nVisit " << std::endl;
  myBST.visit(1);
  myBST.visit(2);
  myBST.visit(3);
  myBST.visit(4);
  myBST.print();
  std::cout<<std::endl;

  // Height
  std::cout<<" \nHeight " << std::endl;
  BST<int> myTree;
  int treeHeight = myTree.height();
  std::cout << "Altura del arbol: " << treeHeight << std::endl;

  //Ancestors
  std::cout<<" \nAncestors " << std::endl;
  myBST.ancestors(115);

  // whatLevelAml
  std::cout<<" \nWhat Level Aml: " << myBST.whatLevelAml(30) << std::endl;
  myBST.print();
  
  return 0;
}