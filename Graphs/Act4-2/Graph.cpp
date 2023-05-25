
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

void Graph::dijkstraAlgorithm(int v) {
  // Crear una priority queue del STL de C++
  // https://www.geeksforgeeks.org/implement-min-heap-using-stl/
  std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> pq;
  // vector de distancias con el resultado del algoritmo
  std::vector<int> dist(numNodes+1, INF);
  // Insertar el nodo de origen v en la priority queue -- pares (dist, vertice)
  pq.push(std::make_pair(0, v)); // la distancia de v a v es cero
  dist[v] = 0;
  // Mientras el priority queue no este vacio
  while (!pq.empty()) {
    // Extraer un vertice de el priority queue
    int nodeU = pq.top().second; // pares (dist, vertice)
    pq.pop();
    // Obtener los vecions del vertice nodeU
    NodeLinkedList<std::pair<int, int>> *ptr = adjList[nodeU].getHead();
    while (ptr != nullptr) {
      std::pair<int, int> par = ptr->data;
      int nodeV = par.first; // nodeV es vecino de nodeU
      int peso = par.second; // peso de la arista (nodoU,nodeV)
      if (dist[nodeV] > dist[nodeU]+peso) {
        // Actualizar la distancia (mas corta) de nodeV
        dist[nodeV] = dist[nodeU] + peso;
        pq.push(std::make_pair(dist[nodeV], nodeV));
      }
      ptr = ptr->next;
    }
  }
  // Imprimir las distancias mas cortas entre v y todos los nodos del grafo
  std::cout << "Vertice\tDistancia desde v" << std::endl;
  for (int i = 1; i <= numNodes; i++) {
    if (dist[i] != INF)
      std::cout << i << "\t" << dist[i] << std::endl;
    else
      std::cout << i << "\tINF" << std::endl;
  }
}