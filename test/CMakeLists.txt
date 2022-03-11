cmake_minimum_required(VERSION 3.19)

add_executable(TestSuite
  TestSuite.cpp
  UnitTest.cpp
  MapTest.cpp
  HyperArrayTest.cpp
)
 
target_link_libraries (TestSuite
  PUBLIC Wargame gtest
)