#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <fstream>

enum class CellType
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
    sf::Vector2f position;
    CellType type;
    bool visited; //for BFS
};


class LevelMap
{
    std::unordered_map<int, std::vector<int>> adjacencyList; //stores neighbours of connected nodes
    std::unordered_map<int, MapNode> nodeMap; //stores info about each node
    int totalNumOfNodes;
    MapNode playerNode;

public:
    LevelMap();
    void addNode(int id, MapNode node);
    void addEdge(int source, int destination);
    MapNode getNode(int id);
    std::vector<int> getNodeNeighbours(int id);
    int getTotalNumOfNodes();


    //map creation from file
    LevelMap createMapFromFile(const std::string& fileName);
    void createEdges(LevelMap& level, int width, int height);

    //draw map
    void drawLevel(sf::RenderWindow& window, LevelMap& level);



};

