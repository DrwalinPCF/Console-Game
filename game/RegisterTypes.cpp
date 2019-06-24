
#ifndef REGISTER_TYPES_CPP
#define REGISTER_TYPES_CPP

#include "RegisterTypes.h"

#include "../lib/Utility.hpp"

#include "../engine/World.h"

#include "Player.h"
#include "Character.h"
#include "Mob.h"
#include "Projectile.h"

void RegisterTypes( World * world )
{
	world->RegisterType( Allocate<Player>() );
	world->RegisterType( Allocate<Mob>() );
	world->RegisterType( Allocate<Projectile>() );
}

#endif

