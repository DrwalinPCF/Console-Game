
#ifndef DRAWER_HPP
#define DRAWER_HPP

#include "Vector.hpp"
#include "Window.hpp"

#include <vector>

enum DRAWER_FLAGS
{
	STATIC_DRAW = 1,
	DIRECTLY_IN_VIEW = 2,
	IN_VIEW = 4,
	QUEUED = 8,
	AFTER_PREPROCESS = 16
};

struct DrawerPointData
{
	unsigned char flags;
	//unsigned char light;
	unsigned char viewDistance;
	unsigned char opaqueness;
};

class Drawer
{
protected:
	
	Window * win;
	Vector currentLocalPos;
	
	int w, h, bytes;
	DrawerPointData * rawData;
	DrawerPointData ** data;
	
	unsigned char currentDrawingPointOpqueness;
	unsigned char opaqueness;
	
	Vector playerPos;
	
public:
	
	void SetPlayerPos( Vector playerPos )
	{
		this->playerPos = playerPos;
	}
	
	inline void UpdateSize()
	{
		if( this->w != this->win->w || this->h != this->win->h )
		{
			if( this->rawData )
				Free( this->rawData );
			if( this->data )
				Free( this->data );
			
			this->w = this->win->w;
			this->h = this->win->h;
			
			this->bytes = sizeof(DrawerPointData) * w * h;
			
			this->rawData = Allocate<DrawerPointData>( w * h );
			this->data = Allocate<DrawerPointData*>( w );
			
			for( int i = 0; i < this->w; ++i )
				this->data[i] = this->rawData + (this->w*i);
			
			memset( this->rawData, 0, this->bytes );
		}
	}
	
	inline void SetCurrentFlags( bool staticDraw, unsigned char opaqueness )
	{
		this->currentDrawingPointOpqueness = 0;
		this->currentDrawingPointOpqueness |= staticDraw ? STATIC_DRAW : 0;
		this->opaqueness = opaqueness;
	}
	
	virtual void Preprocess()
	{
	}
	
	inline void Redraw()
	{
		if( this->win )
		{
			this->Preprocess();
			this->win->Update();
		}
		memset( this->rawData, 0, this->bytes );
	}
	
	inline void Clear()
	{
		if( this->win )
		{
			this->win->Clear();
		}
	}
	
	inline void Draw( Vector pos, char sign, WORD color = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN )
	{
		Vector p = currentLocalPos + pos;
		if( p.x < 0 || p.y < 0 || p.x >= this->w || p.y >= this->h )
			return;
		
		this->win->PutChar( p, sign, color );
		
		this->UpdateSize();
		
		DrawerPointData * currentPoint = this->data[p.x] + p.y;
		currentPoint->flags |= this->currentDrawingPointOpqueness;
		currentPoint->opaqueness += this->opaqueness;
		if( currentPoint->opaqueness < this->opaqueness )
			currentPoint->opaqueness = 255;
	}
	
	inline loctype GetWinX() const
	{
		return this->win->x;
	}
	
	inline loctype GetWinY() const
	{
		return this->win->y;
	}
	
	inline Vector GetWinSize() const
	{
		return Vector( this->win->w, this->win->h );
	}
	
	void SetCurrentPos( const Vector & pos )
	{
		this->currentLocalPos = pos;
	}
	
	Vector GetCurrentPos() const
	{
		return this->currentLocalPos;
	}
	
	void SetWindow( Window * win_ )
	{
		this->win = win_;
		this->UpdateSize();
	}
	
	Drawer()
	{
		this->win = nullptr;
		this->w = 0;
		this->h = 0;
		this->rawData = NULL;
		this->data = NULL;
		this->bytes = 0;
	}
	
	~Drawer()
	{
		if( this->rawData )
			Free( this->rawData );
		if( this->data )
			Free( this->data );
	}
};

#endif

