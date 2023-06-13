// Esta clase permite representar grafos dirigidos ponderados
#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <string>
#include "LinkedList.h"
#include "Incidencia.h"
#include <map>


// https://stackoverflow.com/questions/18429021/why-is-infinity-0x3f3f3f3f
#define INF 0x3f3f3f3f

class Graph {
  private:
    int numNodes;
    int numEdges;

    // Lista de adyacencia (vector de listas ligadas con pair<Incidencia, peso>)
    std::vector<LinkedList<std::pair<Incidencia, int>>> adjList;

    std::map<int, std::string> nodosOrdenados;
    std::map<std::string, int> accessedIPs;

    
    

    void split(std::string line, std::vector<int> & res);

  public:
    Graph();
    Graph(std::ifstream &archivo, std::vector<Incidencia> &nodosOrigen); // Constructor con archivo
    ~Graph();
    void loadDirWeightedGraph(std::istream & input);
    void print();
    void BFS(int v);
    void dijkstraAlgorithm(int v);
    int getNumEdges();
    int getNumNodes();
    std::vector<LinkedList<std::pair<Incidencia, int>>> getAdjList();
    std::map<int, std::string> getNodosOrdenados();
    int getNodeOrder(const std::string &node);
    std::map<std::string, int> getAccessedIp();
    void countEntries(std::vector<Incidencia> &nodosOrigen);
    void countAccessedIPs();

};


#endif // __GRAPH_H_