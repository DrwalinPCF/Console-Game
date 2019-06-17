
#ifndef DRAWER_CPP
#define DRAWER_CPP

#include "Drawer.hpp"

#include "../engine/Utility.hpp"

void Drawer::Preprocess()
{
}

void Drawer::SetCurrentPos( const Vector & pos )
{
	this->currentLocalPos = pos;
}

Vector Drawer::GetCurrentPos() const
{
	return this->currentLocalPos;
}

void Drawer::SetWindow( Window * win_ )
{
	this->win = win_;
	this->UpdateSize();
}

Drawer::Drawer()
{
	this->win = nullptr;
	this->w = 0;
	this->h = 0;
	this->rawData = NULL;
	this->data = NULL;
	this->bytes = 0;
}

Drawer::~Drawer()
{
	if( this->rawData )
		Free( this->rawData );
	if( this->data )
		Free( this->data );
}

#endif

