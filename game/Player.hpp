
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
	
	virtual void Draw( unsigned currentSecond, class Drawer * drawer ) override
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
	
	virtual unsigned Tick() override
	{
		unsigned ret = Character::Tick();
		
		if( IsKeyDown( VK_ESCAPE ) )
			this->world->Exit();
		if( IsKeyDown( VK_OEM_3 ) )
			dynamic_cast<World2*>(this->world)->BeginDrawingMenu( World2::MenuTypes::DEV_CONSOLE );
		
		if( IsKeyDown( 'A' ) )
			this->Move( Vector( -1, 0 ) );
		if( IsKeyDown( 'D' ) )
			this->Move( Vector( 1, 0 ) );
		if( IsKeyDown( 'S' ) )
			this->Move( Vector( 0, 1 ) );
		if( IsKeyDown( 'W' ) )
			this->Move( Vector( 0, -1 ) );
		
		if( IsKeyDown( VK_LEFT ) )
			this->direction = Vector( -1, 0 );
		if( IsKeyDown( VK_RIGHT ) )
			this->direction = Vector( 1, 0 );
		if( IsKeyDown( VK_UP ) )
			this->direction = Vector( 0, -1 );
		if( IsKeyDown( VK_DOWN ) )
			this->direction = Vector( 0, 1 );
		
		if( IsKeyDown( VK_SPACE ) )
			this->Attack();
		if( IsKeyDown( VK_RETURN ) )
			this->Shoot();
		
		
		if( IsKeyDown( 0x30 ) )
			PrintMemoryAllocatedToFile( "file0.txt" );
		if( IsKeyDown( 0x31 ) )
			PrintMemoryAllocatedToFile( "file1.txt" );
		if( IsKeyDown( 0x32 ) )
			PrintMemoryAllocatedToFile( "file2.txt" );
		if( IsKeyDown( 0x33 ) )
			PrintMemoryAllocatedToFile( "file3.txt" );
		if( IsKeyDown( 0x34 ) )
			PrintMemoryAllocatedToFile( "file4.txt" );
		if( IsKeyDown( 0x35 ) )
			PrintMemoryAllocatedToFile( "file5.txt" );
		if( IsKeyDown( 0x36 ) )
			PrintMemoryAllocatedToFile( "file6.txt" );
		if( IsKeyDown( 0x37 ) )
			PrintMemoryAllocatedToFile( "file7.txt" );
		if( IsKeyDown( 0x38 ) )
			PrintMemoryAllocatedToFile( "file8.txt" );
		if( IsKeyDown( 0x39 ) )
			PrintMemoryAllocatedToFile( "file9.txt" );
		
		
		return ret;
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
	
	
	virtual std::string GetTypeName() const override
	{
		return "Player";
	}
	
	virtual Actor * Make() const override
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

