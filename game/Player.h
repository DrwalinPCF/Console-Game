
#ifndef PLAYER_H
#define PLAYER_H

#include <set>

#include "../engine/Drawer.hpp"

#include "Character.h"

class Player : public Character
{
protected:
	
	
	
public:
	
	virtual void Draw( unsigned currentSecond, class Drawer * drawer ) override;
	
	virtual unsigned Tick() override;
	
	virtual void Save( std::ostream & file ) const override;
	virtual void Load( std::istream & file ) override;
	
	virtual void Spawn( const std::string & name, const Vector & pos ) override;
	virtual void Despawn() override;
	
	virtual void Init( class World * world ) override;
	virtual void Deinit() override;
	
	virtual std::string GetTypeName() const override;
	
	virtual Actor * Make() const override;
	virtual ~Player() override;
	Player();
};

#endif

