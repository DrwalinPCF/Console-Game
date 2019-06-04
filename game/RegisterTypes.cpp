
#ifndef REGISTER_TYPES_CPP
#define REGISTER_TYPES_CPP

#include "../engine/Utility.hpp"

#include "../engine/World.cpp"

#include "Block.hpp"
#include "Player.hpp"
#include "Character.hpp"
#include "Mob.hpp"

#include "Projectile.cpp"

void RegisterTypes( World * world )
{
	world->RegisterType( Allocate<Block>() );
	world->RegisterType( Allocate<Player>() );
	world->RegisterType( Allocate<Mob>() );
	world->RegisterType( Allocate<Projectile>() );
}

#endif

