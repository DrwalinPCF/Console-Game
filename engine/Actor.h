
#ifndef ACTOR_H
#define ACTOR_H

#include <string>
#include <fstream>

#include "Vector.hpp"
#include "Drawer.hpp"

class Actor
{
protected:
	
	Vector pos;
	Vector size;
	std::string name;
	class World * world;
	
public:
	
	std::string GetName() const;
	
	virtual bool IsWalkable() const{return false;}//= 0;
	virtual bool NeedTick() const{return true;}//= 0;
	
	
	bool SetPos( const Vector & loc );
	bool Move( const Vector & move );
	
	Vector GetPos() const;
	Vector GetSize() const;
	
	
	virtual void Draw( unsigned deltaTime, class Drawer * drawer ){}// = 0;
	Vector GetAABBmin() const;
	Vector GetAABBmax() const;
	
	bool InBounds( const Vector & min, const Vector & max ) const;
	
	virtual void Save( std::ofstream & file ) const;
	virtual void Load( std::ifstream & file );
	
	virtual unsigned Tick(){return 50;}// = 0;
	
	virtual void Spawn( const std::string & name, const Vector & pos, const Vector & size );
	virtual void Despawn();
	
	virtual void Init( class World * world );
	virtual void Deinit();
	
	
	virtual std::string GetTypeName(){return "Actor";}// = 0;		// return name of the class
	virtual Actor * Make(){return NULL;}// = 0;					// return new T(); for every type
	virtual ~Actor();
	Actor();
};

#endif

