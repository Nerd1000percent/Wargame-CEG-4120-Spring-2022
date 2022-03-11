cmake_minimum_required(VERSION 3.19)

add_executable(TestSuite
  TestSuite.cpp
  UnitTest.cpp
)

target_link_libraries(TestSuite gtest)
