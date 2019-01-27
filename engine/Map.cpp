
#ifndef MAP_CPP
#define MAP_CPP

#include "Map.h"

void Map::AddActor( Actor * actor )
{
	if( actor )
	{
		if( this->actors.find( actor ) != this->actors.end() )
		{
			this->UpdateActor( actor );
		}
		else
		{
			Map::Box * box = Allocate<Map::Box>();
			box->min = actor->GetAABBmin();
			box->max = actor->GetAABBmax();
			
			if( box->min.x > box->max.x )
				std::swap( box->min.x, box->max.x );
			if( box->min.y > box->max.y )
				std::swap( box->min.y, box->max.y );
			
			box->min_ = (box->min-15)/16;
			box->max_ = (box->max+15)/16;
			box->actor = actor;
			this->actors[ actor ] = box;
			
			Vector pos;
			for( pos.x = box->min_.x; pos.x <= box->max_.x; ++pos.x )
			{
				std::map < loctype, std::set<Box*> > & it = this->space[pos.x];
				for( pos.y = box->min_.y; pos.y <= box->max_.y; ++pos.y )
				{
					it[pos.y].insert( box );
				}
			}
		}
	}
}

void Map::RemoveActor( Actor * actor )
{
	auto it = this->actors.find( actor );
	if( it != this->actors.end() )
	{
		Box * box = it->second;
		auto itx = this->space.begin();//upper_bound( box->min_.x );
		auto itxe = this->space.lower_bound( box->max_.x );
		++itxe;
		for( ; /*itx != itxe &&*/ itx != this->space.end(); ++itx )
		{
			auto ity = itx->second.begin();//upper_bound( box->min_.y );
			auto itye = itx->second.lower_bound( box->max_.y );
			++itye;
			for( ; /*ity != itye &&*/ ity != itx->second.end(); ++ity )
			{
				ity->second.erase( box );
			}
		}
		
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
		Box * box = it->second;
		
		box->min = actor->GetAABBmin();
		box->max = actor->GetAABBmax();
			
		if( box->min.x > box->max.x )
			std::swap( box->min.x, box->max.x );
		if( box->min.y > box->max.y )
			std::swap( box->min.y, box->max.y );
		
		if( box->min_ != (box->min-15)/16 || box->max_ != (box->max+15)/16 )
		{
			box->min_ = (box->min-15)/16;
			box->max_ = (box->max+15)/16;
			
			auto itx = this->space.begin();//upper_bound( box->min_.x );
			auto itxe = this->space.lower_bound( box->max_.x );
			++itxe;
			for( ; /*itx != itxe &&*/ itx != this->space.end(); ++itx )
			{
				auto ity = itx->second.begin();//upper_bound( box->min_.y );
				auto itye = itx->second.lower_bound( box->max_.y );
				++itye;
				for( ; /*ity != itye &&*/ ity != itx->second.end(); ++ity )
				{
					ity->second.erase( box );
				}
			}
			
			Vector pos;
			for( pos.x = box->min_.x; pos.x <= box->max_.x; ++pos.x )
			{
				std::map < loctype, std::set<Box*> > & it = this->space[pos.x];
				for( pos.y = box->min_.y; pos.y <= box->max_.y; ++pos.y )
				{
					it[pos.y].insert( box );
				}
			}
		}
	}
	else
	{
		this->AddActor( actor );
	}
}

void Map::GetActors( const Vector & min, const Vector & max, const std::set<Actor*> & ignoreActors, std::set<Actor*> & ret )
{
	Vector min_ = (min-15)/16;
	Vector max_ = (max+15)/16;
	auto itx = this->space.begin();//upper_bound( min_.x );
	auto itxe = this->space.lower_bound( max_.x );
	++itxe;
	for( ; /*itx != itxe &&*/ itx != this->space.end(); ++itx )
	{
		auto ity = itx->second.begin();//upper_bound( min_.y );
		auto itye = itx->second.lower_bound( max_.y );
		++itye;
		for( ; /*ity != itye &&*/ ity != itx->second.end(); ++ity )
		{
			for( auto it = ity->second.begin(); it != ity->second.end(); ++it )
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
	Vector min_ = (min-15)/16;
	Vector max_ = (max+15)/16;
	auto itx = this->space.begin();//upper_bound( min_.x );
	auto itxe = this->space.lower_bound( max_.x );
	++itxe;
	for( ; /*itx != itxe &&*/ itx != this->space.end(); ++itx )
	{
		auto ity = itx->second.begin();//upper_bound( min_.y );
		auto itye = itx->second.lower_bound( max_.y );
		++itye;
		for( ; /*ity != itye &&*/ ity != itx->second.end(); ++ity )
		{
			for( auto it = ity->second.begin(); it != ity->second.end(); ++it )
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
	actors.clear();
	space.clear();
	world = NULL;
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
	world = NULL;
}

Map::~Map()
{
	this->Clear();
}

#endif

