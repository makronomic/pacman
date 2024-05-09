#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <fstream>

enum  CellType
{
    EMPTY,
    WALL,
    PLAYER,
    ENEMY,
    FOOD
};

//each node in the graph carries its type and position
class MapNode
{
public:
    int id;
    sf::Vector2f position;
    CellType type;
    bool visited = false; //for BFS
};


class LevelMap
{
    std::unordered_map<int, std::vector<int>> adjacencyList; //stores neighbours of connected nodes
    std::unordered_map<int, MapNode> nodeMap; //stores info about each node
    int totalNumOfNodes;
    MapNode playerNode;
    int height;
    int width;
    int foodCount;

public:
    LevelMap();

    void addNode(int id, MapNode node);
    void addEdge(int source, int destination);
    bool edgeExists(int source, int destination);
    MapNode getNode(int id);
    std::vector<int> getNodeNeighbours(int id);
    int getTotalNumOfNodes();


    //map creation from file
    LevelMap createMapFromFile(const std::string& fileName);
    void createEdges(LevelMap& level);

    //draw map
     void drawLevel(sf::RenderWindow& window);

    //tracking player
     void updatePlayerPosition();
     int getPlayerNodeID(const sf::Vector2f& playerPosition);  // Function to get the player node ID based on its position
     bool isValidMove(int& newID);


     //debug
     void printFoodCount();
};

