cmake_minimum_required(VERSION 3.21)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)

add_executable(ft_containers stack.hpp vector.hpp utility.hpp reverse_iterator.hpp tree_iterator.hpp RBTree.hpp Map.hpp main.cpp)
