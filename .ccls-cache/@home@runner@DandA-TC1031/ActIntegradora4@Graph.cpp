#include "Graph.h"
#include <algorithm>
#include <fstream>
#include <map>
#include "Incidencia.h"
#include <iostream>
#include <sstream>


Graph::Graph() {
  adjList.clear();
}

Graph::Graph(std::ifstream &input) {
  std::string mes;
  std::string dia;
  std::string horas;
  std::string ip_origen;
  std::string ip_destino;
  std::string peso;
  std::string razon;
  std::string error1;
  std::string error2;
  std::string error3;
  std::string error4;
  std::string error5;
  std::string error6;

  
  std::vector<Incidencia> nodosOrigen;
  std::vector<Incidencia> incidencias;
  
  std::string line;
  std::map<int, std::string> ipInfo; //Map 
  
  int i = 0;

  while (std::getline(input, line)) {
    if (i == 0) {
      std::vector<int> result;
      split(line, result);
      numNodes = result[0];
      numEdges = result[1];

      // Reservar memoria para renglones de la lista de adyacencia
      // Nodos son uno basados (renglon 0 no sera usado)
      adjList.resize(numNodes + 1);
      // Declarar un lista vacia para cada renglon y se almacena en el vector
      for (int k = 1; k <= numNodes; k++) {
        LinkedList<std::pair<int, int>> tmpList;
        adjList[k] = tmpList;
      }
      nodosOrigen.resize(numNodes);
    }
      
    //Guardar nodos
    else if (i <= numNodes){
      // std::cout<< line << std::endl;
      Incidencia nodoOrigen;
      nodoOrigen.setIpValue(line, 0);
      //std::cout << nodoOrigen.getIpOrigenValue() << std::endl;
      nodosOrigen.push_back(nodoOrigen);
    }
      
    // Guardar incidencias
    else if(i <= numNodes + numEdges){
      incidencias.resize(numEdges);
      std::istringstream ss(line);
      // Obtenemos los datos que estan separados por espacios
      ss >> mes >> dia >> horas >> ip_origen >> ip_destino >> error1 >> error2 >> error3 >> error4 >>
          error5 >> error6;
      Incidencia IncidenciaTemp(mes,dia,horas,ip_origen,ip_destino, peso, razon);
      //std::cout<< IncidenciaTemp.getIpOrigen() <<std::endl;
      incidencias.push_back(IncidenciaTemp);
    }
    i++;
  }

  for(int j=0; j<100; j++){
    std::cout<<incidencias[j].getIpOrigen() << std::endl;
  }
}

    

Graph::~Graph() {
  adjList.clear();
}

int Graph::getNumEdges(){
  return numEdges;
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


// Complejidad O((|V | + |E|) log |V |)

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


// Grafo bipartita - Complejidad O(|V| + |E|)

bool Graph::colorBipartiteGraph(int v, int col, std::vector<int> &color){
   if (color[v] != -1 && color[v] != col) {
    return false;
  }
  color[v] = col;
  bool ans = true;

  NodeLinkedList<std::pair<int, int>> *ptr = adjList[v].getHead();
    
  while (ptr != nullptr) {
    std::pair<int, int> par = ptr->data;
    int nodeU = par.first;
    
    if (color[nodeU] == -1) {
      ans &= colorBipartiteGraph(nodeU, 1 - col, color);
    }

    else if (color[nodeU] != 1 - col) {
      return false;
    }

    ptr = ptr->next;
  }
  return ans;
}

bool Graph::isBipartite(int v, int col){
  std::vector<int> color(numNodes + 1, -1);  // Inicializar vector de colores
  return colorBipartiteGraph(v, col, color);
}