
#ifndef UTILITY_CPP
#define UTILITY_CPP

#include "Utility.hpp"

std::ofstream DBGFL( "Game.dbg.log" );
std::map < void*, MEMORYSTRUCT > * DEBUG_MEMORY_USED = new std::map < void*, MEMORYSTRUCT >();

#include <windows.h>

bool IsKeyDown( int keyId )
{
	return GetAsyncKeyState( keyId ) & 0x8000;
}

#endif

