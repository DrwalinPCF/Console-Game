
#ifndef DRAW_GUI_CPP
#define DRAW_GUI_CPP

#include "World2.hpp"

void World2::DrawGUI( Window * window )
{
	auto it = this->actors.find( "Player" );
	if( it != this->actors.end() )
	{
		Character * player = dynamic_cast<Character*>(it->second);
		if( player )
		{
			window->Print( Vector( 1, 1 ), "Player:" );
			window->Print( Vector( 5, 2 ), "Hp: %4i / %4i", player->GetHP(), player->GetMaxHP() );
			window->Print( Vector( 5, 3 ), "Pos: ( %lli, %lli )", player->GetPos().x, player->GetPos().y );
		}
		else
		{
			window->Print( Vector( 1, 1 ), "Actor named \"Player\" is not of type Character" );
		}
	}
	else
	{
		window->Print( Vector( 1, 1 ), "Cannot find actor with name \"Player\"" );
	}
	
	window->Print( Vector( 0, 4 ), " " );
	
	static int ticks = 0;
	++ticks;
	window->Print( "\n fps = %i / %f = %f", ticks, float(clock())*0.001f, float(ticks) / (float(clock())*0.001f) );
	
	window->Print( "\n Number of Actors: %lli ", this->GetNumberOfActors() );
	window->Print( "\n Actor::Tick per world tick: %lli ", this->GetActorTicksPerWorldTick() );
}

#endif

