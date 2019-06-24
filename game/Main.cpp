
#include <cstdlib>
#include <ctime>

#include <exception>

#include <conio.h>


#include "../lib/Utility.hpp"

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
		World2 * world = Allocate<World2>();
		
		RegisterTypes( world );
		
		WorldGenerator wg( world, Vector(0,0), Vector(1024,1024) );
		wg.GeneratePerlinNoise();
		wg.GameOfLifeStep( 7, 5, 9, 1 );
		wg.GameOfLifeStep( 5, 3, 7, 1 );
		wg.GameOfLifeStep( 5, 3, 7, 1 );
		wg.GameOfLifeStep( 5, 3, 7, 1 );
		wg.GameOfLifeStep( 5, 3, 7, 1 );
		wg.GameOfLifeStep( 5, 3, 7, 1 );
		wg.GameOfLifeStep( 5, 3, 7, 1 );
		wg.GameOfLifeStep( 5, 3, 7, 1 );
		wg.GameOfLifeStep( 5, 3, 7, 1 );
		wg.GenerateActors();
		
		
		world->AddActor( "Player", Vector(0,0), Allocate<Player>() );
		world->AddActor( "Mob_01", Vector(10,10), Allocate<Mob>() );
		
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



