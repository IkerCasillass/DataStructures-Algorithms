/*
- Equipo 2
  - Iker Casilas | A01641047
  - César Simental | A01641385

 * Algoritmos de busqueda
 *
 * Compilación:
 *  g++ -std=c++17 -Wall *.cpp -o main
 *
 * Ejecución:
 *  ./main < TestCases/test01.txt
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::string;

/* En este caso, sequentialSearch() tiene complejidad de O(n/2). Esto debido a que
comparamos por par de caracteres, sabiendo que los caracteres repetidos siempre
están juntos. */
char sequentialSearch(const std::vector<char> &A, int &compara) {
  int i = 0;
  int j = 1;
  compara = 1;
  
  while (i < (int)A.size() /*&& A[i] != key*/) {
    while (j < (int)A.size()-1) {
      if (A[i] == A[j]) {
        //Siguiente par de caracteres
        i += 2;
        j += 2;
      }
      else {
        return A[i];
      }
      compara++;
    }
    i++;
  }
  
  if (i >= (int)A.size()){ 
    return A[i-1]; //Si el valor repetido es el último
  }
  else {
    return 0;
  }
}

/* binarySearch() será peor para estos casos de prueba debido a que tiene una complejidad de O(n).
Aunque sabemos que los caracteres repetidos son contiguos, la búsqueda binaria siempre parte del
valor medio, por lo que termina haciendo más comparaciones que la secuencial.*/
char binarySearch(const std::vector<char> &A, int &compara) {
  int low = 0, mid = 0, high = A.size() - 1, key = 0;
  compara = 0;

  while(key < (int)A.size()) {
    
    while (low <= high) {
      mid = low + (high - low) / 2;
      compara++;
      
      if (A[key] == A[mid]) {
        //Encontramos caracter único?
        if ((key == mid && A[key] != A[high]) || (key == mid and key == high)) { 
          return A[key]; //Regresamos caracter único
        }
        else {
          key += 2; //Saltamos a siguiente par de caracteres
          low = key;
          high = A.size() - 1;
        }
      }
      //key menor que mid
      else if (A[key] < A[mid]) {
        high = mid - 1;
      }
      //key mayor que mid
      else {
        low = mid + 1;
      }
   }
  }
  return 0;
}


int main(void) {
  int num = 0, comparaciones = 0;
  string cadena;

  // Leemos numero de strings de archivo de texto
  cin >> num;
  cout << "Number of strings: " << num << endl;
  cout << "\n";


  cout << "Secuencial:\t";
  cout << "\tBinaria:" << endl;
  
  // Lectura de los strings de archivo de texto
  for (int i = 0; i < num; i++) {
    cin >> cadena;
    //cout<<cadena << "\n"; //para imprimir la cadena que se analiza
    
    //Creando vector de caracteres
    std::vector<char> caracteres(cadena.begin(), cadena.end()); 
    
    cout << sequentialSearch(caracteres, comparaciones) << " ";
    cout << comparaciones << "\t\t\t\t";

    //Ordenar caracteres para la busqueda binaria
    std::sort(caracteres.begin(), caracteres.end()); 
    
    comparaciones = 0;
    cout << binarySearch(caracteres, comparaciones) << " ";
    cout << comparaciones << endl;
  }
  
  return 0;
}