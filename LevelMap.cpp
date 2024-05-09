#include "LevelMap.h"
#include <iostream>
#include "assets.h"
#include <thread>


const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;

LevelMap::LevelMap()
{
    totalNumOfNodes = 0;
    foodCount = 0;
}

void LevelMap::getFoodCount()
{
    std::cout << foodCount;
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
                level.foodCount++;
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

    for (int i = 0; i < nodeMap.size(); ++i)
    {
        sf::RectangleShape shape(sf::Vector2f(TILE_HEIGHT, TILE_HEIGHT));
        shape.setFillColor(sf::Color::Transparent);
        shape.setPosition(nodeMap[i].position);

        sf::CircleShape food(3.0f); 
        sf::Vector2f foodPos;

        switch (nodeMap[i].type)
        {
        case CellType::WALL:
            shape.setOutlineColor(sf::Color::Color(0, 0, 148));
            shape.setOutlineThickness(2.0f);
            shape.setFillColor(sf::Color::Color(0, 0, 0));
            break;


        case CellType::FOOD:
            food.setFillColor(sf::Color::Yellow);
            foodPos = nodeMap[i].position + sf::Vector2f(TILE_HEIGHT / 2.0f, TILE_HEIGHT / 2.0f); //position circle in half of tile
            food.setOrigin(food.getRadius(), food.getRadius()); // set the origin to the center
            food.setPosition(foodPos);
            window.draw(food); 
            break;


        case CellType::EMPTY:
        default:
            shape.setFillColor(sf::Color::Black); //empty
            break;
        }

        window.draw(shape); // Draw the tile
    }

    // Draw player sprite
    Assets::player.getSprite().setPosition(playerNode.position);
    window.draw(Assets::player.getSprite());
}





void LevelMap::updatePlayerPosition()
{
    int newID;
    if (!isValidMove(newID))
    {
        return;
    }

    std::cout << newID << std::endl;



    // Update player position
    playerNode.position = nodeMap[newID].position;
    int prevID = playerNode.id;
    // Update player node ID
    playerNode.id = newID;

    // If the  cell contained food, update it to EMPTY
    if (nodeMap[newID].type == CellType::FOOD)
    {
        foodCount--;
        nodeMap[prevID].type = CellType::EMPTY;
    }
    // Update player node in the node map
    nodeMap[playerNode.id] = playerNode;

}




int LevelMap::getPlayerNodeID(const sf::Vector2f& playerPosition) 
{
    // Calculate the node ID based on the player's position
    int column = static_cast<int>(playerPosition.x) / TILE_WIDTH;
    int row = static_cast<int>(playerPosition.y) / TILE_HEIGHT;

    return row * width + column;
}

bool LevelMap::isValidMove(int& newID)
{

    // Get the possible node IDs of the new position based on the player state
    switch (Assets::player.state)
    {
    case 'u': newID = playerNode.id - width; break;  // Subtract width for moving up
    case 'd': newID = playerNode.id + width; break;  // Add width for moving down
    case 'l': newID = playerNode.id - 1; break;      // Subtract 1 for moving left
    case 'r': newID = playerNode.id + 1; break;      // Add 1 for moving right
    }

        // Check if the newID is out of bounds to avoid game crashing :)
    if (newID < 0 || newID >= nodeMap.size()) {
        return false;
    }

    if (nodeMap[newID].type == CellType::WALL)
    {
        return false;
    }

    // Get neighbours of the current player node
    auto neighbours = getNodeNeighbours(playerNode.id);

    
    // Check if the new position is a valid edge of the current position
    return std::find(neighbours.begin(), neighbours.end(), newID) != neighbours.end();
}

