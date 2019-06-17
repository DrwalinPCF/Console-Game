
#include <cstdlib>
#include <ctime>

#include <exception>

#include "../engine/Utility.cpp"

#include "../engine/Map.cpp"
#include "../engine/Actor.cpp"
#include "../engine/World.cpp"

#include "Block.cpp"
#include "Player.cpp"
#include "Character.cpp"
#include "World2.cpp"
#include "Mob.cpp"

#include "Projectile.cpp"

#include "RegisterTypes.cpp"

#include "WorldGenerator.cpp"

#include "Perlin.cpp"

#include "../engine/Vector.cpp"
#include "../engine/Window.cpp"
#include "../engine/Drawer.cpp"
#include "DrawerPreprocessor.cpp"

int main()
{
	srand( time( NULL ) );
	
	try
	{
		World * world = Allocate<World2>();
		
		RegisterTypes( world );
		
		WorldGenerator wg( world, Vector(-100,-100), Vector(100,100) );
		wg.GenerateRandom( 0.25f );
		
		int count;
		//printf( "\n Number of game of life iterations: " );
		//scanf( "%i", &count );
		count = 3;
		
		for( int i = 0; i < count; ++i )
			wg.GameOfLifeStep( 5, 2, 5, 1 );
		
		wg.GenerateActors();
		
		
		world->AddActor( "Player", Vector(0,0), Vector(1,1), Allocate<Player>() );
		//world->AddActor( "Block_01", Vector(3,0), Vector(1,1), Allocate<Block>() );
		//world->AddActor( "Block_02", Vector(3,4), Vector(4,2), Allocate<Block>() );
		//world->AddActor( "Block_03", Vector(-3,0), Vector(3,1), Allocate<Block>() );
		//world->AddActor( "Block_04", Vector(-3,7), Vector(1,3), Allocate<Block>() );
		//world->AddActor( "Block_05", Vector(-3,-5), Vector(1,2), Allocate<Block>() );
		//world->AddActor( "Block_06", Vector(3,-3), Vector(3,2), Allocate<Block>() );
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



