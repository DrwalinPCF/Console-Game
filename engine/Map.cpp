
#ifndef MAP_CPP
#define MAP_CPP

#include "Map.h"

void Map::AddActor( Actor * actor )
{
	if( actor )
	{
		if( this->actors.find( actor ) != this->actors.end() )
			this->UpdateActor( actor );
		else
		{
			Map::Box * box = Allocate<Map::Box>();
			box->min = actor->GetAABBmin();
			box->max = actor->GetAABBmax();
			box->actor = actor;
			this->actors[ actor ] = box;
			this->spaceMin[ box->min.x ][ box->min.y ].insert( box );
		}
	}
}

void Map::RemoveActor( Actor * actor )
{
	auto it = this->actors.find( actor );
	if( it != this->actors.end() )
	{
		this->spaceMin[ it->second->min.x ][ it->second->min.y ].erase( it->second );
		if( this->spaceMin[ it->second->min.x ][ it->second->min.y ].empty() )
		{
			this->spaceMin[ it->second->min.x ].erase( it->second->min.y );
			if( this->spaceMin[ it->second->min.x ].empty() )
			{
				this->spaceMin.erase( it->second->min.x );
			}
		}
		
		//delete it->second;
		Free( it->second );
		it->second = nullptr;
		this->actors.erase( it );
	}
}

void Map::UpdateActor( Actor * actor )
{
	auto it = this->actors.find( actor );
	if( it != this->actors.end() )
	{
		this->spaceMin[ it->second->min.x ][ it->second->min.y ].erase( it->second );
		if( this->spaceMin[ it->second->min.x ][ it->second->min.y ].empty() )
		{
			this->spaceMin[ it->second->min.x ].erase( it->second->min.y );
			if( this->spaceMin[ it->second->min.x ].empty() )
			{
				this->spaceMin.erase( it->second->min.x );
			}
		}
		
		it->second->min = actor->GetAABBmin();
		it->second->max = actor->GetAABBmax();
		this->spaceMin[ it->second->min.x ][ it->second->min.y ].insert( it->second );
	}
}

void Map::GetActors( const Vector & min, const Vector & max, const std::set<Actor*> & ignoreActors, std::set<Actor*> & ret )
{
	auto itBegX = this->spaceMin.begin();
	auto itEndX = this->spaceMin.lower_bound( max.x + 1 );
	
	for( ; itBegX != itEndX; ++itBegX )
	{
		auto itBegY = itBegX->second.begin();
		
		auto itEndY = itBegX->second.lower_bound( max.y + 1 );
		for( ; itBegY != itEndY; ++itBegY )
		{
			for( auto it = itBegY->second.begin(); it != itBegY->second.end(); ++it )
			{
				if( (*it)->actor->InBounds( min, max ) )
					if( ignoreActors.find((*it)->actor) == ignoreActors.end() )
						ret.insert( (*it)->actor );
			}
		}
	}
}

bool Map::IsSpaceWalkable( const Vector & min, const Vector & max, const std::set<Actor*> & ignoreActors )
{
	auto itBegX = this->spaceMin.begin();
	auto itEndX = this->spaceMin.lower_bound( max.x + 1 );
	
	for( ; itBegX != itEndX; ++itBegX )
	{
		auto itBegY = itBegX->second.begin();
		
		auto itEndY = itBegX->second.lower_bound( max.y + 1 );
		for( ; itBegY != itEndY; ++itBegY )
		{
			for( auto it = itBegY->second.begin(); it != itBegY->second.end(); ++it )
			{
				if( (*it)->actor->IsWalkable() == false )
					if( (*it)->actor->InBounds( min, max ) )
						if( ignoreActors.find((*it)->actor) == ignoreActors.end() )
							return false;
			}
		}
	}
	
	return true;
}

void Map::Clear()
{
	for( auto it = actors.begin(); it != actors.end(); ++it )
		Free( it->second );
		//delete it->second;
	actors.clear();
	spaceMin.clear();
	world = nullptr;
}
	
class World * Map::GetWorld()
{
	return this->world;
}

void Map::SetWorld( class World * world )
{
	this->world = world;
}

Map::Map()
{
	world = nullptr;
}

Map::~Map()
{
	this->Clear();
}

#endif

