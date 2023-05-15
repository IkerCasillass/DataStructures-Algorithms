#include <iostream>
#include "Registro.h"
class IP {
  private:
    int access_num;
    Registro access_info;

  public:
  IP();
  ~IP();
};


IP::IP(){
  access_num = 0;
}

IP::~IP(){}