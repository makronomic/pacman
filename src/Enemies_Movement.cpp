#include "Enemies_Movement.h"


Object ghost(
    { 700.f, 100.f },
    2.f,
    Object::Type::ENEMY
);


void dummyGhostSpawn() {
    ghost.setSpriteSheet("resources/ghosts.png");
    ghost.getSprite().setTexture(ghost.getSpriteSheet());
    ghost.getSprite().setTextureRect(sf::IntRect(
        0,
        0,
        16,
        16
    ));
    ghost.getSprite().setScale(2, 2);
}



// Convert character state to Direction enum
Direction convertStateToDirection(char state) {
    switch (state) {
    case 'u': return Up;
    case 'd': return Down;
    case 'l': return Left;
    case 'r': return Right;
    default: return None;
    }
}

// Convert Direction enum to character state
char convertDirectionToState(Direction dir) {
    switch (dir) {
    case Up: return 'u';
    case Down: return 'd';
    case Left: return 'l';
    case Right: return 'r';
    default: return 'i';  // 'i' for idle or invalid
    }
}

// Get the opposite direction to avoid backtracking
Direction getOppositeDirection(Direction dir) {
    switch (dir) {
    case Up: return Down;
    case Down: return Up;
    case Left: return Right;
    case Right: return Left;
    default: return None;
    }
}

// Function to simulate and check ghost movement without collisions
bool canMoveToPosition(Object& ghost, int newX, int newY) {
    Object simulatedGhost = ghost;
    simulatedGhost.setPos(newX, newY);
    simulatedGhost.getSprite().setPosition(static_cast<float>(newX), static_cast<float>(newY));

    for (const auto& other : Assets::objects) {
        if (&ghost != other && ghost.getSprite().getGlobalBounds().intersects(other->getSprite().getGlobalBounds())) {
            return false; // Collision detected
        }
    }
    return true; // No collision detected, move is valid
}

// Choose a new direction that does not lead to a collision
Direction chooseNewDirection(Object& ghost, Direction currentDirection) {
    std::vector<Direction> possibleDirections = { Up, Down, Left, Right };
    possibleDirections.erase(std::remove(possibleDirections.begin(), possibleDirections.end(), getOppositeDirection(currentDirection)), possibleDirections.end());

    std::vector<Direction> validDirections;
    for (auto dir : possibleDirections) {
        int newX = ghost.getPos().x, newY = ghost.getPos().y;
        switch (dir) {
        case Down:  newY += 2; break;
        case Left:  newX -= 2; break;
        case Up:    newY -= 2; break;
        case Right: newX += 2; break;
        }
        if (canMoveToPosition(ghost, newX, newY)) {
            validDirections.push_back(dir);
        }
    }

    if (!validDirections.empty()) {
        int randIndex = rand() % validDirections.size();
        return validDirections[randIndex];
    }

    return currentDirection; // If no valid move, continue in the current direction
}


void updateGhost(Object& ghost) {

    Direction currentDirection = convertStateToDirection(ghost.state);
    Direction newDirection = chooseNewDirection(ghost, currentDirection);
    ghost.state = convertDirectionToState(newDirection);

    // Apply movement based on new direction
    switch (newDirection) {
    case Up:    ghost.setPos(ghost.getPos().x, ghost.getPos().y - 2); break;
    case Down:  ghost.setPos(ghost.getPos().x, ghost.getPos().y + 2); break;
    case Left:  ghost.setPos(ghost.getPos().x - 2, ghost.getPos().y); break;
    case Right: ghost.setPos(ghost.getPos().x + 2, ghost.getPos().y); break;
    default:    break;  // No movement if None
    }

    // Ensure the sprite position is synchronized with the logical position
    ghost.getSprite().setPosition(ghost.getPos());

}