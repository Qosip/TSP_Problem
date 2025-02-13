#include "distances_reader.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::vector<std::vector<int>> readDistanceMatrix(const std::string& filename, int clusterCount) {
    std::vector<std::vector<int>> matrix(clusterCount, std::vector<int>(clusterCount, -1));  // Initialisation avec -1
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
            if (row > 0 && col > 0) {
                if (!cell.empty()) {
                    try {
                        matrix[row - 1][col - 1] = std::stoi(cell);
                    } catch (const std::invalid_argument& e) {
                        //std::cerr << "Erreur de conversion sur [" << row << "," << col << "] = '" << cell << "'" << std::endl;
                        matrix[row - 1][col - 1] = -1;  // Remplace les valeurs vides ou invalides par -1
                    }
                } else {
                    matrix[row - 1][col - 1] = -1;  // Remplace les cellules vides par -1
                }
            }
            col++;
        }
        row++;
    }

    // Compléter la matrice symétrique
    for (int i = 0; i < clusterCount; i++) {
        for (int j = 0; j < i; j++) {
            if (matrix[i][j] == -1 && matrix[j][i] != -1) {
                matrix[i][j] = matrix[j][i];
            } else if (matrix[j][i] == -1 && matrix[i][j] != -1) {
                matrix[j][i] = matrix[i][j];
            }
        }
    }

    return matrix;
}

void printMatrix(const std::vector<std::vector<int>>& matrix) {
    int clusterCount = matrix.size();

    std::cout << "\t";
    for (int i = 0; i < clusterCount; i++) {
        std::cout << "[" << i + 1 << "]" << "\t";
    }
    std::cout << std::endl;

    for (int i = 0; i < clusterCount; i++) {
        std::cout << "[" << i + 1 << "]" << "\t";
        for (int val : matrix[i]) {
            std::cout << (val == -1 ? "." : std::to_string(val)) << "\t";  // Affiche "." si la valeur est -1
        }
        std::cout << std::endl;
    }
}
