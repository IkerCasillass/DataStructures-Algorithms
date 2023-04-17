#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include "AlgorithmSort.h"


// Constructor
template <class T> AlgorithmSort<T>::AlgorithmSort() {}

// Imprime en pantalla los elementos del vector
template <class T> void AlgorithmSort<T>::printVector(std::vector<T> A) {
  std::cout << "Los elementos del vector ordenado son: " << std::endl;
  for (int i = 0; i < (int)A.size(); i++) {
    std::cout << A[i] << " ";
  }
  std::cout << std::endl;
}

template <class T>
void AlgorithmSort<T>::insertionSort(std::vector<T> &A, int n,
                                     unsigned int &compara,
                                     unsigned int &swap) {
  compara = swap = 0;
  for (int i = 1; i < n; i++) {
    T key = A[i];
    int j = i - 1;
    // mover los elementos que son mayores a key hacia la derecha
    compara++;
    while (j >= 0 && A[j] > key) {
      A[j + 1] = A[j];
      swap++;
      j--;
      compara++;
    }
    A[j + 1] = key;
  }
}

template <class T>
int AlgorithmSort<T>::partition(std::vector<T> &A, int low, int high,
                                unsigned int &compara, unsigned int &swap) {

  T pivot = A[high];
  int i = low - 1;
  for (int j = low; j < high; j++) {
    compara++;
    if (A[j] < pivot) {
      i++;
      std::swap(A[i], A[j]);
      swap++;
    }
  }
  std::swap(A[i + 1], A[high]);
  swap++;
  return i + 1;
}

template <class T>
void AlgorithmSort<T>::quickSort(std::vector<T> &A, int low, int high,
                                 unsigned int &compara, unsigned int &swap) {
  if (low < high) {
    // encontrar la particion
    int pi = partition(A, low, high, compara, swap);
    // ordenar la mitad izquierda y derecha
    quickSort(A, low, pi - 1, compara, swap);
    quickSort(A, pi + 1, high, compara, swap);
  }
}

template <class T>
int AlgorithmSort<T>::binarySearch(std::vector<Registro> &vectorSorted, int key, int &compara) {
  int low = 0;
  int high = vectorSorted.size() - 1;
  int mid = 0;
  compara = 0;
  while (low <= high) {
    mid = low + (high - low) / 2;
    compara++;
    if (key == vectorSorted[mid].getFechaHora())
      return mid;
    else if (key < vectorSorted[mid].getFechaHora())
      high = mid - 1;
    else
      low = mid + 1;
  }
  return -1;
}


// No need to call this TemporaryFunction() function,
// it's just to avoid link error.
// void TemporaryFunction ()
// {
//     AlgorithmSort<int> TempObj;
// }