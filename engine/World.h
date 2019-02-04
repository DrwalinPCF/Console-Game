
#ifndef WORLD_H
#define WORLD_H

#include <map>
#include <set>
#include <vector>
#include <string>

#include "Vector.hpp"
#include "Window.hpp"

#include "Actor.h"
#include "Map.h"

#include "Drawer.hpp"

class World
{
protected:
	
	Map * map;
	
	std::set < std::string > queueActorsToRemove;
	std::map < std::string, Actor* > actors;
	
	std::map < std::string, Actor* > registeredActors;
	
	Vector screenOffset;
	
	Drawer * mapDrawer;
	Window * mapScr;
	Window * guiScr;
	Window * screen;
	
	bool end;
	
	bool drawMenu;
	bool updateTick;
	
	std::string centeredActorName;
	
	std::multimap < unsigned, Actor* > tickUpdateQueue;
	
	unsigned currentMoment;
	
	
	long long numberOfActorTicksPerWorldTick;
	
public:
	
	long long GetActorTicksPerWorldTick() const{ return this->numberOfActorTicksPerWorldTick; }
	
	inline unsigned GetCurrentMoment() const { return this->currentMoment; }
	
	long long GetNumberOfActors() const;
	
	std::string GetNewUniqueActorName() const;
	
	void QueueRemoveActor( std::string name );
	
	Map * GetMap();
	
	bool CenterAtActor( const std::string & name );
	
	std::string GetNameOfActorType( Actor * actor ) const;
	
	void Exit();
	
	bool RegisterType( Actor * constructer );
	
	void AddActor( std::string name, Vector pos, Vector size, Actor * ptr );
	void AddActor( Actor * ptr );
	
	void DestroyActor( const std::string & name );
	void DestroyActor( Actor * actor );
	
	bool Save( const std::string & fileName ) const;
	bool AppendLoadWithoutOverlapp( const std::string & fileName );
	bool AppendLoadWithOverlapp( const std::string & fileName );
	bool Load( const std::string & fileName );
	
	virtual void DrawMenu( Window * window ) = 0;
	virtual void DrawGUI( Window * window ) = 0;
	void Tick();
	void Draw( unsigned deltaTime );
	
	void BeginLoop();
	
	
	void Destroy();
	
	World();
	~World();
};

#endif

