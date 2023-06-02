// Esta clase permite representar grafos dirigidos ponderados
#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <string>
#include "LinkedList.h"
#include "QueueLinkedList.h"

// https://stackoverflow.com/questions/18429021/why-is-infinity-0x3f3f3f3f
#define INF 0x3f3f3f3f

class Graph {
  private:
    int numNodes;
    int numEdges;
    // Lista de adyacencia (vector de listas ligadas de pares nodo,peso)
    std::vector<LinkedList<std::pair<std::string, int>>> adjList;

    void split(std::string line, std::vector<int> & res);
    // To-DO
    bool colorBipartiteGraph(int v, int col, std::vector<int> &color);

  public:
    Graph();
    Graph(std::ifstream &archivo); // Constructor con archivo
    ~Graph();
    void loadDirWeightedGraph(std::istream & input);
    void print();
    void BFS(int v);
    void dijkstraAlgorithm(int v);
    int getNumEdges();

    // To-DO
    bool isBipartite(int v, int col);  


};


#endif // __GRAPH_H_