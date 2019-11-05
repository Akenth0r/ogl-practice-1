#include "PathFinder.h"

PathFinder::PathFinder()
{
	// Default set of possible moves
	moves =
	{
		// x y
		ivec2(0,1),		// up
		ivec2(1,0),		// right
		ivec2(0,-1),	// down
		ivec2(-1,0)		// left
	};
}

PathFinder::PathFinder(const vector<ivec2>& moves)
{
	this->moves = moves;
}

void PathFinder::clearWave()
{
	for (int i = 0; i < 21; i++)
		for (int j = 0; j < 21; j++)
			wave[i][j] = -1;
}


bool PathFinder::isVisited(ivec2 cur)
{
	for (auto it : visited)
		if (it == cur)
			return true;
	return false;
}

bool PathFinder::propagateWave(ivec2 start, ivec2 end)
{
	queue<ivec2> q;
	q.push(start);
	// When start or end isn't empty cell
	// We can't find the path
	if ((passabilityMap[start.y][start.x] && passabilityMap[start.y][start.x] != PLAYER) || (passabilityMap[end.y][end.x] && passabilityMap[start.y][start.x] != PLAYER))
		return false;

	if (end == start)
		return false;

	// Wave source
	wave[start.y][start.x] = 0;



	// Propagate wave
	while (!q.empty())
	{
		ivec2 cur = q.front();
		q.pop();
		
		if (isVisited(cur))
			continue; 
		visited.push_back(cur);

		// If we find end point - propagation will stop
		if (cur == end)
			break;
		// Go through possible moves
		for (auto move : moves)
		{
			int x = cur.x + move.x,
				y = cur.y + move.y;
			// When cell is not visited and it is empty cell
			if (y >= 0 && y < 21 && x >= 0 && x < 21 && passabilityMap[y][x] == EMPTY && !isVisited(ivec2(x,y)))
			{
				// Add to queue and set the cost
				q.push(ivec2(x, y));
				wave[y][x] = wave[cur.y][cur.x] + 1;
			}
		}
	}
		return true; // wave was propagated
}

vector<ivec2> PathFinder::findPath(ivec2 start, ivec2 end)
{
	clearWave();
	path.clear();
	visited.clear();
	// If wave was not propagated
	// then there are no possible paths
	if (!propagateWave(start, end))
		return path;
	ivec2 cur = end;
	// If end was not reached, move to nearest
	if (wave[end.y][end.x] < 0)
	{
		ivec2 min = start; 
		ivec2 dif = end - min;
		float distance = sqrt((float)dif.x * dif.x + (float)dif.y * dif.y); // euclidean distance
		for (int i = 0; i < 21; i++)
		{
			for (int j = 0; j < 21; j++)
				if (wave[i][j] >= 0)
				{
					ivec2 cur = ivec2(j, i);
					dif = end - cur;
					float curDistance = sqrt((float)dif.x * dif.x + (float)dif.y * dif.y);
					if (distance > curDistance)
					{
						distance = curDistance;
						min = cur;
					}
				}

		}
		cur = min;
	}

	if (start == cur)
		return path;

	path.push_back(cur);
	while (cur != start)
		for (auto move : moves)
		{
			int x = cur.x + move.x,
				y = cur.y + move.y;
			// Find a cell with cost = cur.cost - 1
			if (y >= 0 && y < 21 && x >= 0 && x < 21 && wave[y][x] == (wave[cur.y][cur.x] - 1) && wave[y][x] != -1)
			{
				path.push_back(ivec2(x, y));
				cur = ivec2(x, y);
			}
		}
	reverse(path.begin(), path.end());
	return path;
}