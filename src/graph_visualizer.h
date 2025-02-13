//
// Created by fddav on 11/02/2025.
//

#ifndef TSP_PROBLEM_GRAPH_VISUALIZER_H
#define TSP_PROBLEM_GRAPH_VISUALIZER_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <limits>
#include <fstream>
#include <sstream>
#include <cmath>
#include <thread>
#include <chrono>

void visualizeGraph(const std::vector<std::vector<int>>& graph, const std::vector<int>& path);

#endif //TSP_PROBLEM_GRAPH_VISUALIZER_H
