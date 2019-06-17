
#ifndef WINDOW_H
#define WINDOW_H

#include "Vector.hpp"
#include <cstdarg>

#include <windows.h>

class Window
{
public:
	
	HANDLE hOutput;
	
	CHAR_INFO * consoleBuffer;
	int x, y;
	int w, h;
	
	int curretnPosInBuffer;
	
	COORD bufferSize;
	COORD bufferCoord;
	SMALL_RECT consoleWriteArea;
	
	void GetConsoleSize( Vector & size );
	void PutChar( Vector pos, char sign, WORD color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE );
	void GetChar( Vector pos, char & sign, WORD & color );
	
	void RollUp();
	
	void vPrint( Vector pos, WORD color, const char * format, va_list & vargs );
	void Print( Vector pos, WORD color, const char * format, ... );
	void Print( Vector pos, const char * format, ... );
	void Print( WORD color, const char * format, ... );
	void Print( const char * format, ... );
	
	Vector GetCursorPos() const;
	
	void Update();
	void Clear();
	
	void Destroy();
	void Init( float minx, float miny, float maxx, float maxy );
	
	Window();
	~Window();
};

#endif

