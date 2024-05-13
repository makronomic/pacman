#include "assets.h"
#include "Enemies_Movement.h"
#include "LevelMap.h"
#include <iostream>
#include <thread>
#include <queue>
#include <stack>

const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;

LevelMap::LevelMap() {
	totalNumOfNodes = 0;
	foodCount = 0;
	score = 0;
	height = 0;
	width = 0;
	gameOver = false;
}

int LevelMap::getFoodCount() {
	return foodCount;
}

bool LevelMap::isGameOver() {
	return gameOver;
}



void LevelMap::addNode(int id, MapNode node) {
	nodeMap[id] = node;
	totalNumOfNodes++;
}

bool LevelMap::edgeExists(int source, int destination) {
	auto sourceNode = adjacencyList.find(source);
	if (sourceNode != adjacencyList.end()) {
		for (auto neighbor : sourceNode->second) {
			if (neighbor == destination) {
				return true;
			}
		}
	}
	return false;
}


void LevelMap::addEdge(int source, int destination) {
	if (!edgeExists(source, destination)) {
		//add neighbour node in adjacency list of each of the nodes
		adjacencyList[source].push_back(destination);
		adjacencyList[destination].push_back(source);
	}
}

MapNode LevelMap::getNode(int id) {
	return nodeMap[id];
}

std::vector<int> LevelMap::getNodeNeighbours(int id) {
	return adjacencyList[id];
}

