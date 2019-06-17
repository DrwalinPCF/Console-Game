
#ifndef CHARACTER_CPP
#define CHARACTER_CPP

#include "../engine/World.h"
#include "Projectile.h"

#include "Character.h"

bool Character::IsWalkable() const
{
	return false;
}

bool Character::NeedTick() const
{
	return true;
}

unsigned char Character::GetOpaqueness() const
{
	return 8;
}

bool Character::IsStaticallyDrawn() const
{
	return false;
}

void Character::Shoot()
{
	if( this->attackCooldown <= this->world->GetCurrentMoment() )
	{
		Projectile * projectile = Allocate<Projectile>();
		projectile->Init( this->world );
		
		Vector projectileStartPosition = this->GetPos();
		if( this->direction.x < 0 )
			projectileStartPosition += Vector( -1, this->GetSize().y/2 );
		else if( this->direction.x > 0 )
			projectileStartPosition += Vector( this->GetSize().x, this->GetSize().y/2 );
		else if( this->direction.y < 0 )
			projectileStartPosition += Vector( this->GetSize().x/2, -1 );
		else if( this->direction.y > 0 )
			projectileStartPosition += Vector( this->GetSize().x/2, this->GetSize().y );
		else
			projectileStartPosition += Vector(-1,-1);
		
		projectile->Spawn( this->world->GetNewUniqueActorName(), projectileStartPosition, Vector(1,1) );
		
		this->world->AddActor( projectile );
		projectile->SetVelocity( this->direction, 100, (rand()%600)+2000 );
		this->attackCooldown = this->world->GetCurrentMoment() + 250;
	}
}

void Character::Attack()
{
	if( this->attackCooldown <= this->world->GetCurrentMoment() )
	{
		std::set<Actor*> targets;
		this->world->GetMap()->GetActors( this->GetPos()-Vector(1,1), this->GetPos()+this->GetSize(), {this}, targets );
		for( auto it = targets.begin(); it != targets.end(); ++it )
		{
			Character * ch = dynamic_cast<Character*>(*it);
			if( ch )
			{
				ch->DamageAbsorb( 31 );
			}
		}
		this->attackCooldown = this->world->GetCurrentMoment() + 250;
	}
}

void Character::DamageAbsorb( int dmg )
{
	this->hp -= dmg;
}

int Character::GetHP() const
{
	return this->hp;
}

int Character::GetMaxHP() const
{
	return this->maxHp;
}

void Character::Draw( unsigned currentSecond, class Drawer * drawer )
{
	drawer->Draw( Vector(0,0), 'C' );
}

unsigned Character::Tick()
{
	if( this->hp <= 0 )
	{
		//death
		if( this->GetName() != "Player" )
		{
			this->world->QueueRemoveActor( this->GetName() );
			this->Despawn();
			return 1000000;
		}
		else
		{
			
		}
	}
	
	return 110;
}

void Character::Save( std::ostream & file ) const
{
	Actor::Save( file );
	file << this->hp << " ";
	file << this->maxHp << " ";
	file << this->attackCooldown << " ";
	file << this->direction.x << " ";
	file << this->direction.y << " ";
}

void Character::Load( std::istream & file )
{
	Actor::Load( file );
	file >> this->hp;
	file >> this->maxHp;
	file >> this->attackCooldown;
	file >> this->direction.x;
	file >> this->direction.y;
}

void Character::Spawn( const std::string & name, const Vector & pos, const Vector & size )
{
	Actor::Spawn( name, pos, size );
	this->maxHp = 100;
	this->hp = 100;
	this->direction = Vector( 1, 0 );
	this->attackCooldown = 0;
}

void Character::Despawn()
{
	Actor::Despawn();
}

void Character::Init( class World * world )
{
	Actor::Init( world );
}

void Character::Deinit()
{
	Actor::Deinit();
}


std::string Character::GetTypeName() const
{
	return "Character";
}

Actor * Character::Make() const
{
	return Allocate<Character>();
}

Character::~Character()
{
}

Character::Character()
{
	this->attackCooldown = 0;
}

#endif

