#include "Graph.h"
#include <algorithm>
#include <fstream>
#include <map>
#include "Incidencia.h"
#include <iostream>
#include <sstream>
#include <queue>
#include <vector>


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
  // std::map<int, std::string> ipInfo; //Map 
  
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
        LinkedList<std::pair<std::string, int>> tmpList;
        adjList[k] = tmpList;
      }
    }
      
    //Guardar nodos
    else if (i <= numNodes){
      Incidencia nodoOrigen;
      nodoOrigen.setIpValue(line, 0);
      nodosOrigen.push_back(nodoOrigen);
    }
      
    // Guardar incidencias
    else if(i <= numNodes + numEdges){
      std::istringstream ss(line);
      // Obtenemos los datos que estan separados por espacios
      ss >> mes >> dia >> horas >> ip_origen >> ip_destino >> peso >> error1 >> error2 >> error3 >> error4 >>
          error5 >> error6;
      
      //std::cout<< ip_origen << "----" << ip_destino <<std::endl;
      Incidencia IncidenciaTemp(mes,dia,horas,ip_origen,ip_destino, peso, razon);
      IncidenciaTemp.cambiarFormato(ip_origen, ip_destino, peso);
      incidencias.push_back(IncidenciaTemp);
    }
    i++;
  }

  // Ordenar nodos
  std::sort(nodosOrigen.begin(), nodosOrigen.end());

   // Crear mapa para almacenar nodos y su numero de orden
  std::map<int, std::string> nodosOrdenados;
  for (int j = 0; j < (int)nodosOrigen.size(); j++) {
    nodosOrdenados[j + 1] = nodosOrigen[j].getIpOrigen();
  }
  
  // Construir lista de adyacencia - -- - -- -- - 
  std::sort(incidencias.begin(), incidencias.end());
  
  int x=0;
  int numV = 0;
  std::string nombre = nodosOrigen[0].getIpOrigen();
  
  for(int i = 1; i <= numEdges; i++) {
    std::string nombre_temp = nombre;
    nombre = incidencias[i-1].getIpOrigen();
    
    if(nombre_temp != nombre){
      nodosOrigen[x].setNumVecinos(numV);
      x++;
      numV = 0;
    }
      
    int nodoU = x;
    
    std::string nodoV = incidencias[i-1].getIpDestino();
    int weight = incidencias[i-1].getPeso();

    // grafo dirigido agregar aristas (u,v) unicamente 
    adjList[nodoU].addLast(std::make_pair(nodoV, weight));
    numV++;
  }

  std::ofstream outputFile("grados_ips.txt");
  if(outputFile.is_open()){
    for(int i = 1; i <= numNodes; i++){
      outputFile <<"(" << nodosOrigen[i].getIpOrigen() << "," << nodosOrigen[i].getNumVecinos() << ")" << std::endl;
    }
    outputFile.close();
  }
  else{
    std::cout << "Error con el archivo." << std::endl;
  }

  std::cout << nodosOrigen[13356].getNumVecinos() << std::endl;
  std::cout << nodosOrigen[13357].getNumVecinos() << std::endl;
  std::cout << nodosOrigen[13358].getNumVecinos() << std::endl;
  std::cout << nodosOrigen[13359].getNumVecinos() << std::endl;
  std::cout << nodosOrigen[13369].getNumVecinos() << std::endl;
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
/*
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
        LinkedList<std::pair<std::string, int>> tmpList;
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
*/

void Graph::print() {
  std::cout << "numNode: " << numNodes << std::endl;
  std::cout << "numEdges: " << numEdges << std::endl;
  std::cout << "Adjacency List" << std::endl;
  for (int nodeU = 1; nodeU <= numNodes; nodeU++) {
    std::cout << "vertex " << nodeU << ": ";
    NodeLinkedList<std::pair<std::string, int>> *ptr = adjList[nodeU].getHead();
    while (ptr != nullptr ) {
      std::pair<std::string, int> par = ptr->data;
      std::cout << "{" << par.first << "," << par.second << "} ";
      ptr = ptr->next;
    }
    std::cout << std::endl;
  }
}


