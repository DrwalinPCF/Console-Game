
#ifndef DRAW_MENU_CPP
#define DRAW_MENU_CPP

#include "../engine/Utility.hpp"

#include "World2.hpp"

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
			this->Save( in[1] );
		}
		else if( in[0] == "load" && in.size() > 1 )
		{
			this->Load( in[1] );
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

