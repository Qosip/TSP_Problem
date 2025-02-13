//
// Created by fddav on 11/02/2025.
//

#ifndef TSP_PROBLEM_DISTANCES_READER_H
#define TSP_PROBLEM_DISTANCES_READER_H

#include <vector>
#include <string>

std::vector<std::vector<int>> readDistanceMatrix(const std::string& filename, int clusterCount);
void printMatrix(const std::vector<std::vector<int>>& matrix);


#endif //TSP_PROBLEM_DISTANCES_READER_H
