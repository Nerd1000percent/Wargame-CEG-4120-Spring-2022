cmake_minimum_required(VERSION 3.19)
project (WargameWorkspace)

add_executable (Wargame
	source/Main.cpp
	source/Map.cpp
	header/Map.h
	source/Terrain.cpp
	header/Terrain.h
	source/Tiles.cpp
	header/Tiles.h
	source/Unit.cpp
	header/Unit.h
	)
  
 target_include_directories (Wargame 
   PUBLIC header
 )