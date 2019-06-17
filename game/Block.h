
#ifndef BLOCK_H
#define BLOCK_H

#include "../engine/Actor.h"
#include "../engine/Drawer.hpp"

class Block : public Actor
{
protected:
	
	
	
public:
	
	virtual bool IsWalkable() const override;
	virtual bool NeedTick() const override;
	virtual unsigned char GetOpaqueness() const override;
	virtual bool IsStaticallyDrawn() const override;
	
	virtual void Draw( unsigned currentSecond, class Drawer * drawer ) override;
	
	virtual unsigned Tick() override;
	
	virtual void Save( std::ostream & file ) const override;
	virtual void Load( std::istream & file ) override;
	
	virtual void Spawn( const std::string & name, const Vector & pos, const Vector & size ) override;
	virtual void Despawn() override;
	
	virtual void Init( class World * world ) override;
	virtual void Deinit() override;
	
	virtual std::string GetTypeName() const override;
	virtual Actor * Make() const override;
	virtual ~Block() override;
	Block();
};

#endif

