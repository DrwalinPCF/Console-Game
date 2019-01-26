
#ifndef STRING_GETTER_CPP
#define STRING_GETTER_CPP

#include "World2.hpp"

std::string StringGetter::GetString( Window * window )
{
	if( reset )
	{
		input = "";
		input.reserve( 1000 );
		this->x = window->GetCursorPos().x;
		this->y = window->GetCursorPos().y;
		reset = false;
	}
	
	if( kbhit() )
	{
		int ch = getch();
		
		switch( ch )
		{
		case 13:
			reset = true;
			return input;
			break;
		
		case -32:
			if( getch() != 83 )
				break;
		case 8:
			if( input.size() > 0 )
			{
				input.resize( input.size() - 1 );
				--x;
				window->PutChar( Vector(x, y), ' ' );
			}
			break;
			
		default:
			input.push_back( ch );
			window->PutChar( Vector(x, y), input.back() );
			++x;
		}
	}
	
	return "";
}

StringGetter::StringGetter()
{
	reset = true;
}

#endif

