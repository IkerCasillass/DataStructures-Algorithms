#include "Graph.h"
#include <algorithm>
#include <fstream>
#include <map>
#include "Incidencia.h"
#include <iostream>
#include <sstream>
#include <queue>
#include <vector>
#include <tuple>



Graph::Graph() {
  adjList.clear();
}

Graph::Graph(std::ifstream &input, std::vector<Incidencia> &nodosOrigen) {
   std::string mes, dia, horas,ip_origen, ip_destino, peso, razon, error1, error2, error3,
    error4, error5, error6;  
  
  std::vector<Incidencia> incidencias;
  std::string line;
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

        LinkedList<std::pair<Incidencia, int>> tmpList; // con Ipinfo
        
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

      //Incidencia temporal
      Incidencia IncidenciaTemp(mes,dia,horas,ip_origen,ip_destino, peso, razon);
      IncidenciaTemp.cambiarFormato(ip_origen, ip_destino, peso);
      //Agregar a vector incidencias
      incidencias.push_back(IncidenciaTemp);
    }
    i++;
  }

  // Ordenar nodos
  std::sort(nodosOrigen.begin(), nodosOrigen.end());

  for (int j = 0; j < (int)nodosOrigen.size(); j++) {
    nodosOrdenados[j + 1] = nodosOrigen[j].getIpOrigen();
  }


  //Imprimir valores de map
//   for (const auto& pair : nodosOrdenados) {
//   std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
// }
  
  // Construir lista de adyacencia - -- - -- -- - 
  std::sort(incidencias.begin(), incidencias.end());
  
  int x=0;
  int numV = 0;
  std::string nombre = nodosOrigen[0].getIpOrigen();

  // Rellenar lista
  for(int i = 1; i <= numEdges; i++) {
    std::string nombre_temp = nombre;
    nombre = incidencias[i-1].getIpOrigen();
    // std::string accesado = incidencias[i-1].getIpDestino();
    Incidencia accesado;
    accesado.setIpOrigen(incidencias[i-1].getIpDestino());
    accesado.cambiarFormato(accesado.getIpOrigen(), "000.000.000.000", "0");


    // Nodo sin salidas
    if(nodosOrigen[x].getIpOrigen() != nombre_temp){
      numV = 0;
      nodosOrigen[x].setNumVecinos(numV);
      x++;
      
    }
    // Cambio de nodo cuando si hay salidas
    else if(nombre_temp != nombre){
      if(x >0 && nodosOrigen[x-1].getNumVecinos() == 0){
        numV++;
      }
      Incidencia primeraIp;
      primeraIp.setIpOrigen(incidencias[i-(numV+1)].getIpDestino());
      primeraIp.cambiarFormato(primeraIp.getIpOrigen(), "000.000.000.000", "0");
      
      nodosOrigen[x].salidas.push_back(primeraIp);
      nodosOrigen[x].setNumVecinos(numV);
      numV = 0;
      x++;
    }

    int nodoU = x;
    Incidencia nodoV = incidencias[i-1]; // Guardar incidencia
    int weight = incidencias[i-1].getPeso();

    // grafo dirigido agregar aristas (u,v) unicamente 
    // Insertar incidencia(ipinfo) y peso
    adjList[nodoU].addLast(std::make_pair(nodoV, weight));
    

    //nombre_temp == nombre
    if(nombre_temp == nombre){
      nodosOrigen[x].salidas.push_back(accesado);
    }
    
    numV++;

    // Búsqueda inversa en el mapa nodosOrdenados
    // for (const auto& pair : nodosOrdenados) {
    //   if (pair.second == accesado) {
    //     nodo = pair.first;
    //     break;
    //   }
    // }
    
  }

  // ----- archivo con grados de salida -----
  std::ofstream outputFile("incidencias_ordenadas.txt");
  if(outputFile.is_open()){
    for(int i = 0; i < 105282; i++){
      outputFile <<"(" << incidencias[i].getIpOrigen() << " ->> " << incidencias[i].getIpDestino() << ")" << std::endl;
    }
    outputFile.close();
    std::cout<< "> Archivo con incidencias construido" <<std::endl;
  }
  else{
    std::cout << "Error con el archivo." << std::endl;
  }
  this->countAccessedIPs();
}

Graph::~Graph() {
  adjList.clear();
}

int Graph::getNumEdges(){
  return numEdges;
}

int Graph::getNumNodes(){
  return numNodes;
}
std::map<std::string, int> Graph::getAccessedIp(){
  return accessedIPs;
}

std::map<int, std::string> Graph::getNodosOrdenados(){
  return nodosOrdenados;
}


std::vector<LinkedList<std::pair<Incidencia, int>>>Graph::getAdjList(){
  return adjList;
}

// Obtener orden de nodo
int Graph::getNodeOrder(const std::string &node){
  for(const auto &map : nodosOrdenados) {
    if(map.second == node) {
      return map.first;
    }
  }
  return -1; // Si el nodo no se encuentra en el map
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

void Graph::countAccessedIPs() {

  // Recorrer la lista de adyacencia y contar las conexiones salientes para cada IP
  for (int nodeU = 1; nodeU <= numNodes; nodeU++) {
    NodeLinkedList<std::pair<Incidencia, int>>* ptr = adjList[nodeU].getHead();
    while (ptr != nullptr) {
      std::string ipDestino = ptr->data.first.getIpDestino();

      // Incrementar el conteo de la IP accedida en el mapa
      accessedIPs[ipDestino]++;

      ptr = ptr->next;
    }
  }
  // // Imprimir el resultado del conteo
  // std::cout << "IPs accedidas: " << std::endl;
  // for (const auto& pair : accessedIPs) {
  //   std::cout << pair.first << ": " << pair.second << std::endl;
  // }
}

void Graph::print() {
  std::cout << "numNode: " << numNodes << std::endl;
  std::cout << "numEdges: " << numEdges << std::endl;
  std::cout << "Adjacency List" << std::endl;
  for (int nodeU = 0; nodeU <= numNodes; nodeU++) {
    std::cout << "vertex " << nodeU << ": ";
    NodeLinkedList<std::pair<Incidencia, int>> *ptr = adjList[nodeU].getHead();
    while (ptr != nullptr) {
      std::pair<Incidencia, int> par = ptr->data;
      std::cout << "{" << par.first.getIpOrigen() << "," << par.second << "} ";
      ptr = ptr->next;
    }
    std::cout << std::endl;
  }
}


