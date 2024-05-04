#include "LevelMap.h"
#include <iostream>

LevelMap::LevelMap()
{
    totalNumOfNodes = 0;
}

void LevelMap::addNode(int id, MapNode node)
{
    nodeMap[id] = node;
    totalNumOfNodes++;
}

void LevelMap::addEdge(int source, int destination)
{
    //add neighbour node in adjacency list of each of the nodes
    adjacencyList[source].push_back(destination); 
    adjacencyList[destination].push_back(source);
}

MapNode LevelMap::getNode(int id)
{
    return nodeMap[id];
}

std::vector<int> LevelMap::getNodeNeighbours(int id)
{
    return adjacencyList[id];
}

int LevelMap::getTotalNumOfNodes()
{
    return totalNumOfNodes;
}

LevelMap LevelMap::createMapFromFile(const std::string& fileName)
{
    LevelMap level;

    std::ifstream file(fileName);
    std::string line;

    int nodeID = 0;
    int currentColumn = 0;
    int currentRow = 0;

    //create nodes based on each character from the file.
    while (std::getline(file,line))
    {
        currentColumn = 0;
        for (char c : line)
        {
            MapNode cell;

            cell.position.x = currentColumn * 20; // assuming each node has width 20
            cell.position.y = currentRow * 20; // assuming each node has height 20

            switch (c) 
            {
            case '#':
                cell.type = CellType::WALL;
                break;
            case '.':
                cell.type = CellType::FOOD;
                break;
            }
            level.addNode(nodeID, cell);
            nodeID++;
            currentColumn++;
        }

        currentRow++;
    }

    //connect the edges
    createEdges(level, currentColumn, currentRow);

    return level;
}

void LevelMap::createEdges(LevelMap& level, int width, int height) 
{
    for (int y = 0; y < height; ++y) 
    {
        for (int x = 0; x < width; ++x) 
        {
            int currentId = y * width + x; //convert 2d index into 1d index for id

            MapNode currentNode = level.getNode(currentId);

            if (currentNode.type != CellType::WALL)  //check if not wall, create edges to other nodes
            {
                // Connect to adjacent nodes (up, down, left, right)
                if (x > 0) //check if node has left neighbour, then if itsn't a wall add edge between the 2 cells
                {
                    int leftId = currentId - 1;
                    if (level.getNode(leftId).type != CellType::WALL) 
                    {
                        level.addEdge(currentId, leftId);
                    }
                }
                if (x < width - 1)  //check if node has right neighbour
                {
                    int rightId = currentId + 1;
                    if (level.getNode(rightId).type != CellType::WALL) 
                    {
                        level.addEdge(currentId, rightId);
                    }
                }
                if (y > 0) //check if node has upper neighbour
                {
                    int upId = currentId - width;
                    if (level.getNode(upId).type != CellType::WALL)
                    {
                        level.addEdge(currentId, upId);
                    }
                }
                if (y < height - 1) //check if node has neighbour beneath it
                {
                    int downId = currentId + width;
                    if (level.getNode(downId).type != CellType::WALL) 
                    {
                        level.addEdge(currentId, downId);
                    }
                }
            }
        }
    }
}


void LevelMap::drawLevel(sf::RenderWindow& window, LevelMap& level) 
{
    //std::cout << "here";

    for (int i = 0; i < level.getTotalNumOfNodes(); ++i) 
    {
        MapNode node = level.getNode(i);

        sf::RectangleShape shape(sf::Vector2f(20, 20));
        shape.setPosition(node.position);

        switch (node.type) 
        {
        case CellType::WALL:
            shape.setFillColor(sf::Color::Blue);
            break;
        case CellType::FOOD:
            shape.setFillColor(sf::Color::Magenta);
            break;
            // Add more cases as needed
        }
        window.draw(shape);
    }
}