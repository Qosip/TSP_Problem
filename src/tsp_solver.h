//
// Created by fddav on 11/02/2025.
//

#ifndef TSP_PROBLEM_TSP_SOLVER_H
#define TSP_PROBLEM_TSP_SOLVER_H


#include <vector>
#include <unordered_map>

int tspNearestNeighbor(const std::vector<std::vector<int>>& graph, int start);
int dijkstraClusters(const std::vector<std::vector<int>>& graph, int start, int destination);
int dijkstraBuildings(const std::vector<std::vector<int>>& graph, const std::vector<std::vector<int>>& graphClusters, int start, int destination);

#endif //TSP_PROBLEM_TSP_SOLVER_H
