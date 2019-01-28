
#ifndef MAP_CPP
#define MAP_CPP

#include "Map.h"

Map::Box::Box()
{
	min = Vector(0,0);
	max = Vector(0,0);
	actor = NULL;
}

FILE * df_ile = NULL;

void Map::AddActor( Actor * actor )
{
	if( df_ile == NULL )
		df_ile = fopen( "DebugFile.txt", "w" );
	if( actor )
	{
		if( this->actors.find( actor ) != this->actors.end() )
		{
			this->UpdateActor( actor );
		}
		else
		{
			Map::Box * box = Allocate<Map::Box>();
			if( box )
			{
				box->min = actor->GetAABBmin();
				box->max = actor->GetAABBmax();
				
				if( box->min.x > box->max.x )
					std::swap( box->min.x, box->max.x );
				if( box->min.y > box->max.y )
					std::swap( box->min.y, box->max.y );
				
				box->actor = actor;
				this->actors[ actor ] = box;
				
				Vector pos;
				for( pos.x = box->min.x; pos.x <= box->max.x; ++pos.x )
				{
					for( pos.y = box->min.y; pos.y <= box->max.y; ++pos.y )
					{
						this->space[pos].insert( actor );
					}
				}
			}
		}
	}
}

void Map::RemoveActor( Actor * actor )
{
	if( actor )
	{
		auto it = this->actors.find( actor );
		if( it != this->actors.end() )
		{
			Box * box = it->second;
			
			Vector pos;
			for( pos.x = box->min.x; pos.x <= box->max.x; ++pos.x )
			{
				for( pos.y = box->min.y; pos.y <= box->max.y; ++pos.y )
				{
					auto it = this->space.find( pos );
					if( it != this->space.end() )
					{
						it->second.erase( actor );
						if( it->second.empty() )
						{
							this->space.erase( it );
						}
					}
				}
			}
			
			Free( it->second );
			it->second = nullptr;
			this->actors.erase( it );
		}
	}
}

void Map::UpdateActor( Actor * actor )
{
	if( actor )
	{
		auto it = this->actors.find( actor );
		if( it != this->actors.end() )
		{
			Box * box = it->second;
			
			Vector pos;
			for( pos.x = box->min.x; pos.x <= box->max.x; ++pos.x )
			{
				for( pos.y = box->min.y; pos.y <= box->max.y; ++pos.y )
				{
					auto it = this->space.find( pos );
					if( it != this->space.end() )
					{
						it->second.erase( actor );
						if( it->second.empty() )
						{
							this->space.erase( it );
						}
					}
				}
			}
			
			box->min = actor->GetAABBmin();
			box->max = actor->GetAABBmax();
			
			if( box->min.x > box->max.x )
				std::swap( box->min.x, box->max.x );
			if( box->min.y > box->max.y )
				std::swap( box->min.y, box->max.y );
			
			for( pos.x = box->min.x; pos.x <= box->max.x; ++pos.x )
			{
				for( pos.y = box->min.y; pos.y <= box->max.y; ++pos.y )
				{
					this->space[pos].insert( actor );
				}
			}
		}
		else
		{
			this->AddActor( actor );
		}
	}
}

void Map::GetActors( const Vector & min, const Vector & max, const std::set<Actor*> & ignoreActors, std::set<Actor*> & ret ) const
{
	Vector pos;
	for( pos.x = min.x; pos.x <= max.x; ++pos.x )
	{
		for( pos.y = min.y; pos.y <= max.y; ++pos.y )
		{
			auto it_ = this->space.find( pos );
			if( it_ != this->space.end() )
			{
				for( auto it = it_->second.begin(); it != it_->second.end(); ++it )
				{
					if( (*it)->InBounds( min, max ) )
					{
						if( ignoreActors.find(*it) == ignoreActors.end() )
						{
							ret.insert( *it );
						}
					}
				}
			}
		}
	}
}

bool Map::IsSpaceWalkable( const Vector & min, const Vector & max, const std::set<Actor*> & ignoreActors ) const
{
	Vector pos;
	for( pos.x = min.x; pos.x <= max.x; ++pos.x )
	{
		for( pos.y = min.y; pos.y <= max.y; ++pos.y )
		{
			auto it_ = this->space.find( pos );
			if( it_ != this->space.end() )
			{
				for( auto it = it_->second.begin(); it != it_->second.end(); ++it )
				{
					if( (*it)->IsWalkable() == false )
					{
						if( (*it)->InBounds( min, max ) )
						{
							if( ignoreActors.find(*it) == ignoreActors.end() )
							{
								return false;
							}
						}
					}
				}
			}
		}
	}
	return true;
}

void Map::Clear()
{
	for( auto it = this->actors.begin(); it != this->actors.end(); ++it )
		Free( it->second );
	this->actors.clear();
	this->space.clear();
}

Map::Map() :
	MODIFIER(0,0), DIVIDER(1)
{
}

Map::~Map()
{
	this->Clear();
}

#endif

