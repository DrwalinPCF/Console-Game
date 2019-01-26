
#ifndef PLAYER_H
#define PLAYER_H

#include <set>

#include "../engine/Map.h"
#include "../engine/Drawer.hpp"

#include "Character.hpp"
#include "World2.hpp"

class Player : public Character
{
protected:
	
	
	
public:
	
	virtual void Draw( unsigned deltaTime, class Drawer * drawer ) override
	{
		if( this->direction.x > 0 )
			drawer->Draw( Vector(0,0), '>' );
		else if( this->direction.x < 0 )
			drawer->Draw( Vector(0,0), '<' );
		else if( this->direction.y > 0 )
			drawer->Draw( Vector(0,0), 'v' );
		else if( this->direction.y < 0 )
			drawer->Draw( Vector(0,0), '^' );
		else
			drawer->Draw( Vector(0,0), 'X', FOREGROUND_RED | BACKGROUND_BLUE );
	}
	
	virtual void Tick( unsigned deltaTime ) override
	{
		Character::Tick( deltaTime );
		
		if( GetAsyncKeyState( 'A' ) & 0x8000 )
		{
			this->Move( Vector( -1, 0 ) );
		}
		if( GetAsyncKeyState( 'D' ) & 0x8000 )
		{
			this->Move( Vector( 1, 0 ) );
		}
		if( GetAsyncKeyState( 'S' ) & 0x8000 )
		{
			this->Move( Vector( 0, 1 ) );
		}
		if( GetAsyncKeyState( 'W' ) & 0x8000 )
		{
			this->Move( Vector( 0, -1 ) );
		}
		if( GetAsyncKeyState( VK_ESCAPE ) & 0x8000 )
		{
			this->world->Exit();
		}
		if( GetAsyncKeyState( VK_OEM_3 ) & 0x8000 )
			dynamic_cast<World2*>(this->world)->BeginDrawingMenu( World2::MenuTypes::DEV_CONSOLE );
		
		if( GetAsyncKeyState( VK_SPACE ) & 0x8000 )
			this->Attack();
		
		if( GetAsyncKeyState( VK_LEFT ) & 0x8000 )
			this->direction = Vector( -1, 0 );
		
		if( GetAsyncKeyState( VK_RIGHT ) & 0x8000 )
			this->direction = Vector( 1, 0 );
		
		if( GetAsyncKeyState( VK_UP ) & 0x8000 )
			this->direction = Vector( 0, -1 );
		
		if( GetAsyncKeyState( VK_DOWN ) & 0x8000 )
			this->direction = Vector( 0, 1 );
		
		if( GetAsyncKeyState( VK_RETURN ) & 0x8000 )
			this->Shoot();
		
		
		if( GetAsyncKeyState( 0x30 ) & 0x8000 )
			PrintMemoryAllocatedToFile( "file0.txt" );
		if( GetAsyncKeyState( 0x31 ) & 0x8000 )
			PrintMemoryAllocatedToFile( "file1.txt" );
		if( GetAsyncKeyState( 0x32 ) & 0x8000 )
			PrintMemoryAllocatedToFile( "file2.txt" );
		if( GetAsyncKeyState( 0x33 ) & 0x8000 )
			PrintMemoryAllocatedToFile( "file3.txt" );
		if( GetAsyncKeyState( 0x34 ) & 0x8000 )
			PrintMemoryAllocatedToFile( "file4.txt" );
		if( GetAsyncKeyState( 0x35 ) & 0x8000 )
			PrintMemoryAllocatedToFile( "file5.txt" );
		if( GetAsyncKeyState( 0x36 ) & 0x8000 )
			PrintMemoryAllocatedToFile( "file6.txt" );
		if( GetAsyncKeyState( 0x37 ) & 0x8000 )
			PrintMemoryAllocatedToFile( "file7.txt" );
		if( GetAsyncKeyState( 0x38 ) & 0x8000 )
			PrintMemoryAllocatedToFile( "file8.txt" );
		if( GetAsyncKeyState( 0x39 ) & 0x8000 )
			PrintMemoryAllocatedToFile( "file9.txt" );
		
	}
	
	virtual void Save( std::ofstream & file ) const override
	{
		Character::Save( file );
	}
	
	virtual void Load( std::ifstream & file ) override
	{
		Character::Load( file );
	}
	
	virtual void Spawn( const std::string & name, const Vector & pos, const Vector & size ) override
	{
		Character::Spawn( name, pos, size );
	}
	
	virtual void Despawn() override
	{
		Character::Despawn();
	}
	
	virtual void Init( class World * world ) override
	{
		Character::Init( world );
	}
	
	virtual void Deinit() override
	{
		Character::Deinit();
	}
	
	
	virtual std::string GetTypeName() override
	{
		return "Player";
	}
	
	virtual Actor * Make() override
	{
		return Allocate<Player>();
	}
	
	virtual ~Player() override
	{
	}
	
	Player()
	{
	}
};

#endif

