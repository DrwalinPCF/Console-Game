
#ifndef CHARACTER_H
#define CHARACTER_H

#include "../engine/Actor.h"
#include "../engine/Drawer.hpp"

class Character : public Actor
{
protected:
	
	int maxHp;
	int hp;
	
	int attackCooldown;
	
	Vector direction;
	
public:
	
	virtual bool IsWalkable() const override;
	virtual bool NeedTick() const override;
	virtual unsigned char GetOpaqueness() const override;
	virtual bool IsStaticallyDrawn() const override;
	
	void Shoot();
	void Attack();
	
	void DamageAbsorb( int dmg );
	int GetHP() const;
	int GetMaxHP() const;
	
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
	virtual ~Character() override;
	Character();
};

#endif

