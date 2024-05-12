#pragma once
#include "object.h"

class Animation
{
public:
	static void motionPicture(Object&);
	static void enemyState(Object& x, int enemyFrameDirection, int yPos, int& counter);
};

