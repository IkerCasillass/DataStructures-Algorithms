#ifndef _ALGORITMO_SORT_H_
#define _ALGORITMO_SORT_H_

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include "Registro.h"

class Registro; // forward declaration

template <class T> class AlgorithmSort {
private:
  int partition(std::vector<T> &A, int low, int high, unsigned int &compara,
                unsigned int &swap);

public:
  AlgorithmSort();
  void printVector(std::vector<T> A);

  void insertionSort(std::vector<T> &A, int n, unsigned int &compara,
                     unsigned int &swap);

  void quickSort(std::vector<T> &A, int low, int high, unsigned int &compara,
                 unsigned int &swap);

  int binarySearch(std::vector<Registro> &vectorSorted, int key, int &compara);

};

#endif // _ALGORITMO_SORT_H_
