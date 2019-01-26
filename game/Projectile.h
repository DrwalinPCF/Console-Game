
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "../engine/Actor.h"
#include "../engine/Drawer.hpp"

class Projectile : public Actor
{
protected:
	
	Vector direction;
	unsigned velocity;
	int movementCooldown;
	int timeToDespawn;
	
	Vector changedPositionBy;
	
public:
	
	void SetVelocity( Vector direction, unsigned velocity, int timeToDespawn );
	
	virtual bool IsWalkable() const override;
	
	virtual bool NeedTick() const override;
	
	virtual void Draw( unsigned deltaTime, class Drawer * drawer ) override;
	
	virtual void Tick( unsigned deltaTime ) override;
	
	virtual void Save( std::ofstream & file ) const override;
	
	virtual void Load( std::ifstream & file ) override;
	
	virtual void Spawn( const std::string & name, const Vector & pos, const Vector & size ) override;
	
	virtual void Despawn() override;
	
	virtual void Init( class Map * map ) override;
	
	virtual void Deinit() override;
	
	
	virtual std::string GetTypeName() override;
	
	virtual Actor * Make() override;
	
	virtual ~Projectile() override;
	
	Projectile();
};

#endif

