#pragma once
#include <queue>
#include "data.h"
#include <vector>
#include <GLM/glm.hpp>

class PathFinder
{

public:
	// Constructors
	PathFinder();
	PathFinder(const vector<ivec2>& moves);

	// Find shortest path using Lee algorithm
	vector<ivec2> findPath(ivec2 start, ivec2 end);

	~PathFinder()=default;

private:
	// Clear wave
	void clearWave();
	// Set costs
	bool propagateWave(ivec2 start, ivec2 end);
	// Checks if cell visited
	bool isVisited(ivec2 cur);

	vector<ivec2> path;
	vector<ivec2> visited;
	vector<ivec2> moves; // set of moves
	int wave[21][21];
};
