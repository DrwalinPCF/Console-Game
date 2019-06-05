
#ifndef WORLD_GENERATOR_CPP
#define WORLD_GENERATOR_CPP

#include "WorldGenerator.h"

#include "Block.hpp"

void WorldGenerator::GameOfLifeStep( const int minToGetAlive, const int minBorderLife, const int maxBorderLife, int radius )
{
	auto & mapA = this->isCurrentlyA ? this->mapA : this->mapB;
	auto & mapB = this->isCurrentlyA ? this->mapB : this->mapA;
	
	int i, j, k, l, sum;
	
	for( i = 0; i < this->size.x; ++i )
	{
		for( j = 0; j < this->size.y; ++j )
		{
			sum ^= sum;
			for( k = ( (i-radius) < 0 ) ? 0 : (i-radius); k < this->size.x && k <= i+radius; ++k )
			{
				for( l = ( (j-radius) < 0 ) ? 0 : (j-radius); l < this->size.y && l <= j+radius; ++l )
				{
					if( k != i || l != j )
						sum += (int)( mapA[k][l] );
				}
			}
			if( sum < minBorderLife || sum > maxBorderLife )
				mapB[i][j] = false;
			else if( sum >= minToGetAlive )
				mapB[i][j] = true;
			else
				mapB[i][j] = mapA[i][j];
		}
	}
	
	this->isCurrentlyA = !(this->isCurrentlyA);
}

void WorldGenerator::GenerateActors()
{
	int i, j, prev;
	
	auto & map = this->isCurrentlyA ? this->mapB : this->mapA;
	
	for( i = 0; i < this->size.x; ++i )
	{
		auto & line = map[i];
		j = 0;
		
		while( j < this->size.y )
		{
			for( ; j < this->size.y && line[j] == false; ++j );
			if( j >= this->size.y )
				break;
			prev = j;
			for( ; j < this->size.y && line[j] == true; ++j );
			
			int l = j - prev;
			
			this->world->AddActor( this->world->GetNewUniqueActorName(), Vector( i, prev ) + this->begin, Vector( 1, l ), Allocate<Block>() );
		}
	}
}

void WorldGenerator::GenerateRandom( float filling )
{
	auto & map = this->isCurrentlyA ? this->mapA : this->mapB;
	int i, j;
	for( i = 0; i < this->size.x; ++i )
	{
		auto & A = map[i];
		for( j = 0; j < this->size.y; ++j )
		{
			A[j] = (bool)( rand() < ((int)(filling*(float)RAND_MAX)) );
		}
	}
}

WorldGenerator::WorldGenerator( World * world, Vector begin, Vector end )
{
	this->world = world;
	
	this->begin = begin;
	this->end = end;
	this->size = this->end - this->begin;
	
	this->isCurrentlyA = false;
	
	int i, j;
	this->mapA.resize( this->size.x );
	this->mapB.resize( this->size.x );
	for( i = 0; i < this->size.x; ++i )
	{
		this->mapA[i].resize( this->size.y );
		this->mapB[i].resize( this->size.y );
		for( j = 0; j < this->size.y; ++j )
		{
			this->mapA[i][j] = false;
			this->mapB[i][j] = false;
		}
	}
}

WorldGenerator::~WorldGenerator()
{
	
}

#endif

