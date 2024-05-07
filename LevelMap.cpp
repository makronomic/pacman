#include "LevelMap.h"
#include <iostream>
#include "assets.h"


const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;

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

            cell.id = nodeID;
            cell.position.x = currentColumn * TILE_WIDTH; 
            cell.position.y = currentRow * TILE_HEIGHT; 

            switch (c) 
            {
            case '#':
                cell.type = CellType::WALL;
                break;
            case '.':
                cell.type = CellType::FOOD;
                break;
            case 'P':
                cell.type = CellType::PLAYER;
                level.playerNode = cell;
                level.playerNode.id = nodeID;
                break;
            case ' ':
                cell.type = CellType::EMPTY;
                break;
            }
            level.addNode(nodeID, cell);
            nodeID++;
            currentColumn++;
        }

        currentRow++;
    }
    level.height = currentRow;
    level.width = currentColumn;
    //connect the edges
    createEdges(level);

    return level;
}

void LevelMap::createEdges(LevelMap& level) 
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



void LevelMap::drawLevel(sf::RenderWindow& window)
{
    // Draw other tiles
    for (int i = 0; i < getTotalNumOfNodes(); ++i)
    {
        MapNode node = getNode(i);

        sf::RectangleShape shape(sf::Vector2f(TILE_HEIGHT, TILE_HEIGHT));
        shape.setFillColor(sf::Color::Black);
        shape.setPosition(node.position);

        switch (node.type)
        {
        case CellType::WALL:
            shape.setFillColor(sf::Color::Blue);
            break;
        case CellType::FOOD:
            shape.setFillColor(sf::Color::Magenta);
            break;
        case CellType::EMPTY:
            shape.setFillColor(sf::Color::Black); //green for now to test
            break;
        }

        window.draw(shape); // Draw the tile
    }

    // Draw player sprite
    Assets::player.getSprite().setPosition(playerNode.position);
    window.draw(Assets::player.getSprite());
}




void LevelMap::updatePlayerPosition(const sf::Vector2f& newPosition) {
    playerNode.position = newPosition;
    playerNode.id = getPlayerNodeID(newPosition); // Update player node ID
    nodeMap[playerNode.id] = playerNode; // Update player node in the node map
}



int LevelMap::getPlayerNodeID(const sf::Vector2f& playerPosition) {
    // Calculate the node ID based on the player's position
    int column = static_cast<int>(playerPosition.x) / TILE_WIDTH;
    int row = static_cast<int>(playerPosition.y) / TILE_HEIGHT;
    int width = 25; //  map width in tiles, current 800(window width)/32(tile width) = 25

    return row * width + column;
}