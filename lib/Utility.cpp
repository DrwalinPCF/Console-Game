
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

std::string GetLastErrorAsString()
{
    DWORD errorMessageID = GetLastError();
    
    if( errorMessageID == 0 )
        return std::string();
    
    LPSTR messageBuffer = NULL;
    size_t size = FormatMessageA( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL );
    std::string message( messageBuffer, size );
    LocalFree(messageBuffer);
    
    return message;
}


namespace UtilityCPP
{
	HWND consoleHWND = GetConsoleWindow();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFO font;
	unsigned updateCooldown = 0;
};

/*
	returns mouse position in console output coordinate system
*/
Vector GetMousePosition()
{
	if( UtilityCPP::updateCooldown < clock() )
	{
		UtilityCPP::font.dwFontSize.X = 8;
		UtilityCPP::font.dwFontSize.Y = 8;
		GetCurrentConsoleFont( UtilityCPP::hConsole, false, &UtilityCPP::font );
		UtilityCPP::updateCooldown = clock() + 3000;
	}
	
	POINT globalCursor;
	GetCursorPos( &globalCursor );
	if( ScreenToClient( UtilityCPP::consoleHWND, &globalCursor ) )
	{
		globalCursor.x /= UtilityCPP::font.dwFontSize.X;
		globalCursor.y /= UtilityCPP::font.dwFontSize.Y;
		return Vector( globalCursor.x, globalCursor.y );
	}
	
	return Vector(-10000,-10000);
}

#endif

