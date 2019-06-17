
#ifndef MOB_H
#define MOB_H

#include "Character.h"
#include "../engine/Drawer.hpp"

class Mob : public Character
{
protected:
	
	int movementCooldown;
	
public:
	
	virtual bool IsWalkable() const override;
	virtual bool NeedTick() const override;
	
	virtual void Draw( unsigned deltaTime, class Drawer * drawer ) override;
	
	virtual unsigned Tick() override;
	
	virtual void Save( std::ostream & file ) const override;
	virtual void Load( std::istream & file ) override;
	
	virtual void Spawn( const std::string & name, const Vector & pos, const Vector & size ) override;
	virtual void Despawn() override;
	
	virtual void Init( class World * world ) override;
	virtual void Deinit() override;
	
	virtual std::string GetTypeName() const override;
	
	virtual Actor * Make() const override;
	virtual ~Mob() override;
	Mob();
};

#endif

