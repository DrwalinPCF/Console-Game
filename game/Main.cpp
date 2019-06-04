
#include <cstdlib>
#include <ctime>

#include <exception>

#include "../engine/Utility.hpp"

#include "../engine/Map.cpp"
#include "../engine/Actor.cpp"
#include "../engine/World.cpp"

#include "Block.hpp"
#include "Player.hpp"
#include "Character.hpp"
#include "World2.hpp"
#include "Mob.hpp"

#include "Projectile.cpp"

#include "RegisterTypes.cpp"

int main()
{
	srand( time( nullptr ) );
	
	try
	{
		World * world = Allocate<World2>();
		
		RegisterTypes( world );
		
		world->AddActor( "Player", Vector(0,0), Vector(1,1), Allocate<Player>() );
		world->AddActor( "Block_01", Vector(3,0), Vector(1,1), Allocate<Block>() );
		world->AddActor( "Block_02", Vector(3,4), Vector(4,2), Allocate<Block>() );
		world->AddActor( "Block_03", Vector(-3,0), Vector(3,1), Allocate<Block>() );
		world->AddActor( "Block_04", Vector(-3,7), Vector(1,3), Allocate<Block>() );
		world->AddActor( "Block_05", Vector(-3,-5), Vector(1,2), Allocate<Block>() );
		world->AddActor( "Block_06", Vector(3,-3), Vector(3,2), Allocate<Block>() );
		world->AddActor( "Mob_01", Vector(10,10), Vector(3,3), Allocate<Mob>() );
		
		world->CenterAtActor( "Player" );
		
		world->BeginLoop();
		
		world->Destroy();
		
		Free( world );
		
		delete DEBUG_MEMORY_USED;
	}
	catch( const std::exception & e )
	{
		printf( "\n Exception has been thrown: %s ", e.what() );
		getch();
	}
	
	return 0;
}



