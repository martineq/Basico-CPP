// test.cc

#include <iostream>
#include "../src/helloworld.h"
#include "gtest/gtest.h"

using namespace std;

TEST(HolaTest, SiempreBien) {
  HelloWorld hw;
  hw.EjemploRocksDB();
  hw.EjemploMongoose();
  hw.EjemploJson();

  EXPECT_EQ(1,1);
}

int main(int argc, char **argv) {
/*
  HelloWorld hw;
  hw.EjemploRocksDB();
  hw.EjemploMongoose();
  hw.EjemploJson();

  // Test siempre positivo (Sólo de prueba)
  return 0;
*/

  // Testing con GTest
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

