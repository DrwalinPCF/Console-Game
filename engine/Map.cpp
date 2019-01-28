
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
	//fprintf( df_ile, "\nA - 0x%p", actor );
	//fflush( df_ile );
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
						this->space.Access( pos.x, pos.y ).insert( actor );
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
					std::unordered_set<Actor*> & ref = this->space.Access( pos.x, pos.y );
					ref.erase( actor );
					if( ref.empty() )
						this->space.Erase( pos.x, pos.y );
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
					std::unordered_set<Actor*> & ref = this->space.Access( pos.x, pos.y );
					ref.erase( actor );
					if( ref.empty() )
						this->space.Erase( pos.x, pos.y );
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
					this->space.Access( pos.x, pos.y ).insert( actor );
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
			const std::unordered_set<Actor*> & ref = this->space.Access( pos.x, pos.y );
			for( auto it = ref.begin(); it != ref.end(); ++it )
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

bool Map::IsSpaceWalkable( const Vector & min, const Vector & max, const std::set<Actor*> & ignoreActors ) const
{
	Vector pos;
	for( pos.x = min.x; pos.x <= max.x; ++pos.x )
	{
		for( pos.y = min.y; pos.y <= max.y; ++pos.y )
		{
			const std::unordered_set<Actor*> & ref = this->space.Access( pos.x, pos.y );
			for( auto it = ref.begin(); it != ref.end(); ++it )
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
	return true;
}

void Map::Clear()
{
	for( auto it = this->actors.begin(); it != this->actors.end(); ++it )
		Free( it->second );
	this->actors.clear();
	this->space.Clear();
}

Map::Map() :
	MODIFIER(0,0), DIVIDER(1), space(std::unordered_set<Actor*>())
{
}

Map::~Map()
{
	this->Clear();
}

#endif

