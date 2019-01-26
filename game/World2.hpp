
#ifndef WORLD_2_HPP
#define WORLD_2_HPP

#include "Player.hpp"

#include "../engine/World.h"
#include "../engine/Drawer.hpp"

#include <cstdlib>
#include <ctime>

#include <vector>
#include <string>

#include <conio.h>

class StringGetter
{
private:
	
	std::string input;
	int x;
	int y;
	bool reset;
	
public:
	
	std::string GetString( Window * window )
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
	
	StringGetter()
	{
		reset = true;
	}
};

std::vector < std::string > SubdivideString( const std::string & str )
{
	std::vector < std::string > ret;
	unsigned i=0, b=0, e=0;
	
	for( ; i < str.size(); ++i )
	{
		if( str[i] == '\"' || str[i] == '\'' )
		{
			if( e > b )
			{
				if( e > str.size() )
					e = str.size();
				ret.emplace_back( str.substr( b, e-b ) );
			}
			b = i+1;
			e = i+1;
			
			if( i+1 < str.size() )
			{
				for( ++i; i < str.size(); ++i )
				{
					if( str[i] == '\"' || str[i] == '\'' )
					{
						break;
					}
					else
					{
						e = i+1;
					}
				}
				
				if( e > b )
				{
					if( e > str.size() )
						e = str.size();
					ret.resize( ret.size() + 1 );
					ret.back() = str.substr( b, e-b );
				}
				e = i+1;
				b = i+1;
			}
			else
			{
				return ret;
			}
		}
		else if( str[i] == ' ' )
		{
			if( e > b )
			{
				if( e > str.size() )
					e = str.size();
				ret.resize( ret.size() + 1 );
				ret.back() = str.substr( b, e-b );
			}
			e = i+1;
			b = i+1;
		}
		else
		{
			e = i+1;
		}
	}
	
	if( e > b )
	{
		if( e > str.size() )
			e = str.size();
		ret.resize( ret.size() + 1 );
		ret.back() = str.substr( b, e-b );
	}
	
	return ret;
}

class World2 : public World
{
private:
	
	unsigned menuType;
	StringGetter stringGetter;
	
public:
	
	enum MenuTypes
	{
		NONE,
		MAIN_MENU,
		
		DEV_CONSOLE
	};
	
	void BeginDrawingMenu( MenuTypes menu )
	{
		this->menuType = menu;
		this->drawMenu = true;
		this->updateTick = false;
		
		this->guiScr->Clear();
		this->guiScr->Update();
		this->mapScr->Clear();
		this->mapScr->Update();
		
		while( kbhit() ) getch();
	}
	
	void DrawDeveloperConsole( Window * window )
	{
		std::vector < std::string > in = SubdivideString( this->stringGetter.GetString( window ) );
		
		if( in.size() > 0 )
		{
			if( in[0] == "help" )
			{
				window->Print( "\n To exit developer console, type: continue" );
			}
			else if( in[0] == "continue" || in[0] == "exit" || in[0] == "quit" )
			{
				this->drawMenu = false;
				this->updateTick = true;
				window->Clear();
				while( kbhit() ) getch();
			}
			else if( in[0] == "save" && in.size() > 1 )
			{
				this->Save( in[1] );
			}
			else if( in[0] == "load" && in.size() > 1 )
			{
				this->Load( in[1] );
			}
			window->Print( "\n" );
		}
	}
	
	virtual void DrawMenu( Window * window ) override
	{
		unsigned i;
		
		switch( this->menuType )
		{
		case MenuTypes::NONE:
			this->drawMenu = false;
			this->updateTick = true;
			window->Clear();
			break;
			
		case MenuTypes::MAIN_MENU:
			this->drawMenu = false;
			this->updateTick = true;
			window->Clear();
			break;
			
		case MenuTypes::DEV_CONSOLE:
			this->DrawDeveloperConsole( window );
			break;
		}
	}
	
	virtual void DrawGUI( Window * window ) override
	{
		auto it = this->actors.find( "Player" );
		if( it != this->actors.end() )
		{
			Character * player = dynamic_cast<Character*>(it->second);
			if( player )
			{
				window->Print( Vector( 1, 1 ), "Player:" );
				window->Print( Vector( 5, 2 ), "Hp: %0.4f / %0.3f", player->GetHP(), player->GetMaxHP() );
			}
			else
			{
				window->Print( Vector( 1, 1 ), "Actor named \"Player\" is not of type Character" );
			}
		}
		else
		{
			window->Print( Vector( 1, 1 ), "Cannot find actor with name \"Player\"" );
		}
		
		window->Print( Vector( 0, 4 ), " " );
		
		static int ticks = 0;
		++ticks;
		window->Print( "\n fps = %i / %f = %f", ticks, float(clock())*0.001f, float(ticks) / (float(clock())*0.001f) );
		
		window->Print( "\n Number of Actors: %lli ", this->GetNumberOfActors() );
	}
	
	World2()
	{
		this->menuType = MenuTypes::NONE;
	}
	
	~World2()
	{
	}
};

#endif

