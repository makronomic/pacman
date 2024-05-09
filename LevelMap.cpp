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

bool LevelMap::edgeExists(int source, int destination)
{
    auto sourceNode = adjacencyList.find(source);
    if (sourceNode != adjacencyList.end())
    {
        for (auto neighbor : sourceNode->second)
        {
            if (neighbor == destination)
            {
                return true;
            }
        }
    }
    return false;
}


void LevelMap::addEdge(int source, int destination)
{
    if (!edgeExists(source, destination))
    {
        //add neighbour node in adjacency list of each of the nodes
        adjacencyList[source].push_back(destination);
        adjacencyList[destination].push_back(source);
    }
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

    for (int y = 0; y < level.height; y++) 
    {
        for (int x = 0; x < level.width; x++) 
        {

            int currentId = y * level.width + x; //convert 2d index into 1d index for id

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
                if (x < level.width - 1)  //check if node has right neighbour
                {
                    int rightId = currentId + 1;
                    if (level.getNode(rightId).type != CellType::WALL) 
                    {
                        level.addEdge(currentId, rightId);

                    }
                }
                if (y > 0) //check if node has upper neighbour
                {
                    int upId = currentId - level.width;
                    if (level.getNode(upId).type != CellType::WALL)
                    {
                        level.addEdge(currentId, upId);

                    }
                }
                if (y < level.height - 1) //check if node has neighbour beneath it
                {
                    int downId = currentId + level.width;
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
    //std::cout << "\nPlayer Position: " << playerNode.position.x << " " << playerNode.position.y
    //    << "\nPlayer ID: " << playerNode.id << " NodeMap ID: " << nodeMap[playerNode.id].id;

}




void LevelMap::updatePlayerPosition(const sf::Vector2f& newPosition) 
{
    if (!isValidMove(newPosition))
    {
        return;
    }
    playerNode.position = newPosition;


    MapNode previousPlayerNode = playerNode;
    if (previousPlayerNode.type == CellType::FOOD) //lw el ableya food, a5le el cell de tb2a empty now
    {
        previousPlayerNode.type = CellType::WALL;
        nodeMap[previousPlayerNode.id] = previousPlayerNode;
    }


    playerNode.id = getPlayerNodeID(newPosition); // Update player node ID
    nodeMap[playerNode.id] = playerNode; // Update player node in the node map
}



int LevelMap::getPlayerNodeID(const sf::Vector2f& playerPosition) 
{
    // Calculate the node ID based on the player's position
    int column = static_cast<int>(playerPosition.x) / TILE_WIDTH;
    int row = static_cast<int>(playerPosition.y) / TILE_HEIGHT;

    return row * width + column;
}

bool LevelMap::isValidMove(const sf::Vector2f& newPosition)
{
    int newID = 0;

    // Get the node ID of the new position
    switch (Assets::player.state)
    {
    case 'u': newID = playerNode.id - height; break;
    case 'd': newID = playerNode.id + height; break;
    case 'l': newID = playerNode.id - 1; break;
    case 'r': newID = playerNode.id + 1; break;
   // default: newID = 0; break;
    }
    std::cout << "New Position ID: " << newID << std::endl;

    // Get neighbours of the current player node
    auto neighbours = getNodeNeighbours(playerNode.id);

    std::cout << "Current Player Node ID: " << playerNode.id << std::endl;
    std::cout << "Neighbours: ";
    for (auto neighbor : neighbours) {
        std::cout << neighbor << " ";
    }
    std::cout << std::endl;

    // Check if the new position is a valid edge of the current position
    return std::find(neighbours.begin(), neighbours.end(), newID) != neighbours.end();
}


void LevelMap::printAdjList()
{
    std::cout << "Printing adjacency list...\n";
    for (auto it = adjacencyList.begin(); it != adjacencyList.end(); it++) {
        std::cout << "Adjacency list of vertex " << it->first << ": ";
        for (auto neighbor : it->second) {
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;
    }
}
