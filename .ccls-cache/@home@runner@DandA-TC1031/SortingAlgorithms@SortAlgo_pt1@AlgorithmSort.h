#ifndef _ALGORITMO_SORT_H_
#define _ALGORITMO_SORT_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

template <class T>
class AlgorithmSort {

  public:
    AlgorithmSort();
    void randomShuffle(std::vector<T> &A);
    void printVector(std::vector<T> A);
    void swapSort(std::vector<T> &A, int n, unsigned int &compara, unsigned int &swap);
    void selectionSort(std::vector<T> &A, int n, unsigned int &compara, unsigned int &swap);
    void bubbleSort(std::vector<T> &A, int n, unsigned int &compara, unsigned int &swap);
    
};

template<class T>
AlgorithmSort<T>::AlgorithmSort() {
  
}

// Mezcla los elementos del vector en forma aleatoria
template<class T>
void AlgorithmSort<T>::randomShuffle(std::vector<T> &A) {
  std::shuffle(A.begin(), A.end(), std::random_device{});
}

// Imprime en pantalla los elementos del vector
template<class T>
void AlgorithmSort<T>::printVector(std::vector<T> A) {
    std::cout << "Los elementos del vector ordenado son: " << std::endl;
    for(int i = 0; i < (int)A.size(); i++) {
      std::cout << A[i] << " ";
    }
    std::cout << std::endl;
}

template <class T>
void AlgorithmSort<T>::swapSort(std::vector<T> &A, int n, unsigned int &compara, unsigned int &swap) {
  compara = swap = 0;
  for(int i = 0; i < n-1; i++) {
    for(int j = i + 1; j < n; j++) {
      compara++;
      if (A[i] > A[j]) {
        std::swap(A[i], A[j]);
        swap++;
      }
    }
  }
}

template <class T>
void AlgorithmSort<T>::selectionSort(std::vector<T> &A, int n, unsigned int &compara, unsigned int &swap) {
  compara = swap = 0;
  for(int i = 0; i < n-1; i++) {
    int minIndex = i;
    for (int j= i + 1; j < n; j++){
      compara++;
      if (A[j]<A[minIndex]) minIndex=j;
    }
    std::swap(A[i], A[minIndex]);
    swap++;
  }
}

template <class T>
void AlgorithmSort<T>::bubbleSort(std::vector<T> &A, int n, unsigned int &compara, unsigned int &swap){
  compara = swap = 0;
  for(int i = 0; i < n-1; i++){
    for (int j = 0; j < n-i-1; j++){
      compara++;
      if(A[j] > A[j+1]){
      std::swap(A[j], A[j+1]);
      swap++;
      }
    }
  }
}


#endif // _ALGORITMO_SORT_H_
