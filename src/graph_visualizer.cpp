
#include "graph_visualizer.h"
#include <filesystem>
// Fonction pour dessiner le graphe et le chemin avec SFML
void visualizeGraph(const std::vector<std::vector<int>>& graph, const std::vector<int>& path) {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Visualisation du graphe");

    // Position des nœuds
    std::vector<sf::Vector2f> positions;
    int n = graph.size();
    float radius = 300;
    for (int i = 0; i < n; ++i) {
        float angle = 2 * M_PI * i / n;
        float x = 600 + radius * cos(angle);
        float y = 400 + radius * sin(angle);
        positions.push_back(sf::Vector2f(x, y));
    }

    std::cout << "Répertoire de travail actuel : " << std::filesystem::current_path() << std::endl;

    sf::Font font;
    if (!font.loadFromFile("../fonts/Arial.ttf")) {
        std::cerr << "Erreur : Impossible de charger la police. Utilisation de la police par défaut." << std::endl;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(30, 30, 30)); // Fond sombre

        // Dessiner les arêtes
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (graph[i][j] != -1) {
                    sf::Vertex line[] = {
                            sf::Vertex(positions[i], sf::Color(200, 200, 200)),
                            sf::Vertex(positions[j], sf::Color(200, 200, 200))
                    };
                    window.draw(line, 2, sf::Lines);
                }
            }
        }

        // Dessiner les nœuds
        for (int i = 0; i < n; ++i) {
            sf::CircleShape node(20);
            node.setPosition(positions[i] - sf::Vector2f(10, 10));
            node.setFillColor(sf::Color::Blue);
            node.setOutlineThickness(2);
            node.setOutlineColor(sf::Color::White);
            window.draw(node);

            // Dessiner les numéros des clusters
            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(18);
            text.setFillColor(sf::Color::White);
            text.setString(std::to_string(i + 1));
            sf::FloatRect bounds = text.getLocalBounds();
            text.setOrigin(bounds.left , bounds.top );

            text.setPosition(positions[i]);
            window.draw(text);
        }

        // Dessiner le chemin avec animation
        for (size_t i = 1; i < path.size(); ++i) {
            sf::Vertex line[] = {
                    sf::Vertex(positions[path[i-1]], sf::Color::Red),
                    sf::Vertex(positions[path[i]], sf::Color::Red)
            };
            window.draw(line, 2, sf::Lines);
            window.display();
            std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Pause pour l'animation
        }

        window.display();
    }
}
