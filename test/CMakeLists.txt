cmake_minimum_required(VERSION 3.19)

add_executable(TestSuite
  TestSuite.cpp
  UnitTest.cpp
  ${CMAKE_SOURCE_DIR}/proj/source/Unit.cpp
)

 target_include_directories (TestSuite 
   PUBLIC ${CMAKE_SOURCE_DIR}/proj/header
 )

target_link_libraries(TestSuite gtest)
