// Equipo 2
// Arturo Sánchez Rodríguez | A01275427
// Iker Casillas            | A01641047
// Cesar Simental           | A01641385

 // * Compilacion para ejecucion:
 // *    g++ -std=c++17 -Wall -O3 -o main *.cpp

#include <iostream>
#include "StackLinkedList.h"
#include <string>

using namespace std;

void getInput(string& myString){
  cout << "Ingrese un string: " ;
  getline(cin, myString);// Lee el string ingresado por el usuario desde la entrada 
}//Función que permite leer una línea completa de entrada, y toma dos argumentos

string reverseString(string str){ //Declara una función llamada reverseString que toma una cadena de texto llamada str como argumento y devuelve una cadena de texto.
  StackLinkedList<char> stack; //Declara una pila (stack) utilizando una estructura de datos de lista enlazada (StackLinkedList) que almacenará caracteres (char).
  string result = ""; //Inicializa una cadena vacía llamada result que almacenará la cadena invertida por palabras.
  for(int i = 0; i < (int)str.length(); i++){ //Crea un bucle que se ejecuta una vez por cada carácter en la cadena de entrada str.
    if (str[i] == ' ') { //Si el carácter actual es un espacio en blanco, se ejecutará el siguiente bloque de código. Este bloque de código se utiliza para procesar una palabra completa.
      while (!stack.isEmpty()) {
        result += stack.getTop();
        stack.pop();
      } //Extrae cada carácter de la pila stack y los agrega a la variable result hasta que la pila esté vacía. Esto reversa la palabra actual.
      result += ' ';
    } else {
      stack.push(str[i]);
    } //Si el carácter actual no es un espacio en blanco, se agrega a la pila stack para que se pueda procesar más tarde.
  }
  while(!stack.isEmpty()){
    result += stack.getTop();
    stack.pop();
  } //se procesan los caracteres restantes en la pila stack, para manejar la ultima palabra de la cadeena 
  return result;
}


int main() {

  StackLinkedList<string> stack; //Se utiliza para almacenar la cadena de entrada y que luego se invertirá.
  string input;
  getInput(input); //Almacenar la cadena de entrada. 
  string reversed = reverseString(input); // Invertir la cadena de entrada almacenada en la variable input
  cout << "\nEl enunciado invertido es: " << reversed << endl;
  stack.push(input); //Se utiliza el objeto stack para insertar la cadena original almacenada en input en la pila
  cout << "\nElemento top del stack: " << stack.getTop() << endl; 
  cout << "\nNumero de elementos en el Stack: " << stack.getNumElements() << endl;
  ////Obtener el elemento en la parte superior de la pila y se imprime
  
  std::cout << "\nEjemplo de stack usando listas ligadas\n";
  
  StackLinkedList<int> myStack;
  // isEmpty()
  std::cout << "isEmpty(): " << std::boolalpha << myStack.isEmpty() << std::endl;
  std::cout << "numElements: " << myStack.getNumElements() << std::endl;
  std::cout << std::endl;
  
  // push
  std::cout << "Push de 5 elementos..." << std::endl;
  for (int i = 1; i < 6; i++) {
    std::cout << "push(" << i+10 << ")" << std::endl;
    myStack.push(i+10);
  }
  std::cout << "numElements: " << myStack.getNumElements() << std::endl;
  myStack.print();
  std::cout << std::endl;

  // pop excepcion
  std::cout << "Pop de 3 elementos..." << std::endl;
  for (int i = 1; i < 4; i++) {
    try {
      myStack.pop();
    }
    catch (std::out_of_range &e) {
      std::cout << "Error: " << e.what() << std::endl << "No se modifico la lista" << std::endl;
    }    
    catch (...) {
      std::cout << "Error desconocido, no se modifico el stack" << std::endl;
    }
  }
  std::cout << "numElements: " << myStack.getNumElements() << std::endl;
  myStack.print();
  std::cout << std::endl;
  
  // top excepcion
  try {
    std::cout << "getTop: " << myStack.getTop() << std::endl;
  }
  catch (std::out_of_range &e) {
    std::cout << "Error: " << e.what() << std::endl << "No se modifico el stack" << std::endl;
  }    
  catch (...) {
    std::cout << "Error desconocido, no se modifico el stack" << std::endl;
  }
  // isEmpty()
  std::cout << "isEmpty(): " << std::boolalpha << myStack.isEmpty() << std::endl;  
  return 0;
}