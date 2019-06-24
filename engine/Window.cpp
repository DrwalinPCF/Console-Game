
#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "../lib/Utility.hpp"

#include "Window.h"

#include <cstdio>

void Window::GetConsoleSize( Vector & size )
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo( GetStdHandle(STD_OUTPUT_HANDLE), &csbi );
	size.x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	size.y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void Window::PutChar( Vector pos, char sign, WORD color )
{
	if( pos.x >= 0 && pos.x < this->w && pos.y >= 0 && pos.y < this->h && this->consoleBuffer )
	{
		this->consoleBuffer[ ( pos.y * this->w ) + pos.x ].Char.AsciiChar = sign;
		this->consoleBuffer[ ( pos.y * this->w ) + pos.x ].Attributes = color;
	}
}

void Window::GetChar( Vector pos, char & sign, WORD & color )
{
	if( pos.x >= 0 && pos.x < this->w && pos.y >= 0 && pos.y < this->h && this->consoleBuffer )
	{
		sign = this->consoleBuffer[ ( pos.y * this->w ) + pos.x ].Char.AsciiChar;
		color = this->consoleBuffer[ ( pos.y * this->w ) + pos.x ].Attributes;
	}
}

void Window::RollUp()
{
	if( this->consoleBuffer != nullptr )
	{
		memmove( this->consoleBuffer, this->consoleBuffer + this->w, ( this->w * ( this->h - 1 ) ) * sizeof(CHAR_INFO) );
		int i = ( this->w * this->h ) - this->w;
		int max = this->w * this->h;
		for( ; i < max; ++i )
		{
			this->consoleBuffer[ i ].Char.AsciiChar = ' ';
			this->consoleBuffer[ i ].Attributes = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN;
		}
	}
}

void Window::vPrint( Vector pos, WORD color, const char * format, va_list & vargs )
{
	if( pos.x >= 0 && pos.x < this->w && pos.y >= 0 && pos.y < this->h && this->consoleBuffer )
	{
		char buf[8192];
		
		vsprintf( buf, format, vargs );
		
		int len = strlen( buf );
		int i, pi;
		int max = this->w * this->h;
		this->curretnPosInBuffer = pos.x + ( this->w * pos.y );
		char * ptr = buf;
		for( i = 0; i < len; ++i, ++ptr, ++(this->curretnPosInBuffer) )
		{
			switch( *ptr )
			{
			case 0:
				return;
				
			case '\n':
				this->curretnPosInBuffer /= this->w;
				this->curretnPosInBuffer += 1;
				this->curretnPosInBuffer *= this->w;
				break;
				
			case '\t':
				this->curretnPosInBuffer = (((((this->curretnPosInBuffer)%this->w)/4)+1)*4) + (this->w*((this->curretnPosInBuffer)/this->w));
				break;
				
			default:
				while( this->curretnPosInBuffer >= max )
				{
					RollUp();
					this->curretnPosInBuffer -= this->w;
				}
				this->consoleBuffer[this->curretnPosInBuffer].Char.AsciiChar = *ptr;
				this->consoleBuffer[this->curretnPosInBuffer].Attributes = color;
			}
		}
	}
}

void Window::Print( Vector pos, WORD color, const char * format, ... )
{
    va_list vargs;
    va_start( vargs, format );
    
    this->vPrint( pos, color, format, vargs );
    
	va_end( vargs );
}

void Window::Print( Vector pos, const char * format, ... )
{
    va_list vargs;
    va_start( vargs, format );
    
	this->vPrint( pos, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN, format, vargs );
	
	va_end( vargs );
}

void Window::Print( WORD color, const char * format, ... )
{
    va_list vargs;
    va_start( vargs, format );
    
	this->vPrint( this->GetCursorPos(), color, format, vargs );
	
	va_end( vargs );
}

void Window::Print( const char * format, ... )
{
    va_list vargs;
    va_start( vargs, format );
    
	this->vPrint( this->GetCursorPos(), FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN, format, vargs );
	
    va_end( vargs );
}

Vector Window::GetCursorPos() const
{
	return Vector( this->curretnPosInBuffer % this->w, this->curretnPosInBuffer / this->w );
}

void Window::Update()
{
	if( this->consoleBuffer )
	{
		WriteConsoleOutput( this->hOutput, this->consoleBuffer, this->bufferSize, this->bufferCoord, &(this->consoleWriteArea) );
	}
}

void Window::Clear()
{
	if( this->consoleBuffer )
	{
		int i = 0;
		int max = this->w * this->h;
		for( ; i < max; ++i )
		{
			this->consoleBuffer[ i ].Char.AsciiChar = ' ';
			this->consoleBuffer[ i ].Attributes = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN;
		}
	}
	this->curretnPosInBuffer = 0;
}

void Window::Destroy()
{
	if( this->consoleBuffer )
	{
		Free( this->consoleBuffer );
		this->consoleBuffer = nullptr;
	}
}

void Window::Init( float minx, float miny, float maxx, float maxy )
{
	this->Destroy();
	
	this->curretnPosInBuffer = 0;
	
	Vector beg, size, end;
	Vector wsize;
	this->GetConsoleSize( wsize );
	if( wsize.x > 400 )
		wsize.x = 400;
	if( wsize.y > 400 )
		wsize.y = 400;
	
	beg.x = int( minx * wsize.x );
	beg.y = int( miny * wsize.y );
	end.x = int( maxx * wsize.x );
	end.y = int( maxy * wsize.y );
	size = end - beg;
	
	this->bufferSize = { (short)size.x, (short)size.y };
	this->bufferCoord = { 0, 0 };
	this->consoleWriteArea = { (short)beg.x, (short)beg.y, (short)((short)end.x - (short)1), (short)((short)end.y - (short)1) };
	
	this->w = size.x;
	this->h = size.y;
	this->x = beg.x;
	this->y = beg.y;
	
	this->consoleBuffer = Allocate<CHAR_INFO>(this->w * this->h);
	this->hOutput = GetStdHandle( STD_OUTPUT_HANDLE );
	
	this->Clear();
}

Window::Window()
{
	this->consoleBuffer = nullptr;
}

Window::~Window()
{
	this->Destroy();
}

#endif

