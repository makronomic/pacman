#include "Enemies_Movement.h"
#include <iostream>
#include <thread>




//// Convert character state to Direction enum
//Direction convertStateToDirection(char state) {
//    switch (state) {
//    case 'u': return Up;
//    case 'd': return Down;
//    case 'l': return Left;
//    case 'r': return Right;
//    default: return None;
//    }
//}

//// Convert Direction enum to character state
//char convertDirectionToState(Direction dir) {
//    switch (dir) {
//    case Up: return 'u';
//    case Down: return 'd';
//    case Left: return 'l';
//    case Right: return 'r';
//    default: return 'i';  // 'i' for idle or invalid
//    }
//}

//// Get the opposite direction to avoid backtracking
//Direction getOppositeDirection(Direction dir) {
//    switch (dir) {
//    case Up: return Down;
//    case Down: return Up;
//    case Left: return Right;
//    case Right: return Left;
//    default: return None;
//    }
//}

//// Function to simulate and check ghost movement without collisions
//bool canMoveToPosition(Object& ghost, int newX, int newY) {
//    Object simulatedGhost = ghost;
//    simulatedGhost.setPos(newX, newY);
//    simulatedGhost.getSprite().setPosition(static_cast<float>(newX), static_cast<float>(newY));
//
//    for (const auto& other : Assets::objects) {
//        if (&ghost != other && ghost.getSprite().getGlobalBounds().intersects(other->getSprite().getGlobalBounds())) {
//            return false; // Collision detected
//        }
//    }
//    return true; // No collision detected, move is valid
//}

//// Choose a new direction that does not lead to a collision
//Direction chooseNewDirection(Object& ghost, Direction currentDirection) {
//    std::vector<Direction> possibleDirections = { Up, Down, Left, Right };
//    possibleDirections.erase(std::remove(possibleDirections.begin(), possibleDirections.end(), getOppositeDirection(currentDirection)), possibleDirections.end());
//
//    std::vector<Direction> validDirections;
//    for (auto dir : possibleDirections) {
//        int newX = ghost.getPos().x, newY = ghost.getPos().y;
//        switch (dir) {
//        case Down:  newY += 2; break;
//        case Left:  newX -= 2; break;
//        case Up:    newY -= 2; break;
//        case Right: newX += 2; break;
//        }
//        if (canMoveToPosition(ghost, newX, newY)) {
//            validDirections.push_back(dir);
//        }
//    }
//
//    if (!validDirections.empty()) {
//        int randIndex = rand() % validDirections.size();
//        return validDirections[randIndex];
//    }
//
//    return currentDirection; // If no valid move, continue in the current direction
//}


void moveRandomly(Object* o) {
	int randDir = Random::get(0, 3); // Random number between 0 and 3
	switch (randDir) {
	case 0: o->state = 'u'; break; // Up
	case 1: o->state = 'd'; break; // Down
	case 2: o->state = 'l'; break; // Left
	case 3: o->state = 'r'; break; // Right
	}


	Assets::level.updateEnemyPosition(o->getId());
}

#include <chrono>

void moveBFS(Object* o, float deltaTime)
{
	// Calculate the BFS path
	std::vector<char> path = Assets::level.BFS(o->getId());

	// If the path is not empty
	if (!path.empty())
	{
		// Move the object based on the next state in the path
		char nextState = path.back();
		o->state = nextState;

		// Remove the last element from the path vector
		path.pop_back();
	}
	// Update the object's position
	Assets::level.updateEnemyPosition(o->getId());
}




void updateGhost(int difficulty) {

	static sf::Clock clock;
	static float elapsedTime = 0.0f;
	float dt = clock.restart().asSeconds(); //deltatime
	elapsedTime += dt;

	while (elapsedTime >= 0.1f) {
		switch (difficulty) {
		case 1:
			for (auto enemy : Assets::objects)
			{
				moveRandomly(enemy);
			}
			elapsedTime -= 0.16f;
			break;
		case 2:
			for (int i = 0; i < 4; i++) {
				moveRandomly(Assets::objects[i]);
			}
			elapsedTime -= 0.1f;
			break;

		case 3:
			for (int i = 0; i < 4; i++)
			{
				moveBFS(Assets::objects[i],dt);
				
			}
			elapsedTime -= 0.16f;
			break;
		default:
			break;
		}
	}
}