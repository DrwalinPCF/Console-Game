
#ifndef DRAWER_HPP
#define DRAWER_HPP

#include "Vector.hpp"
#include "Window.hpp"

class Drawer
{
private:
	
	Window * win;
	Vector currentLocalPos;
	
public:
	
	inline void Redraw()
	{
		if( this->win )
			this->win->Update();
	}
	
	inline void Draw( Vector pos, char sign, WORD color = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN )
	{
		this->win->PutChar( currentLocalPos + pos, sign, color );
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
	}
	
	Drawer()
	{
		this->win = nullptr;
	}
	
	~Drawer()
	{
	}
};

#endif

