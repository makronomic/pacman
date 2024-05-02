#include "check_bound.h"

bool checkBound(Object& o, int up, int down, int left, int right, int tolerance) {
	// make sure the bounds are inside the game resolution with adjustable tolerance
	left = std::max(left, tolerance);
	right = std::min(right, Assets::res - tolerance);
	up = std::max(up, tolerance);
	down = std::min(down, Assets::res - tolerance);

	const auto& bounds = o.getSprite().getGlobalBounds();

	// return true if in bounds
	return left < bounds.left && bounds.left + bounds.width < right && up < bounds.top && bounds.top + bounds.height < down;
}