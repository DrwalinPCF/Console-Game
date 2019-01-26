
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
	
	float hp;
	float maxHp;
	
	int attackCooldown;
	
	Vector direction;
	
public:
	
	void Shoot()
	{
		if( this->attackCooldown > 250 )
		{
			Projectile * projectile = Allocate<Projectile>();
			projectile->Init( this->map );
			
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
			
			projectile->Spawn( this->map->GetWorld()->GetNewUniqueActorName(),
				projectileStartPosition, Vector(1,1) );
			
			this->map->GetWorld()->AddActor( projectile );
			projectile->SetVelocity( this->direction, 20, 311*10 );
			this->attackCooldown = 0;
		}
	}
	
	void Attack()
	{
		if( this->attackCooldown > 250 )
		{
			std::set<Actor*> targets;
			this->map->GetActors( this->GetPos()-Vector(1,1), this->GetPos()+this->GetSize(), {this}, targets );
			for( auto it = targets.begin(); it != targets.end(); ++it )
			{
				Character * ch = dynamic_cast<Character*>(*it);
				if( ch != nullptr )
				{
					ch->DamageAbsorb( 31.1f );
				}
			}
			this->attackCooldown = 0;
		}
	}
	
	void DamageAbsorb( float dmg )
	{
		this->hp -= dmg;
	}
	
	float GetHP() const
	{
		return this->hp;
	}
	
	float GetMaxHP() const
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
	
	virtual void Draw( unsigned deltaTime, class Drawer * drawer ) override
	{
		drawer->Draw( Vector(0,0), 'C' );
	}
	
	virtual void Tick( unsigned deltaTime ) override
	{
		if( this->hp <= 0.0f )
		{
			//death
			if( this->GetName() != "Player" )
			{
				this->map->GetWorld()->QueueRemoveActor( this->GetName() );
				this->Despawn();
			}
			else
			{
				
			}
		}
		else if( this->hp < this->maxHp )
		{
			this->hp += float(deltaTime) * 0.0002f;
			if( this->hp > this->maxHp )
				this->hp = this->maxHp;
		}
		else if( this->hp > this->maxHp )
		{
			this->hp -= float(deltaTime) * 0.01f;
			if( this->hp < this->maxHp )
				this->hp = this->maxHp;
		}
		
		if( this->attackCooldown < 0 )
			this->attackCooldown = 0;
		this->attackCooldown += deltaTime;
	}
	
	virtual void Save( std::ofstream & file ) const override
	{
		Actor::Save( file );
		file << this->hp << " ";
		file << this->maxHp << " ";
		file << this->attackCooldown << " ";
		file << this->direction.x << " ";
		file << this->direction.y << " ";
	}
	
	virtual void Load( std::ifstream & file ) override
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
		Character::Despawn();
	}
	
	virtual void Init( class Map * map ) override
	{
		Actor::Init( map );
	}
	
	virtual void Deinit() override
	{
		Actor::Deinit();
	}
	
	
	virtual std::string GetTypeName() override
	{
		return "Character";
	}
	
	virtual Actor * Make() override
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

