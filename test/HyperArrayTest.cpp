#include <iostream>
#include <string>
#include <memory>
using namespace std;

#include "gtest/gtest.h"
#include "HyperArray.hpp"
#include "nlohmann/json.hpp"

namespace hyperarraytest
{
  class Data
  {
  public:
    Data() {}
    Data(string n) : name(n) {}
    string name;
  };

  // serializers
  void to_json(nlohmann::json& j, const Data& u)
  {
    j["name"] = u.name;
  }

  void from_json(const nlohmann::json& j, Data& u)
  {
    j["name"].get_to(u.name);
  }

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

  TEST(HyperArraySuite, serializationTest)
  {
    HyperArray<Data> hyperarray({ 2, 3, 5 });
    for (size_t i = 0; i < hyperarray.getDimension(0); i++)
      for (size_t j = 0; j < hyperarray.getDimension(1); j++)
        for (size_t k = 0; k < hyperarray.getDimension(2); k++)
          hyperarray.at({ i, j, k }) = "(" + to_string(i) + ", " + to_string(j) + ", " + to_string(k) + ")";

    nlohmann::json j;
    j = hyperarray;
    string serial = j.dump();

    //cout << __FUNCTION__ << ":" << __LINE__ << endl << serial << endl;

    HyperArray<Data> copy({ 0 });
    j.clear();
    j = nlohmann::json::parse(serial);
    //cout << __FUNCTION__ << ":" << __LINE__ << endl << j.dump() << endl;

    j.get_to(copy);

    EXPECT_EQ(hyperarray.size(), copy.size());
    if (hyperarray.size() == copy.size())
      for (size_t i = 0; i < hyperarray.size(); i++)
      {
        EXPECT_EQ(hyperarray.at(i).name, copy.at(i).name);
      }

  }

  TEST(HyperArraySuite, todoTest)
  {
    //EXPECT_TRUE(false) << "finish testing they hyperarray";
  }

}//namespace hyperarraytest