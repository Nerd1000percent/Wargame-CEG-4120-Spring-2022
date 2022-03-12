cmake_minimum_required(VERSION 3.19)
project (Wargame)

add_library (Wargame STATIC
	source/Wargame.cpp
	source/Map.cpp
	header/Map.h
	source/Terrain.cpp
	header/Terrain.h
	source/Tiles.cpp
	header/Tiles.h
	source/Unit.cpp
	header/Unit.h
	header/HyperArray.hpp
	header/UnitDatabase.h
	source/UnitDatabase.cpp
)

target_include_directories (Wargame 
  PUBLIC header
  PUBLIC ${CMAKE_SOURCE_DIR}/nlohmann/include
)

add_executable (WargameApp
  source/Wargame.cpp
)

target_link_libraries (WargameApp
  PUBLIC Wargame
)



