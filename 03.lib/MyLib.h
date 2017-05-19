#ifndef MY_LIB
#define MY_LIB

#include "Arduino.h"

class MyLib{
  private:
    String _greeting;
  public:
    MyLib(String greeting);
    void sayHello(String name);
};

#endif