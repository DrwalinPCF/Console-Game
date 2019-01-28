
#ifndef MAP_CPP
#define MAP_CPP

#include "Map.h"

Map::Box::Box()
{
	min = 0;
	max = 0;
	min_ = 0;
	max_ = 0;
	actor = NULL;
}

FILE * df_ile = NULL;

void Map::AddActor( Actor * actor )
{
	if( df_ile == NULL )
		df_ile = fopen( "DebugFile.txt", "w" );
	fprintf( df_ile, "\nA - 0x%p", actor );
	fflush( df_ile );
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
				
				box->min_ = (box->min-MODIFIER)/DIVIDER;
				box->max_ = (box->max+MODIFIER)/DIVIDER;
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
}

void Map::RemoveActor( Actor * actor )
{
	if( actor )
	{
		auto it = this->actors.find( actor );
		if( it != this->actors.end() )
		{
			/*
			for( auto it1 = this->space.begin(); it1 != this->space.end(); ++it1 )
			{
				for( auto it2 = it1->second.begin(); it2 != it1->second.end(); ++it2 )
				{
					it2->second.erase(it->second );
				}
			}
			*/
			
			for( auto it1 = this->space.begin(); it1 != this->space.end(); ++it1 )
			{
				for( auto it2 = it1->second.begin(); it2 != it1->second.end(); ++it2 )
				{
					if( it2->second.find( it->second ) != it2->second.end() )
					{
						fprintf( df_ile, "\n Before removing: [%lli][%lli] = %s", it1->first, it2->first, it->second->actor->GetName().c_str() );
						fflush( df_ile );
					}
				}
			}
			
			Box * box = it->second;
			
			fprintf( df_ile, "\n Zakres x = < %lli;%lli > <= < %lli;%lli >", box->min_.x, box->max_.x, box->min.x, box->max.x );
			fflush( df_ile );
			fprintf( df_ile, "\n Zakres y = < %lli;%lli > <= < %lli;%lli >", box->min_.y, box->max_.y, box->min.x, box->max.x );
			fflush( df_ile );
			
			auto itx = this->space.lower_bound( box->min_.x );
			auto itxe = this->space.upper_bound( box->max_.x );
			++itxe;
			for( ; itx != itxe && itx != this->space.end(); ++itx )
			{
				auto ity = itx->second.lower_bound( box->min_.y );
				auto itye = itx->second.upper_bound( box->max_.y );
				++itye;
				for( ; ity != itye && ity != itx->second.end(); ++ity )
				{
					ity->second.erase( box );
				}
			}
			
			for( auto it1 = this->space.begin(); it1 != this->space.end(); ++it1 )
			{
				for( auto it2 = it1->second.begin(); it2 != it1->second.end(); ++it2 )
				{
					if( it2->second.find( it->second ) != it2->second.end() )
					{
						fprintf( df_ile, "\n After removing: [%lli][%lli] = %s", it1->first, it2->first, it->second->actor->GetName().c_str() );
						fflush( df_ile );
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
	if( df_ile == NULL )
		df_ile = fopen( "DebugFile.txt", "w" );
	fprintf( df_ile, "\nU - 0x%p", actor );
	fflush( df_ile );
	if( actor )
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
			
			if( box->min_ != (box->min-MODIFIER)/DIVIDER || box->max_ != (box->max+MODIFIER)/DIVIDER )
			{
				box->min_ = (box->min-MODIFIER)/DIVIDER;
				box->max_ = (box->max+MODIFIER)/DIVIDER;
				
				for( auto it1 = this->space.begin(); it1 != this->space.end(); ++it1 )
				{
					for( auto it2 = it1->second.begin(); it2 != it1->second.end(); ++it2 )
					{
						if( it2->second.find( box ) != it2->second.end() )
						{
							fprintf( df_ile, "\n Before updating: [%lli][%lli] = %s", it1->first, it2->first, box->actor->GetName().c_str() );
							fflush( df_ile );
						}
					}
				}
				
				fprintf( df_ile, "\n Zakres x = < %lli;%lli > <= < %lli;%lli >", box->min_.x, box->max_.x, box->min.x, box->max.x );
				fflush( df_ile );
				fprintf( df_ile, "\n Zakres y = < %lli;%lli > <= < %lli;%lli >", box->min_.y, box->max_.y, box->min.x, box->max.x );
				fflush( df_ile );
				
				auto itx = this->space.lower_bound( box->min_.x );
				auto itxe = this->space.upper_bound( box->max_.x );
				++itxe;
				for( ; itx != itxe && itx != this->space.end(); ++itx )
				{
					auto ity = itx->second.lower_bound( box->min_.y );
					auto itye = itx->second.upper_bound( box->max_.y );
					++itye;
					for( ; ity != itye && ity != itx->second.end(); ++ity )
					{
						ity->second.erase( box );
					}
				}
				
				for( auto it1 = this->space.begin(); it1 != this->space.end(); ++it1 )
				{
					for( auto it2 = it1->second.begin(); it2 != it1->second.end(); ++it2 )
					{
						if( it2->second.find( box ) != it2->second.end() )
						{
							fprintf( df_ile, "\n After updating: [%lli][%lli] = %s", it1->first, it2->first, box->actor->GetName().c_str() );
							fflush( df_ile );
						}
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
}

void Map::GetActors( const Vector & min, const Vector & max, const std::set<Actor*> & ignoreActors, std::set<Actor*> & ret ) const
{
	Vector min_ = (min-MODIFIER)/DIVIDER;
	Vector max_ = (max+MODIFIER)/DIVIDER;
	auto itx = this->space.lower_bound( min_.x );
	auto itxe = this->space.upper_bound( max_.x );
	++itxe;
	for( ; itx != itxe && itx != this->space.end(); ++itx )
	{
		auto ity = itx->second.lower_bound( min_.y );
		auto itye = itx->second.upper_bound( max_.y );
		++itye;
		for( ; ity != itye && ity != itx->second.end(); ++ity )
		{
			for( auto it = ity->second.begin(); it != ity->second.end(); ++it )
			{
				if( *it )
					if( (*it)->actor )
						if( (*it)->actor->InBounds( min, max ) )
							if( ignoreActors.find((*it)->actor) == ignoreActors.end() )
								ret.insert( (*it)->actor );
			}
		}
	}
}

bool Map::IsSpaceWalkable( const Vector & min, const Vector & max, const std::set<Actor*> & ignoreActors ) const
{
	Vector min_ = (min-MODIFIER)/DIVIDER;
	Vector max_ = (max+MODIFIER)/DIVIDER;
	auto itx = this->space.lower_bound( min_.x );
	auto itxe = this->space.upper_bound( max_.x );
	++itxe;
	for( ; itx != itxe && itx != this->space.end(); ++itx )
	{
		auto ity = itx->second.lower_bound( min_.y );
		auto itye = itx->second.upper_bound( max_.y );
		++itye;
		for( ; ity != itye && ity != itx->second.end(); ++ity )
		{
			for( auto it = ity->second.begin(); it != ity->second.end(); ++it )
			{
				if( *it )
					if( (*it)->actor )
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

Map::Map() :
	MODIFIER(3,3), DIVIDER(4)
{
	world = NULL;
}

Map::~Map()
{
	this->Clear();
}

#endif

