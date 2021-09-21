cmake_minimum_required(VERSION 3.19)
project(AStar)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(
	AStar
	astar.cpp
	astar.h
	input.cpp
	input.h
	main.cpp
	structures.h
	)
