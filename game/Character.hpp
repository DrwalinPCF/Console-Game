
#ifndef CHARACTER_H
#define CHARACTER_H

#include "../engine/Actor.h"
#include "../engine/Drawer.hpp"
#include "../engine/Map.h"
#include "../engine/World.h"
#include "Projectile.h"

class Character : public Actor
{
protected:
	
	int maxHp;
	int hp;
	
	int attackCooldown;
	
	Vector direction;
	
public:
	
	void Shoot()
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
	
	void Attack()
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
	
	void DamageAbsorb( int dmg )
	{
		this->hp -= dmg;
	}
	
	int GetHP() const
	{
		return this->hp;
	}
	
	int GetMaxHP() const
	{
		return this->maxHp;
	}
	
	virtual bool IsWalkable() const override
	{
		return false;
	}
	
	virtual bool NeedTick() const override
	{
		return true;
	}
	
	virtual void Draw( unsigned currentSecond, class Drawer * drawer ) override
	{
		drawer->Draw( Vector(0,0), 'C' );
	}
	
	virtual unsigned Tick() override
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
		
		return 40;
	}
	
	virtual void Save( std::ostream & file ) const override
	{
		Actor::Save( file );
		file << this->hp << " ";
		file << this->maxHp << " ";
		file << this->attackCooldown << " ";
		file << this->direction.x << " ";
		file << this->direction.y << " ";
	}
	
	virtual void Load( std::istream & file ) override
	{
		Actor::Load( file );
		file >> this->hp;
		file >> this->maxHp;
		file >> this->attackCooldown;
		file >> this->direction.x;
		file >> this->direction.y;
	}
	
	virtual void Spawn( const std::string & name, const Vector & pos, const Vector & size ) override
	{
		Actor::Spawn( name, pos, size );
		this->maxHp = 100;
		this->hp = 100;
		this->direction = Vector( 1, 0 );
		this->attackCooldown = 0;
	}
	
	virtual void Despawn() override
	{
		Actor::Despawn();
	}
	
	virtual void Init( class World * world ) override
	{
		Actor::Init( world );
	}
	
	virtual void Deinit() override
	{
		Actor::Deinit();
	}
	
	
	virtual std::string GetTypeName() const override
	{
		return "Character";
	}
	
	virtual Actor * Make() const override
	{
		return Allocate<Character>();
	}
	
	virtual ~Character() override
	{
	}
	
	Character()
	{
		this->attackCooldown = 0;
	}
};

#endif

