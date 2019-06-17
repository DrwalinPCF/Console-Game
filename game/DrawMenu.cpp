
#ifndef DRAW_MENU_CPP
#define DRAW_MENU_CPP

#include "../engine/Utility.hpp"

#include "World2.h"

#include <conio.h>

void World2::BeginDrawingMenu( MenuTypes menu )
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

void World2::DrawDeveloperConsole( Window * window )
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
			if( in.size() > 1 )
			{
				if( this->Save( in[1] ) )
				{
					window->Print( "\n Saved correctly" );
				}
				else
				{
					window->Print( "\n Couldn't be saved correctly" );
				}
				
				if( in.size() > 2 )
				{
					window->Print( "\n Too many arguments" );
				}
			}
			else
			{
				window->Print( "\n Give file name to save as argument:\n     save <file_name>" );
			}
		}
		else if( in[0] == "load" )
		{
			if( in.size() > 1 )
			{
				if( this->Load( in[1] ) )
				{
					window->Print( "\n Loaded correctly" );
				}
				else
				{
					window->Print( "\n Couldn't be loaded correctly" );
				}
				
				if( in.size() > 2 )
				{
					window->Print( "\n Too many arguments" );
				}
			}
			else
			{
				window->Print( "\n Give file name to load as argument:\n     save <file_name>" );
			}
		}
		else if( in[0] == "spawn" )
		{
			if( in.size() >= 7 )
			{
				std::string typeName = in[1];
				const Actor * type = this->GetRegisteredActorByTypeName( typeName );
				if( type == NULL )
				{
					window->Print( "\n No registered actor type: \"%s\"", typeName.c_str() );
				}
				else
				{
					std::string actorName = in[2];
					int x, y;
					int sx, sy;
					x = atoi(in[3].c_str());
					y = atoi(in[4].c_str());
					sx = atoi(in[5].c_str());
					sy = atoi(in[6].c_str());
					if( this->actors.find( actorName ) == this->actors.end() )
					{
						this->AddActor( actorName, Vector(x,y), Vector(sx,sy), type->Make() );
					}
					else
					{
						window->Print( "\n Actor with name already exists: \"%s\"", actorName.c_str() );
					}
				}
				
				if( in.size() > 7 )
				{
					window->Print( "\n Too many arguments" );
				}
			}
		}
		window->Print( "\n" );
	}
}

void World2::DrawMenu( Window * window )
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

#endif

