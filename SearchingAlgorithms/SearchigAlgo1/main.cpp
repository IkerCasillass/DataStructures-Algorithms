/*
 * Algoritmos de busqueda
 *
 * Compilación:
 *  g++ -std=c++17 -Wall *.cpp -o main
 *
 * Ejecución:
 *  ./main < TestCases/test01.txt
 */

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

int sequentialSearch(const std::vector<int> &A, int key, int &compara) {
  int i = 0;
  compara = 1;
  while (i < (int)A.size() && A[i] != key) {
    i++;
    compara++;
  }
  if (i < (int)A.size())
    return i;
  else
    return -1;
}

int sequentialSearchSortedVector(const std::vector<int> &A, int key, int &compara) {
  compara = 0;
  for (int i = 0; i < (int)A.size(); i++) {
    compara++;
    if (key <= A[i]) {
      if (key == A[i])
        return i;
      else
        return -1;
    }
  }
  return -1;
}

int binarySearch(const std::vector<int> &vectorSorted, int key, int &compara) {
  int low = 0;
  int high = vectorSorted.size() - 1;
  int mid = 0;
  compara = 0;
  while (low <= high) {
    mid = low + (high - low) / 2;
    compara++;
    if (key == vectorSorted[mid])
      return mid;
    else if (key < vectorSorted[mid])
      high = mid - 1;
    else
      low = mid + 1;
  }
  return -1;
}

int binarySearchRecursive(const std::vector<int> &vectorSorted, int low, int high, int key, int &compara) {
  int m;
  if (low > high)
    return -1;
  compara++;
  m = low + (high - low) / 2;
  if (key == vectorSorted[m])
    return m;
  else if (key < vectorSorted[m])
    return binarySearchRecursive(vectorSorted, low, m - 1, key, compara);
  else
    return binarySearchRecursive(vectorSorted, m + 1, high, key, compara);
}

int main(void) {
  int i, tmp, size, key, flag;
  // Inicio conteo de tiempo de ejecución
  cin >> size;
  cout << "Size: " << size << endl;
  cin >> key;
  cout << "Key: " << key << endl;
  cin >> flag;
  cout << "Print flag: " << flag << endl;
  // Declaración del vector
  std::vector<int> myVector;
  // Lectura de los elementos del arreglo
  for (i = 0; i < size; i++) {
    cin >> tmp;
    myVector.push_back(tmp);
  }
  if (flag) {
    cout << "Los elementos del arreglo son: " << endl;
    for (i = 0; i < size; i++) {
      cout << myVector[i] << " ";
    }
    cout << endl;
  }
  int comparaciones = 0;
  cout << endl;
  cout << "Busqueda secuencial" << endl;
  cout << "El Key buscado esta en el indice: "
       << sequentialSearch(myVector, key, comparaciones) << endl;
  cout << "Numero de comparaciones: " << comparaciones << endl;
  cout << endl;

  cout << "Busqueda secuencial en vector ordenado" << endl;
  cout << "El Key buscado esta en el indice: "
       << sequentialSearchSortedVector(myVector, key, comparaciones) << endl;
  cout << "Numero de comparaciones: " << comparaciones << endl;
  cout << endl;

  cout << "Busqueda binaria en vector ordenado" << endl;
  cout << "El Key buscado esta en el indice: "
       << binarySearch(myVector, key, comparaciones) << endl;
  cout << "Numero de comparaciones: " << comparaciones << endl;
  cout << endl;
  

  return 0;
}