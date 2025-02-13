#include "tsp_solver.h"
#include <algorithm>
#include <limits>
#include <stack>
#include <iostream>
#include <queue>
#include <fstream>

// Heuristique gloutonne (Nearest Neighbor) avec Backtracking
int tspNearestNeighbor(const std::vector<std::vector<int>>& graph, int start) {
    int n = graph.size();
    std::vector<bool> visited(n, false);
    std::stack<int> path;  // Pile pour suivre les clusters visitées
    int totalCost = 0, current = start;
    visited[current] = true;
    path.push(current);

    // Table de suivi des clusters visitées
    std::vector<std::string> clusterStatus(n, "✘");
    clusterStatus[current] = "✓";

    while (!path.empty()) {
        bool foundNext = false;
        int minDist = std::numeric_limits<int>::max();
        int next = -1;

        // Recherche du cluster le plus proche non visité
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && graph[current][j] != -1 && graph[current][j] < minDist) {
                minDist = graph[current][j];
                next = j;
                foundNext = true;
            }
        }

        if (foundNext) {
            visited[next] = true;
            totalCost += minDist;
            current = next;
            path.push(current);
            clusterStatus[current] = "✓";  // Marquer le cluster comme visité
        } else {
            // Si aucun cluster n'est trouvé, on revient au cluster précédent
            path.pop();
            if (path.empty()) {
                break;  // Si la pile est vide, on a terminé le parcours
            }
            current = path.top();
        }
    }

    // Retourner au point de départ
    if (graph[current][start] != -1) {
        totalCost += graph[current][start];
    } else {
        std::cerr << "Erreur : Impossible de retourner au cluster de départ." << std::endl;
        return -1;  // Retourner -1 si le retour au cluster de départ est impossible
    }

    // Afficher le tableau des clusters et leur statut
    std::cout << "Tableau des clusters visitées :" << std::endl;
    std::cout << "\t\t\t  |\t";
    for (int i = 1; i < n+1; ++i) {
        std::cout << i << " | "<< "\t";
    }
    std::cout << std::endl;
    std::cout << "Statut :\t\t  |\t";
    for (int i = 0; i < n; ++i) {
        std::cout << clusterStatus[i] << " | " << "\t";
    }
    std::cout << std::endl;

    return totalCost;
}

// Algorithme de Dijkstra pour la distance minimale entre deux clusters avec log du chemin
int dijkstraClusters(const std::vector<std::vector<int>>& graph, int start, int destination, std::vector<int>& path) {
    start -= 1;  // Ajustement pour indexation 1-based à 0-based
    destination -= 1;

    std::cout << "Calcul de la distance minimale entre le cluster " << (start + 1) << " et le cluster " << (destination + 1) << "..." << std::endl;

    // Vérification si le départ et l'arrivée sont le même cluster
    if (start == destination) {
        int internalDistance = graph[start][start];
        if (internalDistance == -1) {
            std::cerr << "Il n'y a pas de distance définie à l'intérieur du cluster." << std::endl;
            return -1;
        }
        std::cout << "Chemin suivi : " << (start + 1) << std::endl;
        path.push_back(start);
        return internalDistance;
    }

    int n = graph.size();
    std::vector<int> dist(n, std::numeric_limits<int>::max());
    std::vector<int> prev(n, -1);
    std::vector<bool> visited(n, false);
    dist[start] = 0;

    using Pair = std::pair<int, int>;
    std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (int v = 0; v < n; ++v) {
            if (graph[u][v] != -1 && !visited[v]) {
                int newDist = dist[u] + graph[u][v];
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    prev[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
    }

    if (dist[destination] == std::numeric_limits<int>::max()) {
        std::cerr << "Il n'y a pas de chemin vers le cluster de destination." << std::endl;
        return -1;
    }

    std::stack<int> tempPath;
    for (int v = destination; v != -1; v = prev[v]) {
        tempPath.push(v);
    }

    path.clear();
    while (!tempPath.empty()) {
        path.push_back(tempPath.top());
        tempPath.pop();
    }

    return dist[destination];
}


int dijkstraBuildings(const std::vector<std::vector<int>>& graph, const std::vector<std::vector<int>>& graphClusters, int start, int destination, std::vector<int>& path) {
    int clusterA = -1, clusterB = -1;

    // Identifier les clusters des bâtiments de départ et de destination
    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph[i].size(); j++) {
            if (graph[i][j] == start) {
                clusterA = i + 1;  // Ajustement pour indexation 1-based
            } else if (graph[i][j] == destination) {
                clusterB = i + 1;  // Ajustement pour indexation 1-based
            }
            // Si les deux clusters sont trouvés, on peut arrêter la recherche
            if (clusterA != -1 && clusterB != -1) {
                break;
            }
        }
    }

    // Vérification si les clusters ont été trouvés
    if (clusterA == -1) {
        std::cerr << "Le bâtiment de départ n'a pas été trouvé dans la matrice." << std::endl;
        return -1;
    }
    if (clusterB == -1) {
        std::cerr << "Le bâtiment de destination n'a pas été trouvé dans la matrice." << std::endl;
        return -1;
    }

    // Appel de la fonction dijkstraClusters pour trouver la distance entre les clusters
    int distance = dijkstraClusters(graphClusters, clusterA, clusterB, path);

    return distance;
}
