#pragma once

#include "assets.h"
#include "Object.h"
#include <cassert>
#include <math.h>

bool bound_check(Object&, int up = 0, int down = Assets::res, int left = 0, int right = Assets::res, int tolerance = 5);
