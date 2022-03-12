cmake_minimum_required(VERSION 3.19)
project (WargameWorkspace)

add_subdirectory (proj)
add_subdirectory (googletest)
add_subdirectory (test)

enable_testing()
add_test(NAME TestSuite COMMAND TestSuite)