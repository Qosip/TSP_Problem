#include <iostream>
#include "distances_reader.h"
#include "tsp_solver.h"
#include "graph_visualizer.h"
#include "clusters_reader.h"

int main() {

    std::string filename = "../data/distances.csv";
    int clusterCount = 24;

    std::vector<int> path;
    /*
    // Charger la matrice des distances
    auto matrix = readDistanceMatrix(filename, clusterCount);

    std::cout << "Matrice des distances :\n";
    //printDistanceMatrix(matrix);

    // Résolution du TSP avec heuristique gloutonne
    //std::cout << "Distance minimale (Nearest Neighbor) : " << tspNearestNeighbor(matrix, 0) << " km\n";

    // Numéro du cluster de départ et d'arrivé
    int start = 1;
    int destination = 19;

    // Calculer la distance minimale entre les deux points
    int minDistance = dijkstraClusters(matrix, start, destination, path);

    if (minDistance != -1) {
        std::cout << "La distance minimale entre le cluster " << start << " et le cluster " << destination << " est : " << minDistance << std::endl;
    } else {
        std::cout << "Il n'y a pas de chemin direct entre les deux points." << std::endl;
    }*/
    /*
    std::string filename2 = "../data/clusters.csv";
    int clusterCount2 = 24;

    // Charger la matrice des distances
    auto matrix2 = readClustersMatrix(filename2, clusterCount2);
    //printMatrix(matrix);
    int batiment1 = 215;
    int batiment2 = 20;
    int minDistance2 = dijkstraBuildings(matrix2, matrix, batiment1, batiment2, path);

    if (minDistance2 != -1) {
        std::cout << "La distance minimale entre le batiment " << batiment1 << " et le batiment " << batiment2 << " est : " << minDistance2 << std::endl;
    } else {
        std::cout << "Il n'y a pas de chemin direct entre les deux batiments." << std::endl;
    }*/

    auto graph = readDistanceMatrix(filename, clusterCount);
    int startCluster = 5;
    int endCluster = 18;
    int distance = dijkstraClusters(graph, startCluster, endCluster, path);

    if (distance != -1) {
        std::cout << "Distance minimale : " << distance << std::endl;
        visualizeGraph(graph, path);
    }
    return 0;
}
