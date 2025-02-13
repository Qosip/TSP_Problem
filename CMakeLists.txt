cmake_minimum_required(VERSION 3.25)
project(TSP_problem)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(TSP_problem src/main.cpp
        src/distances_reader.cpp
        src/distances_reader.h
        src/tsp_solver.cpp
        src/tsp_solver.h
        src/graph_visualizer.cpp
        src/graph_visualizer.h
        src/clusters_reader.cpp
        src/clusters_reader.h)


target_link_libraries(TSP_problem sfml-graphics sfml-window sfml-system)
