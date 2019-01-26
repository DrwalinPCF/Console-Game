
#ifndef WORLD_CPP
#define WORLD_CPP

#include <windows.h>

#include <fstream>
#include <ctime>

#include "World.h"
#include "Actor.h"

#include "Utility.hpp"

long long World::GetNumberOfActors() const
{
	return this->actors.size();
}

std::string World::GetNewUniqueActorName() const
{
	std::string name = GetDateString();
	unsigned long long counter = 0;
	std::string ret;
	do
	{
		ret = name + std::to_string( counter );
		++counter;
	}
	while( this->actors.find(ret) != this->actors.end() );
	return ret;
}

void World::QueueRemoveActor( std::string name )
{
	this->queueActorsToRemove.emplace_back( name );
}

Map * World::GetMap()
{
	return this->map;
}

bool World::CenterAtActor( const std::string & name )
{
	this->centeredActorName = name;
	if( this->actors.find( name ) != this->actors.end() )
		return true;
	return false;
}

std::string World::GetNameOfActorType( Actor * actor ) const
{
	std::map < std::string, Actor* > equal;
	for( auto it = registeredActors.begin(); it != this->registeredActors.end(); ++it )
	{
		if( it->second->GetTypeName() == actor->GetTypeName() )
		{
			equal[it->first] = it->second;
		}
	}
	
	if( equal.size() >= 1 )
		return equal.begin()->first;
	return "";
}

void World::AddActor( Actor * ptr )
{
	auto it = this->actors.find( ptr->GetName() );
	if( it == this->actors.end() )
	{
		this->actors[ ptr->GetName() ] = ptr;
		this->map->AddActor( ptr );
	}
}

void World::AddActor( std::string name, Vector pos, Vector size, Actor * ptr )
{
	auto it = this->actors.find( name );
	if( it == this->actors.end() )
	{
		ptr->Init( this->map );
		ptr->Spawn( name, pos, size );
		this->actors[ name ] = ptr;
		this->map->AddActor( ptr );
	}
}

void World::DestroyActor( const std::string & name )
{
	auto it = this->actors.find( name );
	if( it != this->actors.end() )
	{
		it->second->Deinit();
		this->map->RemoveActor( it->second );
		Free( it->second );
		//delete it->second;
		this->actors.erase( it );
	}
}

void World::DestroyActor( Actor * actor )
{
	if( actor )
		this->DestroyActor( actor->GetName() );
}

void World::Exit()
{
	this->end = true;
}

bool World::RegisterType( Actor * constructer )
{
	if( constructer && constructer->GetTypeName() != "" )
	{
		if( this->registeredActors.find( constructer->GetTypeName() ) != this->registeredActors.end() )
			return false;
		this->registeredActors[ constructer->GetTypeName() ] = constructer;
		return true;
	}
	return false;
}

bool World::Save( const std::string & fileName ) const
{
	std::ofstream file( fileName );
	if( file.good() )
	{
		for( auto it = this->actors.begin(); it != this->actors.end(); ++it )
		{
			file << "\n" << this->GetNameOfActorType( it->second ) << "\n{\n";
			it->second->Save( file );
			file << "\n}\n";
		}
		return true;
	}
	return false;
}

bool World::AppendLoadWithoutOverlapp( const std::string & fileName )
{
	std::ifstream file( fileName );
	
	while( !file.eof() )
	{
		std::string typeName, temp;
		file >> typeName;
		file >> temp;
		auto it = this->registeredActors.find( typeName );
		if( it != this->registeredActors.end() )
		{
			Actor * newActor = it->second->Make();
			newActor->Init( this->map );
			newActor->Load( file );
			if( this->actors.find( newActor->GetName() ) != this->actors.end() )
			{
				//this->actors[newActor->GetName()] = newActor;
				this->AddActor( newActor );
			}
			else
			{
				newActor->Deinit();
				Free( newActor );
			}
		}
		else
		{
			file.close();
			return false;
		}
		file >> temp;
		if( file.eof() )
			break;
	}
	
	file.close();
	return true;
}

bool World::AppendLoadWithOverlapp( const std::string & fileName )
{
	std::ifstream file( fileName );
	
	while( !file.eof() )
	{
		std::string typeName, temp;
		if( file.eof() )
			break;
		file >> typeName;
		if( file.eof() )
			break;
		file >> temp;
		if( file.eof() )
			break;
		auto it = this->registeredActors.find( typeName );
		if( it != this->registeredActors.end() )
		{
			Actor * newActor = it->second->Make();
			newActor->Init( this->map );
			newActor->Load( file );
			auto it2 = this->actors.find( newActor->GetName() );
			if( it2 != this->actors.end() )
			{
				this->DestroyActor( it2->first );
			}
			this->actors[newActor->GetName()] = newActor;
			this->map->AddActor( newActor );
		}
		else
		{
			file.close();
			return false;
		}
		file >> temp;
		if( file.eof() )
			break;
	}
	
	file.close();
	return true;
}

