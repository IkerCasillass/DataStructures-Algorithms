/**
 * Equipo 2
 *
 * Compilacion para debug:
 *    g++ -std=c++17 -Wall -g -o main *.cpp
 * Compilacion para ejecucion:
 *    g++ -std=c++17 -O3 -o main *.cpp
 * Ejecucion:
 *    ./main
 **/

#include <iostream>
// using namespace std;    NO RECOMENDABLE USARLO
// https://www.geeksforgeeks.org/using-namespace-std-considered-bad-practice/

int fibonacciIterativo(int n){
  int i = 0, j = 1, res = 0;
  for (int k = 1; k < n; k++){
    res = i + j;
    i = j;
    j = res;
  }
  return res;
}

int fibonacciRecursivo(int n){
  int serie = 0;
    if(n < 2){
        serie = n;
    }
    else{
        serie = fibonacciRecursivo(n-1) + fibonacciRecursivo(n-2);
    }
    return serie;
  }


unsigned int inversionRecursiva(unsigned int n, double inicial){
  if (n == 0)
    return inicial;
  else
    inicial = inicial * 1.1875;
    return n + inversionRecursiva(n - 1, inicial);
}

unsigned int inversonIterativa(unsigned int n, unsigned int inicial) {
  while (n != 0) {
    inicial = inicial*1.1875;
    n= n-1;
  }
  return inicial;
}

unsigned int potenciaRecursiva(unsigned int x, unsigned int y, unsigned int t){
  if (y == 0)
    return t;
  else
    t = t * x;
    return potenciaRecursiva(x,y - 1, t);
}

unsigned int potenciaIterativa(unsigned int x, unsigned int y) {
  unsigned int total = 1;
  while (y != 0) {
    total = total*x;
    y = y-1;
  }
  return total;
}

int main() {
  std::cout << "Dame un numero positivo: " << std::endl;
  unsigned int num, inicial,x,y;
  std::cin >> num;
  std::cin>>inicial;
  std::cout << "Fibonacci iterativo: " <<fibonacciIterativo(num) <<std::endl;
  std::cout << "Fibonacci recursivo: " <<fibonacciRecursivo(num) <<std::endl;
  std::cout << "Inversion recursiva: " << inversionRecursiva(num,inicial) << std::endl;
  std::cout << "Inversion iterativa: " << inversionRecursiva(num,inicial) << std::endl;
  std::cout << "Dame x: " << std::endl;
  std::cin >>x;
  std::cout << "Dame y: " << std::endl;
  std::cin >>y;
  std::cout << "Potencia recursiva: " << potenciaRecursiva(x,y,1) << std::endl;
  std::cout << "Potencia recursiva: " << potenciaIterativa(x,y) << std::endl;
  return 0;
}