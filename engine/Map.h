
#ifndef MAP_H
#define MAP_H

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <set>

#include "Vector.hpp"

#include "Actor.h"

#include "Quadtree.h"

class Map
{
private:
	
	const Vector MODIFIER;
	const long long DIVIDER;
	
	class Box
	{
	public:
		Vector min;
		Vector max;
		Actor * actor;
		Box();
	};
	
	Quadtree< std::unordered_set<Actor*> > space;
	
	std::unordered_map < Actor*, Box* > actors;
	
public:
	
	void AddActor( Actor * actor );
	void RemoveActor( Actor * actor );
	
	void UpdateActor( Actor * actor );
	
	void GetActors( const Vector & min, const Vector & max, const std::set<Actor*> & ignoreActors, std::set<Actor*> & ret ) const;
	bool IsSpaceWalkable( const Vector & min, const Vector & max, const std::set<Actor*> & ignoreActors = std::set<Actor*>() ) const;
	
	void Clear();
	
	Map();
	~Map();
};

#endif

