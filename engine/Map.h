
#ifndef MAP_H
#define MAP_H

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <set>
#include <map>

#include "Vector.hpp"
#include "BlockState.h"

class Map
{
private:
	
	std::unordered_map < class Actor*, Vector > actorPreviousPositions;
	std::map < loctype, std::map < loctype, std::unordered_set<class Actor*> > > actors;
	
	Vector size;
	class BlockState ** space;
	
public:
	
	Vector GetSize() const;
	
	void SetBlockState( Vector pos, BlockState state );
	const BlockState GetBlockState( Vector pos ) const;
	BlockState & GetBlockState( Vector pos );
	
	void AddActor( class Actor * actor );
	void RemoveActor( class Actor * actor );
	
	void UpdateActor( class Actor * actor );
	
	void GetActors( const Vector & min, const Vector & max, const std::set<class Actor*> & ignoreActors, std::set<class Actor*> & ret );
	bool IsSpaceWalkable( const Vector & min, const Vector & max, const std::set<class Actor*> & ignoreActors = std::set<class Actor*>() );
	
	void Clear();
	void Destroy();
	void Init( Vector size );
	
	Map();
	~Map();
};

#endif

