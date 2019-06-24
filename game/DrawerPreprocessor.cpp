
#ifndef DRAWER_PREPROCESSOR_CPP
#define DRAWER_PREPROCESSOR_CPP

#include "DrawerPreprocessor.h"

#include <cmath>
	
void DrawerPreprocessor::ScanOneLine( const Vector & start, const Vector & end, loctype distance )
{
	loctype multiplier = 24;
	Vector dir = (end-start);
	loctype l = sqrt( ((dir.x*dir.x) + (dir.y*dir.y)) * multiplier * multiplier );
	dir = ( dir * multiplier * multiplier ) / l;
	
	Vector p, prev = start;
	for( int i = 1; i < distance*multiplier; ++i )
	{
		p = start + ((dir * i)/(multiplier*multiplier));
		if( p != prev )
		{
			if( p.x < 0 || p.y < 0 || p.x >= this->w || p.y >= this->h )
				return;
			
			DrawerPointData & previousData = this->data[prev.x][prev.y];
			DrawerPointData & currentData = this->data[p.x][p.y];
			
			unsigned char t = currentData.viewDistance;
			
			if( previousData.viewDistance <= currentData.opaqueness )
			{
				if( t != 0 )
					currentData.viewDistance = t;
				else
					return;
			}
			
			currentData.viewDistance = previousData.viewDistance - currentData.opaqueness;
			
			if( currentData.viewDistance <= 1 )
			{
				if( t != 0 )
					currentData.viewDistance = t;
				else
					return;
			}
			
			currentData.viewDistance -= 1;
			
			if( currentData.viewDistance < t )
				currentData.viewDistance = t;
			
			prev = p;
		}
	}
}

void DrawerPreprocessor::Preprocess()
{
	Drawer::Preprocess();
//	DEBUG( std::to_string(point.x) + ", " + std::to_string(point.y) );
	
	this->data[this->playerPos.x][this->playerPos.y].viewDistance = 255;
	
	Vector end(0,0);
	for( ; end.x+1 < this->w; ++end.x )
		this->ScanOneLine( this->playerPos, end, 32 );
	for( ; end.y+1 < this->h; ++end.y )
		this->ScanOneLine( this->playerPos, end, 32 );
	for( ; end.x > 0; --end.x )
		this->ScanOneLine( this->playerPos, end, 32 );
	for( ; end.y > 0; --end.y )
		this->ScanOneLine( this->playerPos, end, 32 );
	
	char sign;
	WORD color;
	int i, j;
	
	for( i = 0; i < this->w; ++i )
	{
		for( j = 0; j < this->h; ++j )
		{
			int sum = (int)this->data[i][j].viewDistance;
			int se = 0;
			
			if( this->data[i][j].viewDistance )
				se = 32;
			
			if( i > 0 )
			{
				sum += (int)this->data[i-1][j].viewDistance;
				if( this->data[i-1][j].viewDistance )
					se += 5;
			}
			if( j > 0 )
			{
				sum += (int)this->data[i][j-1].viewDistance;
				if( this->data[i][j-1].viewDistance )
					se += 5;
			}
			if( i+1 < this->w )
			{
				sum += (int)this->data[i+1][j].viewDistance;
				if( this->data[i+1][j].viewDistance )
					se += 5;
			}
			if( j+1 < this->h )
			{
				sum += (int)this->data[i][j+1].viewDistance;
				if( this->data[i][j+1].viewDistance )
					se += 5;
			}
				
			if( i > 0 && j > 0 )
			{
				//sum += (int)this->data[i-1][j-1].viewDistance >> 2;
				if( this->data[i-1][j-1].viewDistance >> 2 )
					se += 1;
			}
			if( i > 0 && j+1 < this->h )
			{
				//sum += (int)this->data[i-1][j+1].viewDistance >> 2;
				if( this->data[i-1][j+1].viewDistance >> 2 )
					se += 1;
			}
			if( i+1 < this->w && j > 0 )
			{
				//sum += (int)this->data[i+1][j-1].viewDistance >> 2;
				if( this->data[i+1][j-1].viewDistance >> 2 )
					se += 1;
			}
			if( i+1 < this->w && j+1 < this->h )
			{
				//sum += (int)this->data[i+1][j+1].viewDistance >> 2;
				if( this->data[i+1][j+1].viewDistance >> 2 )
					se += 1;
			}
			
			if( sum == 0 || se < 4 )//(int)this->data[i][j].viewDistance == 0 )//sum == 0 || se == 4 )
			{
				if( (this->data[i][j].flags & DRAWER_FLAGS::STATIC_DRAW ) == 0 )
				{
					this->win->PutChar( Vector(i,j), ' ', BACKGROUND_INTENSITY );
				}
				else
				{
					this->win->GetChar( Vector(i,j), sign, color );
					this->win->PutChar( Vector(i,j), sign, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN /*| FOREGROUND_INTENSITY*/  |  /*BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | */BACKGROUND_INTENSITY );
				}
			}
		}
	}
}

DrawerPreprocessor::DrawerPreprocessor()
{
}

DrawerPreprocessor::~DrawerPreprocessor()
{
}

#endif

