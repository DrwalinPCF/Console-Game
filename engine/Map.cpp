
#ifndef MAP_CPP
#define MAP_CPP

#include "Map.h"
#include "BlockState.h"

#include "Actor.h"

#include "Utility.hpp"

Vector Map::GetSize() const
{
	return this->size;
}

void Map::SetBlockState( Vector pos, BlockState state )
{
	if( pos.x >= 0 && pos.y >= 0 && pos.x < this->size.x && pos.y < this->size.y )
	{
		this->space[pos.x][pos.y] = state;
	}
}

const BlockState Map::GetBlockState( Vector pos ) const
{
	if( pos.x >= 0 && pos.y >= 0 && pos.x < this->size.x && pos.y < this->size.y )
	{
		return this->space[pos.x][pos.y];
	}
	return BlockState();
}

BlockState & Map::GetBlockState( Vector pos )
{
	if( pos.x >= 0 && pos.y >= 0 && pos.x < this->size.x && pos.y < this->size.y )
	{
		return this->space[pos.x][pos.y];
	}
	return BlockState::GetPureReference();
}


void Map::AddActor( Actor * actor )
{
	if( actor )
	{
		if( this->actorPreviousPositions.find( actor ) != this->actorPreviousPositions.end() )
		{
			this->UpdateActor( actor );
		}
		else
		{
			Vector pos = actor->GetPos();
			this->actorPreviousPositions[actor] = pos;
			this->actors[pos.x][pos.y].insert( actor );
		}
	}
}

void Map::RemoveActor( Actor * actor )
{
	if( actor )
	{
		auto it = actorPreviousPositions.find( actor );
		if( it != actorPreviousPositions.end() )
		{
			Vector pos = it->second;
			auto it1 = this->actors.find( pos.x );
			if( it1 != this->actors.end() )
			{
				auto it2 = it1->second.find( pos.y );
				if( it2 != it1->second.end() )
				{
					it2->second.erase( actor );
					if( it2->second.size() == 0 )
						it1->second.erase( it2 );
				}
				if( it1->second.size() == 0 )
					this->actors.erase( it1 );
			}
		}
	}
}

void Map::UpdateActor( Actor * actor )
{
	if( actor )
	{
		Vector pos;
		auto it = this->actorPreviousPositions.find( actor );
		if( it != this->actorPreviousPositions.end() )
		{
			pos = it->second;
			auto it1 = this->actors.find( pos.x );
			if( it1 != this->actors.end() )
			{
				auto it2 = it1->second.find( pos.y );
				if( it2 != it1->second.end() )
				{
					it2->second.erase( actor );
					if( it2->second.size() == 0 )
						it1->second.erase( it2 );
				}
				if( it1->second.size() == 0 )
					this->actors.erase( it1 );
			}
			
			pos = actor->GetPos();
			it->second = pos;
		}
		else
		{
			pos = actor->GetPos();
			this->actorPreviousPositions[actor] = pos;
		}
		
		this->actors[pos.x][pos.y].insert( actor );
	}
}

void Map::GetActors( const Vector & min, const Vector & max, const std::set<Actor*> & ignoreActors, std::set<Actor*> & ret )
{
	auto endx = this->actors.lower_bound( max.x+1 );
	for( auto itx = this->actors.upper_bound( min.x-1 ); itx != endx; ++itx )
	{
		auto endy = itx->second.lower_bound( max.y+1 );
		for( auto ity = itx->second.upper_bound( min.y-1 ); ity != endy; ++ity )
		{
			for( auto it = ity->second.begin(); it != ity->second.end(); ++it )
			{
				if( ignoreActors.find( *it ) == ignoreActors.end() )
				{
					ret.insert( *it );
				}
			}
		}
	}
}

bool Map::IsSpaceWalkable( const Vector & min, const Vector & max, const std::set<Actor*> & ignoreActors )
{
	{
		auto endx = this->actors.lower_bound( max.x+1 );
		for( auto itx = this->actors.upper_bound( min.x-1 ); itx != endx; ++itx )
		{
			auto endy = itx->second.lower_bound( max.y+1 );
			for( auto ity = itx->second.upper_bound( min.y-1 ); ity != endy; ++ity )
			{
				for( auto it = ity->second.begin(); it != ity->second.end(); ++it )
				{
					if( (*it)->IsWalkable() == false )
					{
						if( ignoreActors.find( (*it) ) == ignoreActors.end() )
						{
							return false;
						}
					}
				}
			}
		}
	}
	
	{
		BlockState ** endx = &(this->space[(max.x>this->size.x)?(this->size.x-1):max.x]);
		for( BlockState ** px = &(this->space[(min.x<0)?0:min.x]); px <= endx; ++px )
		{
			BlockState * endy = &((*px)[(max.y>=this->size.y)?(this->size.y-1):max.y]);
			for( BlockState * py = &((*px)[(min.y<0)?0:min.y]); py <= endy; ++py )
			{
				if( py->IsWalkable() == false )
				{
					return false;
				}
			}
		}
	}
	
	return true;
}

void Map::Clear()
{
	this->actors.clear();
	this->actorPreviousPositions.clear();
	this->size = Vector( 0, 0 );
	if( this->space )
	{
		BlockState ** end = this->space + this->size.x;
		for( BlockState ** it = this->space; it < end; ++it )
		{
			memset( *it, 0, this->size.y );
		}
	}
}

void Map::Destroy()
{
	this->Clear();
	if( this->space )
	{
		BlockState ** end = this->space + this->size.x;
		for( BlockState ** it = this->space; it < end; ++it )
		{
			Free( *it );
		}
		Free( this->space );
		this->space = NULL;
	}
}

void Map::Init( Vector size )
{
	this->Destroy();
	this->size = size;
	this->space = Allocate<BlockState*>( this->size.x );
	BlockState ** end = this->space + this->size.x;
	for( BlockState ** it = this->space; it < end; ++it )
	{
		*it = Allocate<BlockState>( this->size.y );
	}
}

Map::Map()
{
	this->size = Vector( 0, 0 );
	this->space = NULL;
}

Map::~Map()
{
	this->Destroy();
}

#endif

