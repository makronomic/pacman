#pragma once
#include <chrono>
#include <random>

namespace Random {
inline std::mt19937 init() {
	std::random_device rd {};
	std::seed_seq	   seq {
		 static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()),
		 rd(),
		 rd(),
		 rd(),
		 rd(),
		 rd(),
	};
	return std::mt19937 { seq };
}

inline std::mt19937 mt { init() };

// Returns a random integer in the inclusive range of [min, max]
inline int get(const int& min, const int& max) {
	if (min >= max)
		return 0;
	return std::uniform_int_distribution { min, max }(mt);
}
} // namespace Random