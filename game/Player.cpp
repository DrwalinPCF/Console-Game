
#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "Player.h"

#include "World2.h"

void Player::Draw( unsigned currentSecond, class Drawer * drawer )
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

unsigned Player::Tick()
{
	unsigned ret = Character::Tick();
	
	if( IsKeyDown( VK_ESCAPE ) )
		this->world->Exit();
	if( IsKeyDown( VK_OEM_3 ) )
		dynamic_cast<World2*>(this->world)->BeginDrawingMenu( World2::MenuTypes::DEV_CONSOLE );
	
	Vector move(0,0);
	
	if( IsKeyDown( 'A' ) )
		move += Vector( -1, 0 );
	if( IsKeyDown( 'D' ) )
		move += Vector( 1, 0 );
	if( IsKeyDown( 'S' ) )
		move += Vector( 0, 1 );
	if( IsKeyDown( 'W' ) )
		move += Vector( 0, -1 );
	
	if( this->Move( move ) == false )
	{
		if( IsKeyDown( 'A' ) )
			this->Move( Vector( -1, 0 ) );
		if( IsKeyDown( 'D' ) )
			this->Move( Vector( 1, 0 ) );
		if( IsKeyDown( 'S' ) )
			this->Move( Vector( 0, 1 ) );
		if( IsKeyDown( 'W' ) )
			this->Move( Vector( 0, -1 ) );
	}
	
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
	
	if( IsKeyDown( 'P' ) )
		this->world->Save( "save.sav" );
	if( IsKeyDown( 'L' ) )
		this->world->QueueLoad( "save.sav" );
	
	return ret;
}

void Player::Save( std::ostream & file ) const
{
	Character::Save( file );
}

void Player::Load( std::istream & file )
{
	Character::Load( file );
}

void Player::Spawn( const std::string & name, const Vector & pos )
{
	Character::Spawn( name, pos );
}

void Player::Despawn()
{
	Character::Despawn();
}

void Player::Init( class World * world )
{
	Character::Init( world );
}

void Player::Deinit()
{
	Character::Deinit();
}


std::string Player::GetTypeName() const
{
	return "Player";
}

Actor * Player::Make() const
{
	return Allocate<Player>();
}

Player::~Player()
{
}

Player::Player()
{
}

#endif

