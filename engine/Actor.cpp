
#ifndef ACTOR_CPP
#define ACTOR_CPP

#include "Actor.h"
#include "Map.h"
#include "World.h"

std::string Actor::GetName() const
{
	return this->name;
}

bool Actor::SetPos( const Vector & loc )
{
	if( this->world )
	{
		if( this->world->GetMap() )
		{
			Vector temp = this->pos;
			this->pos = loc;
			if( this->IsWalkable() || this->world->GetMap()->IsSpaceWalkable( this->pos, this->pos, {this} ) )
			{
				this->world->GetMap()->UpdateActor( this );
				return true;
			}
			this->pos = temp;
		}
	}
	return false;
}

bool Actor::Move( const Vector & move )
{
	return this->SetPos( this->pos + move );
}

Vector Actor::GetPos() const
{
	return this->pos;
}

void Actor::Save( std::ostream & file ) const
{
	if( file.good() )
	{
		file << this->name << " ";
		file << this->pos.x << " ";
		file << this->pos.y << " ";
	}
}

void Actor::Load( std::istream & file )
{
	if( file.good() )
	{
		file >> this->name;
		file >> this->pos.x;
		file >> this->pos.y;
	}
}

void Actor::Spawn( const std::string & name, const Vector & pos )
{
	this->pos = pos;
	this->name = name;
}

void Actor::Despawn()
{
	this->name = "";
}

void Actor::Init( World * world )
{
	this->world = world;
}

void Actor::Deinit()
{
	this->world = nullptr;
}


Actor::Actor() :
	world(nullptr)
{
}

Actor::~Actor()
{
	this->world = nullptr;
}

#endif