int LevelMap::getTotalNumOfNodes() {
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
	while (std::getline(file, line))
	{
		currentColumn = 0;
		MapNode cell;

		for (char c : line) {

			cell.id = nodeID;
			cell.position.x = currentColumn * TILE_WIDTH;
			cell.position.y = currentRow * TILE_HEIGHT;

			switch (c) 
			{
			case '#':
				cell.type = CellType::WALL;
				break;
			case 'E':
				cell.type = CellType::ENEMY;
				level.enemyNode.push_back(cell);
				level.enemyNode.back().id = nodeID;
				break;
			case '.':
				cell.type = CellType::FOOD;
				level.foodCount++;
				break;
			case 'P':
				cell.type = CellType::PLAYER;
				level.playerNode = cell;
				level.playerNode.id = nodeID;
				level.initialPlayerPos = cell.position;
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




void LevelMap::createEdges(LevelMap& level) {
	for (int y = 0; y < level.height; y++) {
		for (int x = 0; x < level.width; x++) {

			int currentId = y * level.width + x; //convert 2d index into 1d index for id

			MapNode currentNode = level.getNode(currentId);

			if (currentNode.type != CellType::WALL)  //check if not wall, create edges to other nodes
			{
				// Connect to adjacent nodes (up, down, left, right)
				if (x > 0) //check if node has left neighbour, then if itsn't a wall add edge between the 2 cells
				{
					int leftId = currentId - 1;
					if (level.getNode(leftId).type != CellType::WALL) {
						level.addEdge(currentId, leftId);
					}
				}
				if (x < level.width - 1)  //check if node has right neighbour
				{
					int rightId = currentId + 1;
					if (level.getNode(rightId).type != CellType::WALL) {
						level.addEdge(currentId, rightId);

					}
				}
				if (y > 0) //check if node has upper neighbour
				{
					int upId = currentId - level.width;
					if (level.getNode(upId).type != CellType::WALL) {
						level.addEdge(currentId, upId);

					}
				}
				if (y < level.height - 1) //check if node has neighbour beneath it
				{
					int downId = currentId + level.width;
					if (level.getNode(downId).type != CellType::WALL) {
						level.addEdge(currentId, downId);

					}
				}
			}
		}
	}
}

void LevelMap::updateEmptyNodes() 
{
	for (int i = 0; i < nodeMap.size(); i++) 
	{

		bool isEmpty = true; // Flag to track if the node should be empty

		// Check if the node is an enemy
		for (int j = 0; j < 4; j++) 
		{

			if (nodeMap[i].id == enemyNode[j].id && nodeMap[i].type == ENEMY) 
			{
				isEmpty = false;
				
			}

		}

		// If the node isnt an enemy and it meets other conditions set it to empty
		if (isEmpty && nodeMap[i].type != WALL && nodeMap[i].type != FOOD && nodeMap[i].id != playerNode.id) 
		{
			nodeMap[i].type = EMPTY;
		}
	}
}


void LevelMap::drawLevel() {
	updateEmptyNodes();

	int count = 0;
	int playercount = 0;

	for (int i = 0; i < nodeMap.size(); ++i) {

		sf::RectangleShape shape(sf::Vector2f(TILE_HEIGHT, TILE_HEIGHT));
		shape.setFillColor(sf::Color::Transparent);
		shape.setPosition(nodeMap[i].position);

		sf::CircleShape food(3.0f);
		sf::Vector2f foodPos;

		if (nodeMap[i].type == ENEMY) count++;
		if (nodeMap[i].type == PLAYER) playercount++;

		switch (nodeMap[i].type) {

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
			Assets::window.draw(food);
			break;


		case CellType::EMPTY:
		default:
			shape.setFillColor(sf::Color::Transparent); //empty
			break;
		}
		Assets::window.draw(shape); // Draw the tile

	}

	// Draw player and enemy sprite
	Assets::player.getSprite().setPosition(playerNode.position);

	// enemy indices start from 1 to 4
	for (int i = 0; i < 4; i++) {
		Assets::objects[i]->getSprite().setPosition(enemyNode[i].position);
		Assets::window.draw(Assets::objects[i]->getSprite());
		//std::cout << "Enemy Node " << i << " ID: " << enemyNode[i].id << std::endl;
	}

	Assets::window.draw(Assets::player.getSprite());

	//std::cout << count <<  " " <<  playercount << std::endl;

	// Draw score
	sf::Font font;
	if (!font.loadFromFile("resources/fonts/Crackman_Front.OTF")) {
		std::cout << "ERROR LOADING FONT!";
	}
	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setString("Score: " + std::to_string(score));
	scoreText.setCharacterSize(35);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(0, -10);
	Assets::window.draw(scoreText);
}

void LevelMap::updatePlayerPosition() {
	int newID;
	int prevID = playerNode.id;

	if (!isValidMove(newID, prevID)) {
		return;
	}


	// Update player position
	playerNode.position = nodeMap[newID].position;
	// Update player node ID
	playerNode.id = newID;
	// If the  cell contained food, update it to EMPTY
	if (nodeMap[newID].type == CellType::FOOD) {
		foodCount--;
		score += 10;
		nodeMap[newID].type = CellType::EMPTY;
		if (foodCount == 0) {
			gameOver = true;
		}
	} else if (nodeMap[newID].type == CellType::ENEMY) {
		nodeMap[playerNode.id].position = initialPlayerPos;
		playerNode.position = initialPlayerPos;
		gameOver = true;
		std::cout << "is Game Over? " << gameOver << std::endl;
	} else {
		nodeMap[newID].type == CellType::EMPTY;
	}

	nodeMap[playerNode.id] = playerNode;

}

void LevelMap::updateEnemyPosition(int enemyIndex) {
	static MapNode* previousNode = nullptr;

	int newID;
	int prevID = enemyNode[enemyIndex].id;


	// ghosts start from 1 not 0 because of pacman
	if (!isValidMove(newID, prevID, enemyIndex)) {
		//std::cout << "Invalid move";
		return;
	}

	if (previousNode != nullptr)
	{

		previousNode->type = CellType::FOOD;
		nodeMap[previousNode->id] = *previousNode; //update node map 
		previousNode = nullptr; // Reset the pointer

	}


	// Check if the new node has food
	if (nodeMap[newID].type == CellType::FOOD) 
	{
		previousNode = &nodeMap[newID]; // Store the node with food
	}
	else if (nodeMap[newID].type == CellType::PLAYER)
	{
		nodeMap[playerNode.id].position = initialPlayerPos;
		playerNode.position = initialPlayerPos;
		gameOver = true;
		std::cout << "is Game Over ? " << gameOver << std::endl;
	}


	// Update enemy position
	enemyNode[enemyIndex].position = nodeMap[newID].position;
	// Update enemy node ID
	enemyNode[enemyIndex].id = newID;



	// Update player node in the node map
	nodeMap[enemyNode[enemyIndex].id] = enemyNode[enemyIndex];

}




bool LevelMap::isValidMove(int& newID, int prevID, int enemyIndex) {
	char entityState = 'i';
	if (nodeMap[prevID].type == CellType::PLAYER) {
		entityState = Assets::player.state;  //get player state
	} else {
		if(enemyIndex != -1)
		entityState = Assets::objects[enemyIndex]->state;        //get enemy state
	}

	// Get the possible node IDs of the new position based on the entity's state
	switch (entityState) {
	case 'u': newID = nodeMap[prevID].id - width; break;  // Subtract width for moving up
	case 'd': newID = nodeMap[prevID].id + width; break;  // Add width for moving down
	case 'l': newID = nodeMap[prevID].id - 1; break;      // Subtract 1 for moving left
	case 'r': newID = nodeMap[prevID].id + 1; break;      // Add 1 for moving right
	}


	// Check if the newID is out of bounds
	if (newID < 0 || newID >= nodeMap.size()) {
		return false;
	}

	// Check if the new position is a wall
	if (nodeMap[newID].type == CellType::WALL) {
		return false;
	}

	// Get neighbours of the current entity node
	auto neighbours = getNodeNeighbours(nodeMap[prevID].id);

	// Check if the new position is a valid edge of the current position
	return std::find(neighbours.begin(), neighbours.end(), newID) != neighbours.end();
}

std::vector<char> LevelMap::BFS(int enemyIndex) {
	std::queue<int> q;
	std::vector<bool> visited(totalNumOfNodes, false);
	std::vector<char> path(totalNumOfNodes, ' ');

	// Start BFS from enemy's current position
	q.push(enemyNode[enemyIndex].id);
	visited[enemyNode[enemyIndex].id] = true;

	while (!q.empty()) {
		int currentNodeID = q.front();
		q.pop();

		// Get neighbours of the current node
		auto neighbours = getNodeNeighbours(currentNodeID);

		// Check all the neighbours
		for (int neighbourID : neighbours) {
			if (!visited[neighbourID] && nodeMap[neighbourID].type != CellType::WALL) {
				visited[neighbourID] = true;
				nodeMap[neighbourID].parent = currentNodeID;

				// Calculate the direction to move
				int diff = neighbourID - currentNodeID;
				if (diff == -width) {
					path[neighbourID] = 'u'; // Move up
				}
				else if (diff == width) {
					path[neighbourID] = 'd'; // Move down
				}
				else if (diff == -1) {
					path[neighbourID] = 'l'; // Move left
				}
				else if (diff == 1) {
					path[neighbourID] = 'r'; // Move right
				}

				q.push(neighbourID);
			}
		}
	}

	// Construct the path from player to enemy
	std::stack<char> reversePath;
	int currentID = playerNode.id;
	while (currentID != enemyNode[enemyIndex].id && currentID != -1) {
		reversePath.push(path[currentID]);
		currentID = nodeMap[currentID].parent;
	}

	// Convert stack to vector
	std::vector<char> finalPath;
	while (!reversePath.empty()) {
		finalPath.push_back(reversePath.top());
		reversePath.pop();
	}

	return finalPath;
}
