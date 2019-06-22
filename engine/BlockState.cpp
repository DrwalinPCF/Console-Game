
#ifndef BLOCK_STATE_CPP
#define BLOCK_STATE_CPP

#include "BlockState.h"

#include "Drawer.hpp"

BlockState & BlockState::GetPureReference()
{
	static BlockState pureStateStatic;
	return pureStateStatic;
}


void BlockState::Draw( Drawer * drawer )
{
	if( this->data )
		drawer->Draw( Vector(0,0), '#', FOREGROUND_INTENSITY );
}

bool BlockState::IsWalkable() const
{
	return this->data == 0;
}

unsigned char BlockState::GetOpaqueness() const
{
	return this->data ? 255 : 0;
}

bool BlockState::IsStaticallyDrawn() const
{
	return true;
}

BlockState::BlockState()
{
	this->data = 0;
}

BlockState::BlockState( unsigned char data )
{
	this->data = data;
}

BlockState::~BlockState()
{
	this->data = 0;
}

#endif

