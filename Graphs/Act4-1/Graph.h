// Esta clase permite representar grafos dirigidos ponderados
#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include "LinkedList.h"
#include "QueueLinkedList.h"
#include "StackLinkedList.h"

class Graph {
  private:
    int numNodes;
    int numEdges;
    // Lista de adyacencia (vector de listas ligadas de pares nodo,peso)
    std::vector<LinkedList<std::pair<int, int>>> adjList;

    void split(std::string line, std::vector<int> & res);
    

  public:
    Graph();
    ~Graph();
    void loadDirWeightedGraph(std::istream & input);
    void print();
    void BFS(int v);
   
    // To-DO
    void DFS(int v);  


};


#endif // __GRAPH_H_