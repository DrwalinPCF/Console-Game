
#ifndef WORLD_GENERATOR_H
#define WORLD_GENERATOR_H

#include "../engine/World.h"

#include "../lib/Vector.hpp"

#include <vector>
#include <map>

#include <ctime>
#include <cstdlib>

class WorldGenerator
{
private:
	
	World * world;
	
	std::vector < std::vector < bool > > mapA, mapB;
	bool isCurrentlyA;
	
	Vector begin;
	Vector end;
	Vector size;
	
public:
	
	void GameOfLifeStep( const int minToGetAlive, const int minBorderLife, const int maxBorderLife, int radius );
	
	void GenerateActors();
	
	void GenerateRandom( float filling );
	void GeneratePerlinNoise();
	
	WorldGenerator( World * world, Vector begin, Vector end );
	~WorldGenerator();
	
};

#endif

