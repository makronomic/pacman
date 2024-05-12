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
    bool has_food = false;
    bool visited = false; //for BFS
};


class LevelMap
{
    std::unordered_map<int, std::vector<int>> adjacencyList; //stores neighbours of connected nodes
    std::unordered_map<int, MapNode> nodeMap; //stores info about each node
    int totalNumOfNodes;
    MapNode playerNode;
    sf::Vector2f initialPlayerPos;
    MapNode enemyNode;

    int height;
    int width;
    
    int score;

public:
    LevelMap();
    bool gameOver;
    int foodCount;
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
     void drawLevel();


    //tracking player
     void updatePlayerPosition();
     bool isValidMove(int& newID, int prevID);

     void updateEnemyPosition();

     void updateEmptyNodes(); //to avoid empty nodes having type player or enemy when they are moved on

     //losing case
     bool isGameOver();

     //winning case (food count == 0)
     int getFoodCount();
    
};

