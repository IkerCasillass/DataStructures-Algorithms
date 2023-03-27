#ifndef _ALGORITMO_SORT_H_
#define _ALGORITMO_SORT_H_

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

template <class T> class AlgorithmSort {
private:
  void merge(std::vector<T> &A, int low, int m, int high,
             unsigned int &compara);
  int partition(std::vector<T> &A, int low, int high, unsigned int &compara, unsigned int &swap);

public:
  AlgorithmSort();
  void printVector(std::vector<T> A);
  void swapSort(std::vector<T> &A, int n, unsigned int &compara,
                unsigned int &swap);

  void insertionSort(std::vector<T> &A, int n, unsigned int &compara,
                     unsigned int &swap);
  void mergeSort(std::vector<T> &A, int low, int high, unsigned int &compara);
  void quickSort(std::vector<T> &A, int low, int high, unsigned int &compara, unsigned int &swap);

  //search
  int binarySearch(const std::vector<int> &vectorSorted, int key, int &compara);

};

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
void AlgorithmSort<T>::swapSort(std::vector<T> &A, int n, unsigned int &compara,
                                unsigned int &swap) {
  compara = swap = 0;
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      compara++;
      if (A[i] > A[j]) {
        std::swap(A[i], A[j]);
        swap++;
      }
    }
  }
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
void AlgorithmSort<T>::mergeSort(std::vector<T> &A, int low, int high,
                                 unsigned int &compara) {
  if (low < high) {
    // encontrar el punto medio
    int m = low + (high - low) / 2;
    // Ordenar dos mitades
    mergeSort(A, low, m, compara);
    mergeSort(A, m + 1, high, compara);
    // Fusionar ambas mitades
    merge(A, low, m, high, compara);
  }
}

template <class T>
void AlgorithmSort<T>::merge(std::vector<T> &A, int low, int m, int high,
                             unsigned int &compara) {
  int i, j, k;
  int n1 = m - low + 1;
  int n2 = high - m;
  // crear los vectores auxiliares L y R
  std::vector<T> L(n1);
  std::vector<T> R(n2);
  for (i = 0; i < n1; i++) L[i] = A[low + i];
  for (j = 0; j < n2; j++) R[j] = A[m + 1 + j];
  // Fusionar los vectores auxiliares Ly R ordenados
  i = j = 0;
  k = low;
  while (i < n1 && j < n2) {
    compara++;
    if (L[i] <= R[j]) {
      A[k] = L[i];
      i++;
    } else {
      A[k] = R[j];
      j++;
    }
    k++;
  }
  // Copia los elementos restantes
  while (i < n1) {
    A[k] = L[i];
    i++; 
    k++;
  }
  while (j < n2) {
    A[k] = R[j];
    j++; 
    k++;
  }
}

template <class T>
int AlgorithmSort<T>::partition(std::vector<T> &A, int low, int high, unsigned int &compara, unsigned int &swap) {
  
  T pivot = A[high];
  int i = low - 1;
  for (int j = low; j<high; j++){
    compara++;
    if (A[j] < pivot ){
      i++;
      std::swap(A[i], A[j]);
      swap++;
    }
  }
  std::swap(A[i+1], A[high]);
  swap++;
  return i+1;
}

template <class T>
void AlgorithmSort<T>::quickSort(std::vector<T> &A, int low, int high, unsigned int &compara, unsigned int &swap) {
  if (low < high) {
    // encontrar la particion
    int pi = partition(A, low, high, compara, swap);
    // ordenar la mitad izquierda y derecha
    quickSort(A, low, pi-1, compara, swap);
    quickSort(A, pi+1, high, compara, swap);
  }
}

template <class T>
int AlgorithmSort<T>::binarySearch(const std::vector<int> &vectorSorted, int key, int &compara) {
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


#endif // _ALGORITMO_SORT_H_
