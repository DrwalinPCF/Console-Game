
#ifndef BLOCK_CPP
#define BLOCK_CPP

#include "Block.h"

bool Block::IsWalkable() const
{
	return false;
}

bool Block::NeedTick() const
{
	return false;
}

unsigned char Block::GetOpaqueness() const
{
	return 255;
}

bool Block::IsStaticallyDrawn() const
{
	return true;
}

void Block::Draw( unsigned currentSecond, class Drawer * drawer )
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

unsigned Block::Tick()
{
	return 10000;
}

void Block::Save( std::ostream & file ) const
{
	Actor::Save( file );
}

void Block::Load( std::istream & file )
{
	Actor::Load( file );
}

void Block::Spawn( const std::string & name, const Vector & pos, const Vector & size )
{
	Actor::Spawn( name, pos, size );
}

void Block::Despawn()
{
	Actor::Despawn();
}

void Block::Init( class World * world )
{
	Actor::Init( world );
}

void Block::Deinit()
{
	Actor::Deinit();
}


std::string Block::GetTypeName() const
{
	return "Block";
}

Actor * Block::Make() const
{
	return Allocate<Block>();
}

Block::~Block()
{
}

Block::Block()
{
}

#endif

