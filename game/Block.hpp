
#ifndef BLOCK_H
#define BLOCK_H

#include "../engine/Actor.h"
#include "../engine/Drawer.hpp"

class Block : public Actor
{
protected:
	
	
	
public:
	
	virtual bool IsWalkable() const override
	{
		return false;
	}
	
	virtual bool NeedTick() const override
	{
		return false;
	}
	
	virtual void Draw( unsigned currentSecond, class Drawer * drawer ) override
	{
		long long x, y;
		for( x = 0; x < size.x; ++x )
		{
			for( y = 0; y < size.y; ++y )
			{
				drawer->Draw( Vector(x,y), '#' );
			}
		}
	}
	
	virtual unsigned Tick() override
	{
		return 10000;
	}
	
	virtual void Save( std::ostream & file ) const override
	{
		Actor::Save( file );
	}
	
	virtual void Load( std::istream & file ) override
	{
		Actor::Load( file );
	}
	
	virtual void Spawn( const std::string & name, const Vector & pos, const Vector & size ) override
	{
		Actor::Spawn( name, pos, size );
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
		return "Block";
	}
	
	virtual Actor * Make() const override
	{
		return Allocate<Block>();
	}
	
	virtual ~Block() override
	{
	}
	
	Block()
	{
	}
};

#endif