// void Graph::BFS(int v) {
//   // Declarar un set del STL de C++ (elementos unicos y ordenados)
//   std::set<int> visited;
//   // Crear un queue
//   QueueLinkedList<int> queue;
//   // Marca el vertice de partida v como visitado y lo mete en el queue
//   visited.insert(v);
//   queue.enqueue(v);
//   std::cout << "Recorrido BFS " << std::endl;
//   while (!queue.isEmpty()) {
//     // Extraemos un vertice de el queue
//     v = queue.getFront();
//     queue.dequeue();
//     std::cout << v << " ";
//     // Obtener los vecinos del vertice v
//     // Si estos no han sido visitados marcarlos como visitados
//     // y los metemos a el queue
//     NodeLinkedList<std::pair<int, int>> *ptr = adjList[v].getHead();
//     while (ptr != nullptr) {
//       std::pair<int, int> par = ptr->data;
//       int u = par.first; // nodo u es vecino de v
//       // Verificar si el vertice u (vecino de v) ya fue visitado
//       bool isVisited = visited.find(u) != visited.end();
//       if (!isVisited) { // no visitado
//         visited.insert(u); // marcar como visitado
//         queue.enqueue(u); // meter en el queue
//       }
//       ptr = ptr->next;
//     }
//   }
//   std::cout << std::endl;
// }


// Complejidad O((|V | + |E|) log |V |)

// void Graph::dijkstraAlgorithm(int v) {
//   // Crear una priority queue del STL de C++
//   // https://www.geeksforgeeks.org/implement-min-heap-using-stl/
//   std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> pq;
//   // vector de distancias con el resultado del algoritmo
//   std::vector<int> dist(numNodes+1, INF);
//   // Insertar el nodo de origen v en la priority queue -- pares (dist, vertice)
//   pq.push(std::make_pair(0, v)); // la distancia de v a v es cero
//   dist[v] = 0;
//   // Mientras el priority queue no este vacio
//   while (!pq.empty()) {
//     // Extraer un vertice de el priority queue
//     int nodeU = pq.top().second; // pares (dist, vertice)
//     pq.pop();
//     // Obtener los vecions del vertice nodeU
//     NodeLinkedList<std::pair<std::string, int>> *ptr = adjList[nodeU].getHead();
//     while (ptr != nullptr) {
//       std::pair<std::string, int> par = ptr->data;
//       std::string nodeV = par.first; // nodeV es vecino de nodeU
//       int peso = par.second; // peso de la arista (nodoU,nodeV)
//       if (dist[nodeV] > dist[nodeU]+peso) {
//         // Actualizar la distancia (mas corta) de nodeV
//         dist[nodeV] = dist[nodeU] + peso;
//         pq.push(std::make_pair(dist[nodeV], nodeV));
//       }
//       ptr = ptr->next;
//     }
//   }

// std::ofstream outputFile("distancia_bootmaster.txt");
//   if(outputFile.is_open()){
//     for(int i = 1; i <= numNodes; i++){
//       if(dist[i] != INF)
//         outputFile << i << " " << dist[i] << std::endl;
//       else
//         outputFile << i << " INF" << std::endl;
//     }
//     outputFile.close();
//   }
//   else{
//     std::cout << "Error con el archivo." << std::endl;
//   }


//   //if(outputFile)
  
//   // Imprimir las distancias mas cortas entre v y todos los nodos del grafo
//   std::cout << "Vertice\tDistancia desde v" << std::endl;
//   for (int i = 1; i <= numNodes; i++) {
//     if (dist[i] != INF)
//       std::cout << i << "\t" << dist[i] << std::endl;
//     else
//       std::cout << i << "\tINF" << std::endl;
//   }
// }

