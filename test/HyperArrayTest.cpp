#include <iostream>
#include <string>
#include <memory>
using namespace std;

#include "gtest/gtest.h"
#include "HyperArray.hpp"

namespace hyperarraytest
{
  class Data
  {
  public:
    Data() {}
    Data(string n) : name(n) {}
    string name;
  };

  TEST(HyperArraySuite, dataTest)
  {
    HyperArray<Data> hyperarray({ 2, 3, 5 });
    for (size_t i = 0; i < hyperarray.getDimension(0); i++)
      for (size_t j = 0; j < hyperarray.getDimension(1); j++)
        for (size_t k = 0; k < hyperarray.getDimension(2); k++)
          hyperarray.at({ i, j, k }) = "(" + to_string(i) + ", " + to_string(j) + ", " + to_string(k) + ")";

// don't print all this in the release build.  it is just for debugging this test case
#ifdef DEBUG
    for (size_t i = 0; i < hyperarray.getDimension(0); i++)
    {
      for (size_t j = 0; j < hyperarray.getDimension(1); j++)
      {
        for (size_t k = 0; k < hyperarray.getDimension(2); k++)
        {
          cout << hyperarray.at({ i, j, k }).name << " ";
        }
        cout << endl;
      }
      cout << endl;
    }
    cout << endl;
#endif

    for (size_t i = 0; i < hyperarray.getDimension(0); i++)
      for (size_t j = 0; j < hyperarray.getDimension(1); j++)
        for (size_t k = 0; k < hyperarray.getDimension(2); k++)
        {
          EXPECT_EQ(hyperarray.at({ i, j, k }).name, "(" + to_string(i) + ", " + to_string(j) + ", " + to_string(k) + ")");
        }
  }

  TEST(HyperArraySuite, todoTest)
  {
    EXPECT_TRUE(false) << "finish testing they hyperarray";
  }

}//namespace hyperarraytest