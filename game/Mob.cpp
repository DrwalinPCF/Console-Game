
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
	drawer->Draw( Vector(0,0), '_', FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_RED );
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

void Mob::Spawn( const std::string & name, const Vector & pos )
{
	Character::Spawn( name, pos );
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

