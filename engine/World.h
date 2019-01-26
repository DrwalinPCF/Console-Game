
#ifndef WORLD_H
#define WORLD_H

#include <map>
#include <set>
#include <vector>
#include <string>

#include "Vector.hpp"
#include "Window.hpp"

#include "Actor.h"
#include "RangeQuadTree.hpp"

#include "Drawer.hpp"

class World
{
protected:
	
	RangeQuadTree<Actor*> tree;
	
	std::vector < std::string > queueActorsToRemove;
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
	
public:
	
	void UpdateActorCollider( Actor * ptr );
	void GetActors( Vector min, Vector max, const std::set<Actor*> & ignore, std::set < Actor* > & ret );
	bool IsWalkable( Vector min, Vector max, const std::set<Actor*> & ignore );
	
	long long GetNumberOfActors() const;
	
	std::string GetNewUniqueActorName() const;
	
	void QueueRemoveActor( std::string name );
	
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
	void Tick( unsigned deltaTime );
	void Draw( unsigned deltaTime );
	
	void BeginLoop();
	
	
	void Destroy();
	
	World();
	~World();
};

#endif

