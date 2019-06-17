
#ifndef MOB_HPP
#define MOB_HPP

#include "Mob.h"

#include "../engine/World.h"

bool Mob::IsWalkable() const
{
	return false;
}

bool Mob::NeedTick() const
{
	return true;
}

void Mob::Draw( unsigned deltaTime, class Drawer * drawer )
{
	long long x, y;
	for( x = 0; x < size.x; ++x )
	{
		for( y = 0; y < size.y; ++y )
		{
			drawer->Draw( Vector(x,y), '_', FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_RED );
		}
	}
}

unsigned Mob::Tick()
{
	unsigned ret = Character::Tick();
	if( this->movementCooldown <= this->world->GetCurrentMoment() )
	{
		this->Move( Vector( (rand()%3)-1, (rand()%3)-1 ) );
		this->movementCooldown = this->world->GetCurrentMoment() + 250;
	}
	return ret;
}

void Mob::Save( std::ostream & file ) const
{
	Character::Save( file );
	file << this->movementCooldown << " ";
}

void Mob::Load( std::istream & file )
{
	Character::Load( file );
	file >> this->movementCooldown;
}

void Mob::Spawn( const std::string & name, const Vector & pos, const Vector & size )
{
	Character::Spawn( name, pos, size );
}

void Mob::Despawn()
{
	Character::Despawn();
}

void Mob::Init( class World * world )
{
	Character::Init( world );
}

void Mob::Deinit()
{
	Character::Deinit();
}


std::string Mob::GetTypeName() const
{
	return "Mob";
}

Actor * Mob::Make() const
{
	return Allocate<Mob>();
}

Mob::~Mob()
{
}

Mob::Mob()
{
	this->movementCooldown = 0;
}

#endif

