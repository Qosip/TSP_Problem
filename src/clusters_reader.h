//
// Created by fddav on 12/02/2025.
//

#ifndef TSP_PROBLEM_CLUSTERS_READER_H
#define TSP_PROBLEM_CLUSTERS_READER_H

#include <vector>
#include <string>

using namespace std;

std::vector<std::vector<int>> readClustersMatrix(const std::string& filename, int clusterCount);

#endif //TSP_PROBLEM_CLUSTERS_READER_H
