
#ifndef WORLD_2_H
#define WORLD_2_H

#include <vector>
#include <string>

#include "../engine/World.h"
#include "../engine/Drawer.hpp"

class StringGetter
{
private:
	
	std::string input;
	int x;
	int y;
	bool reset;
	
public:
	
	std::string GetString( Window * window );
	StringGetter();
};

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
	
	void BeginDrawingMenu( MenuTypes menu );
	void DrawDeveloperConsole( Window * window );
	virtual void DrawMenu( Window * window ) override;
	
	virtual void DrawGUI( Window * window ) override;
	
	World2();
	~World2();
};

#include "StringGetter.cpp"
#include "DrawMenu.cpp"
#include "DrawGUI.cpp"

#endif

