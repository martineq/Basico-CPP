#include    <iostream>
#include    "helloworld.h"

using namespace std;
 
int main(int argc, char** argv) {

  HelloWorld hw;
  hw.EjemploRocksDB();
  hw.EjemploMongoose();
  hw.EjemploJson();

	return 0; // touch
}

