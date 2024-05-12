#pragma once
#include "Object.h"
#include "motion.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm> // For std::shuffle
#include <random>    // For std::mt19937 and std::uniform_int_distribution

extern Object ghost;

//enum Direction {
//    Up,
//    Down,
//    Left,
//    Right,
//    None  // Handle invalid direction
//};

void dummyGhostSpawn();
//Direction convertStateToDirection(char);
//char convertDirectionToState(Direction);
//Direction getOppositeDirection(Direction);
//Direction getOppositeDirection(Direction);
//bool canMoveToPosition(Object&, int, int);
//Direction chooseNewDirection(Object&, Direction);
void updateGhost(int difficulty);