
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "../engine/Actor.h"
#include "../engine/Drawer.hpp"

class Projectile : public Actor
{
protected:
	
	Vector direction;
	unsigned velocity;
	unsigned timeToDespawn;
	Vector changedPositionBy;
	
public:
	
	void SetVelocity( Vector direction, unsigned velocity, int timeToDespawn );
	
	virtual bool IsWalkable() const override;
	virtual bool NeedTick() const override;
	virtual unsigned char GetOpaqueness() const override;
	virtual bool IsStaticallyDrawn() const override;
	
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
	virtual ~Projectile() override;
	Projectile();
};

#endif

