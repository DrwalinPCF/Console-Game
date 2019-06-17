
#ifndef STRING_GETTER_CPP
#define STRING_GETTER_CPP

#include "World2.h"

#include <conio.h>

std::string StringGetter::GetString( Window * window )
{
	if( this->reset )
	{
		this->input = "";
		this->input.reserve( 1000 );
		this->x = window->GetCursorPos().x;
		this->y = window->GetCursorPos().y;
		this->reset = false;
	}
	
	while( true )
	{
		printf( "\n %i", (int) getch() );
	}
	
	if( kbhit() )
	{
		int ch = getch();
		
		switch( ch )
		{
		case '~':
			return "continue";
			
		case 13:
			this->reset = true;
			return this->input;
		
		case -32:
			if( getch() != 83 )
				break;
		case 8:
			if( this->input.size() > 0 )
			{
				this->input.resize( this->input.size() - 1 );
				--(this->x);
				window->PutChar( Vector(this->x, this->y), ' ' );
			}
			break;
			
		default:
			this->input.push_back( ch );
			window->PutChar( Vector(this->x, this->y), this->input.back() );
			++(this->x);
		}
	}
	
	return "";
}

StringGetter::StringGetter()
{
	this->reset = true;
}

#endif