bool World::Load( const std::string & fileName )
{
	this->map->Clear();
	this->map->SetWorld( this );
	for( auto it = this->actors.begin(); it != this->actors.end(); ++it )
		Free( it->second );
	actors.clear();
	return this->AppendLoadWithOverlapp( fileName );
}

void World::Tick( unsigned deltaTime )
{
	if( this->updateTick )
	{
		for( auto it = this->actors.begin(); it != this->actors.end(); ++it )
		{
			if( it->second->NeedTick() )
			{
				it->second->Tick( deltaTime );
			}
		}
		
		for( auto it = this->queueActorsToRemove.begin(); it != this->queueActorsToRemove.end(); ++it )
		{
			this->DestroyActor( *it );
		}
	}
}

void World::Draw( unsigned deltaTime )
{
	if( this->drawMenu == false )
	{
		this->screenOffset = Vector( 0, 0 );
		{
			auto it = this->actors.find( this->centeredActorName );
			if( it != this->actors.end() )
			{
				this->screenOffset = it->second->GetPos() + ( it->second->GetSize() / 2 ) - ( /*Vector(this->mapScr->w,this->mapScr->h)*/  this->mapDrawer->GetWinSize() / 2 );
			}
		}
		
		std::set <Actor*> toDraw;
		std::set <Actor*> ignores;
		this->map->GetActors( Vector(0,0) + this->screenOffset, Vector(0,0) + this->screenOffset + this->mapDrawer->GetWinSize(), ignores, toDraw );
		
		this->mapScr->Clear();
		for( auto it = toDraw.begin(); it != toDraw.end(); ++it )
		{
			this->mapDrawer->SetCurrentPos( (*it)->GetPos() - this->screenOffset );
			(*it)->Draw( deltaTime, this->mapDrawer );
		}
		this->mapScr->Update();
		
		this->guiScr->Clear();
		this->DrawGUI( this->guiScr );
		this->guiScr->Update();
	}
	else
	{
		this->DrawMenu( this->screen );
		this->screen->Update();
	}
}

void World::BeginLoop()
{
	this->end = false;
	this->drawMenu = true;
	this->updateTick = false;
	unsigned beg = 0;
	while( this->end == false )
	{
		unsigned deltaTime = clock() - beg;
		if( deltaTime < 20 )
		{
			Sleep( 20 - deltaTime );
		}
		deltaTime = clock() - beg;
		if( deltaTime < 20 )
			deltaTime = 20;
		else if( deltaTime > 100 )
			deltaTime = 100;
		
		beg = clock();
		
		this->Tick( deltaTime );
		this->Draw( deltaTime );
		
		
		
		
		/*
		this->map->Clear();
		this->map->~Map();
		
		this->map = new ( (void*)(this->map) ) Map();
		this->map->SetWorld( this );
		
		for( auto it = this->actors.begin(); it != this->actors.end(); ++it )
		{
			this->map->AddActor( it->second );
		}
		*/
		
		
	}
}

void World::Destroy()
{
	this->map->Clear();
	for( auto it = this->actors.begin(); it != this->actors.end(); ++it )
		Free( it->second );
	for( auto it = registeredActors.begin(); it != this->registeredActors.end(); ++it )
		Free( it->second );
}

World::World() :
	screenOffset(0,0)
{
	if( 1 )
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo( GetStdHandle(STD_OUTPUT_HANDLE), &csbi );
		short x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		short y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
		
		SMALL_RECT windowSize = { 0, 0, short(x-1), short(y-1) };
		COORD bufferSize = { x, y };
		
		auto hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
		SetConsoleWindowInfo( hConsole, TRUE, &windowSize );
		SetConsoleScreenBufferSize( hConsole, bufferSize );
		SetConsoleWindowInfo( hConsole, TRUE, &windowSize );
		SetConsoleScreenBufferSize( hConsole, bufferSize );
		
		::HANDLE hConsoleOut = ::GetStdHandle( STD_OUTPUT_HANDLE );
		::CONSOLE_CURSOR_INFO hCCI;
		::GetConsoleCursorInfo( hConsoleOut, &hCCI );
		hCCI.bVisible = FALSE;
		::SetConsoleCursorInfo( hConsoleOut, &hCCI );
		SetConsoleTitle( "Game" );
	}
	
	this->map = Allocate<Map>();
	this->map->SetWorld( this );
	this->screen = Allocate<Window>();
	this->mapScr = Allocate<Window>();
	this->guiScr = Allocate<Window>();
	this->screen->Init( 0.0f, 0.0f, 1.0f, 1.0f );
	this->mapScr->Init( 0.0f, 0.0f, 0.75f, 1.0f );
	this->guiScr->Init( 0.75f, 0.0f, 1.0f, 1.0f );
	this->mapDrawer = Allocate<Drawer>();
	this->mapDrawer->SetWindow( this->mapScr );
	end = true;
}

World::~World()
{
	Free( this->mapDrawer );
	Free( this->screen );
	Free( this->mapScr );
	Free( this->guiScr );
}

#endif

