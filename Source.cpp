#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Graph.h"

class GraphGUI {
public:
    GraphGUI() : window(sf::VideoMode(800, 600), "Graph Input") {
        font.loadFromFile("G:/MIU DS and ALGO/arial_narrow_7.ttf");
        setupUI();
        graph = nullptr;
    }

    void run() {
        while (window.isOpen()) {
            handleEvents();
            window.clear();
            drawGraph(); // Draw the graph
            draw();
            window.display();
        }
    }

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text inputText;
    sf::Text outputText;
    sf::RectangleShape addEdgeButton; // Button for adding edges
    sf::Text addEdgeButtonText; // Text on the Add Edge button
    sf::RectangleShape createGraphButton; // Button for creating the graph
    sf::Text createGraphButtonText; // Text on the Create Graph button
    sf::RectangleShape calculateMSTButton; // Button for calculating MST
    sf::Text calculateMSTButtonText; // Text on the Calculate MST button
    std::string inputBuffer;
    Graph* graph;

    void setupUI() {
        inputText.setFont(font);
        inputText.setCharacterSize(24);
        inputText.setFillColor(sf::Color::White);
        inputText.setPosition(10, 10);

        outputText.setFont(font);
        outputText.setCharacterSize(24);
        outputText.setFillColor(sf::Color::White);
        outputText.setPosition(10, 100);

        // Define the "Add Edge" button
        addEdgeButton.setSize(sf::Vector2f(100, 50));
        addEdgeButton.setFillColor(sf::Color::Green);
        addEdgeButton.setPosition(10, 150); // Position the button
        addEdgeButtonText.setFont(font);
        addEdgeButtonText.setString("Add Edge");
        addEdgeButtonText.setCharacterSize(20);
        addEdgeButtonText.setFillColor(sf::Color::White);
        addEdgeButtonText.setPosition(15, 160); // Center the text in the button

        // Define the "Create Graph" button
        createGraphButton.setSize(sf::Vector2f(100, 50));
        createGraphButton.setFillColor(sf::Color::Blue);
        createGraphButton.setPosition(10, 210); // Position the button below the Add Edge button
        createGraphButtonText.setFont(font);
        createGraphButtonText.setString("Create Graph");
        createGraphButtonText.setCharacterSize(20);
        createGraphButtonText.setFillColor(sf::Color::White);
        createGraphButtonText.setPosition(15, 220); // Center the text in the button

        // Define the "Calculate MST" button
        calculateMSTButton.setSize(sf::Vector2f(100, 50));
        calculateMSTButton.setFillColor(sf::Color::Yellow);
        calculateMSTButton.setPosition(10, 270); // Position the button below the Create Graph button
        calculateMSTButtonText.setFont(font);
        calculateMSTButtonText.setString("Calculate MST");
        calculateMSTButtonText.setCharacterSize(20);
        calculateMSTButtonText.setFillColor(sf::Color::Black);
        calculateMSTButtonText.setPosition(5, 280); // Center the text in the button
    }

    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128 && event.text.unicode != 8) { // Ignore backspace
                    inputBuffer += static_cast<char>(event.text.unicode);
                }
                else if (event.text.unicode == 8 && !inputBuffer.empty()) { // Handle backspace
                    inputBuffer.pop_back();
                }
            }

            inputText.setString("Input: " + inputBuffer);

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (addEdgeButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        addEdge();
                    }
                    if (createGraphButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        createGraph();
                    }
                    if (calculateMSTButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        calculateMST();
                    }
                }
            }
        }
    }

    void createGraph() {
        std::istringstream iss(inputBuffer);
        int numVertices;
        if (iss >> numVertices && numVertices > 0) {
            if (graph) {
                delete graph;
            }
            graph = new Graph(numVertices); // Create a new graph with user-defined vertices
            outputText.setString("Graph created with " + std::to_string(numVertices) + " vertices.");
            inputBuffer.clear(); // Clear input buffer after processing
        }
        else {
            outputText.setString("Invalid number of vertices");
        }
        inputText.setString("Input: " + inputBuffer); // Update displayed input
    }

    void addEdge() {
        std::istringstream iss(inputBuffer);
        int src, dest, weight;
        if (iss >> src >> dest >> weight) {
            if (graph) {
                graph->addEdges(src, dest, weight);
                outputText.setString("Edge added: " + std::to_string(src) + " -- " + std::to_string(dest) + " == " + std::to_string(weight));
            }
            else {
                outputText.setString("Graph not created yet.");
            }
        }
        else {
            outputText.setString("Invalid input format. Use: <src> <dest> <weight>");
        }
        inputBuffer.clear(); // Clear input buffer after processing
    }

    void calculateMST() {
        if (graph) {
            graph->karuskalMST(); // Calculate MST
            outputText.setString("MST calculated. Check the graph for highlighted edges.");
        }
        else {
            outputText.setString("Graph not created yet.");
        }
    }

    void draw() {
        window.draw(inputText);
        window.draw(outputText);
        window.draw(addEdgeButton);
        window.draw(addEdgeButtonText);
        window.draw(createGraphButton);
        window.draw(createGraphButtonText);
        window.draw(calculateMSTButton);
        window.draw(calculateMSTButtonText);
    }

    void drawGraph() {
        if (graph) {
            // Define positions for nodes dynamically based on the number of vertices
            std::vector<sf::Vector2f> positions(graph->getNumVertices());
            float angleStep = 360.0f / graph->getNumVertices();
            float radius = 200.0f;

            for (int i = 0; i < graph->getNumVertices(); ++i) {
                float angle = i * angleStep * (3.14159f / 180.0f); // Convert to radians
                positions[i] = sf::Vector2f(400 + radius * cos(angle), 300 + radius * sin(angle)); // Circular layout
            }

            // Draw edges
            for (const auto& edge : graph->getEdges()) {
                sf::Color edgeColor = sf::Color::White; // Default color

                // Check if the edge is part of the MST
                const auto& mstEdges = graph->getMstEdges();
                if (std::find(mstEdges.begin(), mstEdges.end(), edge) != mstEdges.end()) {
                    edgeColor = sf::Color::Red; // Highlight MST edges
                }

                sf::Vertex line[] = {
                    sf::Vertex(positions[edge.source], edgeColor),
                    sf::Vertex(positions[edge.destination], edgeColor)
                };
                window.draw(line, 2, sf::Lines);

                // Create text for weight
                sf::Text weightText;
                weightText.setFont(font);
                weightText.setString(std::to_string(edge.weight));
                weightText.setCharacterSize(20);
                weightText.setFillColor(sf::Color::White);
                // Position the weight text above the edge
                weightText.setPosition(
                    (positions[edge.source].x + positions[edge.destination].x) / 2 - 10,
                    (positions[edge.source].y + positions[edge.destination].y) / 2 - 20
                );
                window.draw(weightText); // Draw the weight text
            }

            // Draw nodes
            for (size_t i = 0; i < positions.size(); i++) {
                sf::CircleShape node(20);
                node.setFillColor(sf::Color::Blue);
                node.setPosition(positions[i].x - 20, positions[i].y - 20); // Center the node
                window.draw(node);

                // Create text for node index
                sf::Text nodeText;
                nodeText.setFont(font);
                nodeText.setString(std::to_string(i));
                nodeText.setCharacterSize(20);
                nodeText.setFillColor(sf::Color::White);
                nodeText.setPosition(positions[i].x - 10, positions[i].y - 10); // Center the text
                window.draw(nodeText);
            }
        }
    }
};

int main() {
    GraphGUI gui;
    gui.run();
    return 0;
}