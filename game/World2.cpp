
#ifndef WORLD2_CPP
#define WORLD2_CPP

#include "World2.h"

#include "../engine/Utility.hpp"
#include "DrawerPreprocessor.h"

World2::World2()
{
	Free( this->mapDrawer );
	this->mapDrawer = Allocate<DrawerPreprocessor>();
	this->mapDrawer->SetWindow( this->mapScr );
	this->menuType = MenuTypes::NONE;
}

World2::~World2()
{
}

#include "StringGetter.cpp"
#include "DrawMenu.cpp"
#include "DrawGUI.cpp"

#endif

