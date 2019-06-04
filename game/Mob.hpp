
#ifndef MOB_HPP
#define MOB_HPP

#include "Character.hpp"
#include "../engine/Drawer.hpp"

class Mob : public Character
{
protected:
	
	int movementCooldown;
	
public:
	
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
		long long x, y;
		for( x = 0; x < size.x; ++x )
		{
			for( y = 0; y < size.y; ++y )
			{
				drawer->Draw( Vector(x,y), '_', FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_RED );
			}
		}
	}
	
	virtual unsigned Tick() override
	{
		unsigned ret = Character::Tick();
		if( this->movementCooldown <= this->world->GetCurrentMoment() )
		{
			this->Move( Vector( (rand()%3)-1, (rand()%3)-1 ) );
			this->movementCooldown = this->world->GetCurrentMoment() + 250;
		}
		return ret;
	}
	
	virtual void Save( std::ofstream & file ) const override
	{
		Character::Save( file );
		file << this->movementCooldown << " ";
	}
	
	virtual void Load( std::ifstream & file ) override
	{
		Character::Load( file );
		file >> this->movementCooldown;
	}
	
	virtual void Spawn( const std::string & name, const Vector & pos, const Vector & size ) override
	{
		Character::Spawn( name, pos, size );
	}
	
	virtual void Despawn() override
	{
		Character::Despawn();
	}
	
	virtual void Init( class World * world ) override
	{
		Character::Init( world );
	}
	
	virtual void Deinit() override
	{
		Character::Deinit();
	}
	
	
	virtual std::string GetTypeName() const override
	{
		return "Mob";
	}
	
	virtual Actor * Make() const override
	{
		return Allocate<Mob>();
	}
	
	virtual ~Mob() override
	{
	}
	
	Mob()
	{
		this->movementCooldown = 0;
	}
};

#endif

