#pragma once
#include "GLM/glm.hpp"
#include <iostream>
#include "Data.h"
#include <vector>


using namespace std;
using namespace glm;


// Portal
class Portal
{
public:
	// Default constructor
	Portal();
	// Constructor (2 entry min, in ivec4)
	Portal(ivec4 entries);
	// Another constructor with 2 ivecs
	Portal(ivec2 entry1, ivec2 entry2);
	// Constructor to construct from vector
	Portal(vector<ivec2> entries);
	// Add portal entry
	void AddEntry(ivec2 entry);
	// Check if player is in portal
	bool isPlayerInPortal();
	// Check if player left portal after using
	bool isPlayerLeftPortal();
	// Set left
	void setPlayerLeftPortal(bool left);
	// Next player position
	ivec2 getNextPlayerPos();
	// Simulate portal
	void simulate();

private:
	// Entry list
	vector<ivec2> entries;
	// Is portal left by player
	vector<ivec2>::iterator curPlayerEntry;
	bool isLeft;
};