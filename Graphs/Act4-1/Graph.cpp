
#include "Graph.h"

Graph::Graph() {
  adjList.clear();
}

Graph::~Graph() {
  adjList.clear();
}

void Graph::split(std::string line, std::vector<int> & res) {
    size_t strPos = line.find(" ");
    size_t lastPos = 0;
    while (strPos != std::string::npos) {
      res.push_back(stoi(line.substr(lastPos, strPos - lastPos)));
      lastPos = strPos + 1;
      strPos = line.find(" ", lastPos);
    }
    res.push_back(stoi(line.substr(lastPos, line.size() - lastPos)));
}

void Graph::loadDirWeightedGraph(std::istream & input) {
  std::string line;
  int i = 0;
  while (std::getline(input, line)) {
    if (i == 0) {
      i++;
      continue;
    }
    if (i == 1) {
      std::vector<int> result;
      split(line, result);
      numNodes = result[0];
      numEdges = result[2];
      // Reservar memoria para renglones de la lista de adyacencia
      // Nodos son uno basados (renglon 0 no sera usado)
      adjList.resize(numNodes + 1);
      // Declarar un lista vacia para cada renglon y se almacena en el vector
      for (int k = 1; k <= numNodes; k++) {
        LinkedList<std::pair<int, int>> tmpList;
        adjList[k] = tmpList;
      }
      i++;
      continue;
    }
    // Lectura de aristas del grafo
    std::vector<int> result;
    split(line, result);
    int nodoU = result[0];
    int nodoV = result[1];
    int weight = result[2];
    // grafo dirigido agregar aristas (u,v) unicamente 
    adjList[nodoU].addLast(std::make_pair(nodoV, weight));
    i++;
  }
}

void Graph::print() {
  std::cout << "numNode: " << numNodes << std::endl;
  std::cout << "numEdges: " << numEdges << std::endl;
  std::cout << "Adjacency List" << std::endl;
  for (int nodeU = 1; nodeU <= numNodes; nodeU++) {
    std::cout << "vertex " << nodeU << ": ";
    NodeLinkedList<std::pair<int, int>> *ptr = adjList[nodeU].getHead();
    while (ptr != nullptr) {
      std::pair<int, int> par = ptr->data;
      std::cout << "{" << par.first << "," << par.second << "} ";
      ptr = ptr->next;
    }
    std::cout << std::endl;
  }
}

// Complejidad O(V + E)
void Graph::BFS(int v) {
  // Declarar un set del STL de C++ (elementos unicos y ordenados)
  std::set<int> visited;
  // Crear un queue
  QueueLinkedList<int> queue;
  // Marca el vertice de partida v como visitado y lo mete en el queue
  visited.insert(v);
  queue.enqueue(v);
  std::cout << "Recorrido BFS " << std::endl;
  while (!queue.isEmpty()) {
    // Extraemos un vertice de el queue
    v = queue.getFront();
    queue.dequeue();
    std::cout << v << " ";
    // Obtener los vecinos del vertice v
    // Si estos no han sido visitados marcarlos como visitados
    // y los metemos a el queue
    NodeLinkedList<std::pair<int, int>> *ptr = adjList[v].getHead();
    while (ptr != nullptr) {
      std::pair<int, int> par = ptr->data;
      int u = par.first; // nodo u es vecino de v
      // Verificar si el vertice u (vecino de v) ya fue visitado
      bool isVisited = visited.find(u) != visited.end();
      if (!isVisited) { // no visitado
        visited.insert(u); // marcar como visitado
        queue.enqueue(u); // meter en el queue
      }
      ptr = ptr->next;
    }
  }
  std::cout << std::endl;
}


// Complejidad O(V + E)
void Graph::DFS(int v){
  // Declarar un set del STL de C++ (elementos unicos y ordenados)
  std::set<int> visited;
  // Crear stack
  StackLinkedList<int> stack;
  // Marca el vertice de partida v como visitado y lo mete en el stack
  visited.insert(v);
  stack.push(v);

  std::cout << "Recorrido DFS " << std::endl;
  while (!stack.isEmpty()) {
    // Extraemos un vertice de el stack
    v = stack.getTop();
    stack.pop();
    std::cout << v << " ";
    
    // Obtener los vecinos del vertice v
    // Si estos no han sido visitados marcarlos como visitados
    // y los metemos al stack
    NodeLinkedList<std::pair<int, int>> *ptr = adjList[v].getHead();
    while (ptr != nullptr) {
      std::pair<int, int> par = ptr->data;
      int u = par.first; // nodo u es vecino de v
      // Verificar si el vertice u (vecino de v) ya fue visitado
      bool isVisited = visited.find(u) != visited.end();
      if (!isVisited) { // no visitado
        visited.insert(u); // marcar como visitado
        stack.push(u); // meter en el stack
      }
      ptr = ptr->next;
    }
  }
}