
#include <cstdlib>
#include <ctime>

#include <exception>

#include <conio.h>


#include "../engine/Utility.hpp"

#include "../engine/World.h"
#include "World2.h"
#include "Player.h"
#include "Mob.h"

#include "RegisterTypes.h"
#include "WorldGenerator.h"

int main()
{
	srand( time( NULL ) );
	
	try
	{
		World * world = Allocate<World2>();
		
		RegisterTypes( world );
		
		WorldGenerator wg( world, Vector(-100,-100), Vector(100,100) );
		wg.GeneratePerlinNoise();
		wg.GenerateActors();
		
		
		world->AddActor( "Player", Vector(0,0), Vector(1,1), Allocate<Player>() );
		world->AddActor( "Mob_01", Vector(10,10), Vector(3,3), Allocate<Mob>() );
		
		world->CenterAtActor( "Player" );
		
		world->BeginLoop();
		
		world->Destroy();
		
		Free( world );
		
		PrintMemoryAllocatedToFile( "memory_at_main_exit.log" );
		
		delete DEBUG_MEMORY_USED;
	}
	catch( const std::exception & e )
	{
		printf( "\n Exception has been thrown: %s ", e.what() );
		getch();
	}
	
	return 0;
}



