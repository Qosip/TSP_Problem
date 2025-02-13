//
// Created by fddav on 12/02/2025.
//

#include "clusters_reader.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::vector<std::vector<int>> readClustersMatrix(const std::string& filename, int clusterCount){
    std::vector<std::vector<int>> matrix(clusterCount, std::vector<int>(clusterCount, -1));  // Initialisation avec -1
    /*for (int  i = 0; i <clusterCount; i++){
        cout<<"\n";
        for (int j = 0; j <clusterCount; j++){
            cout<<matrix[i][j]<<", ";
        }
    }*/

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir " << filename << std::endl;
        perror("Détails de l'erreur");
        exit(EXIT_FAILURE);
    }
    std::string line;
    int row = 0;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        int col = 0;

        while (std::getline(ss, cell, ';')) {
            if (row>=0 && col > 0) {
                if (!cell.empty()) {
                    try {
                        matrix[row][col - 1] = std::stoi(cell);
                    } catch (const std::invalid_argument& e) {
                        //std::cerr << "Erreur de conversion sur [" << row << "," << col << "] = '" << cell << "'" << std::endl;
                        matrix[row][col - 1] = -1;  // Remplace les valeurs vides ou invalides par -1
                    }
                } else {
                    matrix[row][col - 1] = -1;  // Remplace les cellules vides par -1
                }
            }
            col++;
        }
        row++;
    }

    return matrix;
}
