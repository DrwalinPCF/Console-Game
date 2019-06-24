
#ifndef WORLD_H
#define WORLD_H

#include <map>
#include <set>
#include <vector>
#include <string>

#include "../lib/Vector.hpp"
#include "Window.h"

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
	
	std::multimap < std::string, int > mapsToLoad;		// arguments: 0-full Load with clear ; 1-append load with overlapp ; 2-append load without overlapp
	
	std::string centeredActorName;
	
	std::multimap < unsigned, Actor* > tickUpdateQueue;
	
	unsigned currentMoment;
	
	
	long long numberOfActorTicksPerWorldTick;
	
public:
	
	Vector GetScreenOffset() const;
	Vector GetWorldCursorPosition() const;
	
	const Actor * GetRegisteredActorByTypeName( const std::string & name ) const;
	
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
	
	void AddActor( std::string name, Vector pos, Actor * ptr );
	void AddActor( Actor * ptr );
	
	void DestroyActor( const std::string & name );
	void DestroyActor( Actor * actor );
	
	bool Save( const std::string & fileName ) const;
	bool AppendLoadWithoutOverlapp( const std::string & fileName );
	bool AppendLoadWithOverlapp( const std::string & fileName );
	bool Load( const std::string & fileName );
	
	void QueueAppendLoadWithoutOverlapp( const std::string & fileName );
	void QueueAppendLoadWithOverlapp( const std::string & fileName );
	void QueueLoad( const std::string & fileName );
	
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

