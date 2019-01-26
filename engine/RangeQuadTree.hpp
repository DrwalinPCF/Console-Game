
/*
	Copyright (C) 2019 Marek Zalewski aka Drwalin - All Rights Reserved
	
	Any one is authorized to copy, use or modify this file,
	but only when this file is marked as written by Marek Zalewski.
	
	No one can claim this file is originally written by them.
	
	No one can modify or remove this Copyright notice from this file.
*/

unsigned long long singletonNumberOfNodes = 0;

#ifndef RANGE_QUAD_TREE_PP
#define RANGE_QUAD_TREE_HPP

#include <unordered_map>
#include <unordered_set>
#include <set>
#include <vector>

#include "Vector.hpp"

template < typename T >
class QuadTree
{
private:
	
	std::unordered_map < long long, std::unordered_map < long long, T > > space;
	
public:
	
	inline T & Access( long long x, long long y )
	{
		return this->space[x][y];
	}
	
	inline void Erase( long long x, long long y )
	{
		auto it1 = this->space.find( x );
		if( it1 != this->space.end() )
		{
			auto it2 = it1->second.find( y );
			if( it2 != it1->second.end() )
			{
				it1->second.erase( it2 );
			}
			if( it1->second.size() == 0 )
			{
				this->space.erase( it1 );
			}
		}
	}
	
	void Clear()
	{
		this->space.clear();
	}
};

class AABB
{
public:
	long long minx;
	long long miny;
	long long maxx;
	long long maxy;
	AABB( long long a, long long b, long long c, long long d )
	{
		minx = a;
		miny = b;
		maxx = c;
		maxy = d;
	}
	AABB()
	{
		minx = 0;
		miny = 0;
		maxx = 0;
		maxy = 0;
	}
	AABB( Vector a, Vector b )
	{
		minx = a.x;
		miny = a.y;
		maxx = b.x;
		maxy = b.y;
	}
};

template < typename T >
class RangeQuadTree
{
private:
	
	QuadTree < std::set<T> > tree;
	long long shiftingScale;
	
	std::unordered_map < T, AABB > elems;
	
public:
	
	void Insert( AABB aabb, const T & elem )
	{
		
		aabb.minx >>= this->shiftingScale;
		aabb.miny >>= this->shiftingScale;
		if( ( aabb.maxx >> this->shiftingScale ) << this->shiftingScale < aabb.maxx )
		{
			aabb.maxx >>= this->shiftingScale;
			aabb.maxx += 1;
		}
		else
			aabb.maxx >>= this->shiftingScale;
		if( ( aabb.maxy >> this->shiftingScale ) << this->shiftingScale < aabb.maxy )
		{
			aabb.maxy >>= this->shiftingScale;
			aabb.maxy += 1;
		}
		else
			aabb.maxy >>= this->shiftingScale;
		
		this->elems[elem] = aabb;
		long long x, y;
		for( x = aabb.minx; x <= aabb.maxx; ++x )
		{
			for( y = aabb.miny; y <= aabb.maxy; ++y )
			{
				this->tree.Access( x, y ).insert( elem );
			}
		}
	}
	
	void Insert( Vector min, Vector max, const T & elem )
	{
		this->Insert( AABB(min,max), elem );
	}
	
	void Erase( const T & elem )
	{
		auto it = this->elems.find( elem );
		if( it != this->elems.end() )
		{
			const AABB & aabb = it->second;
			for( long long x = aabb.minx; x <= aabb.maxx; ++x )
			{
				for( long long y = aabb.miny; y <= aabb.maxy; ++y )
				{
					auto it = this->tree.Access( x, y );
					it.erase( elem );
					if( it.empty() )
					{
						this->tree.Erase( x, y );
					}
				}
			}
			this->elems.erase( it );
		}
	}
	
	void Get( AABB aabb, std::set < T > & ret )
	{
		aabb.minx >>= this->shiftingScale;
		aabb.miny >>= this->shiftingScale;
		if( ( aabb.maxx >> this->shiftingScale ) << this->shiftingScale < aabb.maxx )
		{
			aabb.maxx >>= this->shiftingScale;
			aabb.maxx += 1;
		}
		else
			aabb.maxx >>= this->shiftingScale;
		if( ( aabb.maxy >> this->shiftingScale ) << this->shiftingScale < aabb.maxy )
		{
			aabb.maxy >>= this->shiftingScale;
			aabb.maxy += 1;
		}
		else
			aabb.maxy >>= this->shiftingScale;
		
		for( long long x = aabb.minx; x <= aabb.maxx; ++x )
		{
			for( long long y = aabb.miny; y <= aabb.maxy; ++y )
			{
				const std::set<T> & it = this->tree.Access( x, y );
				
				for( auto it1 = it.begin(); it1 != it.end(); ++it1 )
				{
					ret.insert( *it1 );
				}
			}
		}
	}
	
	void Get( Vector min, Vector max, std::set < T > & ret )
	{
		this->Get( AABB(min,max), ret );
	}
	
	void Clear()
	{
		this->tree.Clear();
		this->elems.clear();
	}
	
	RangeQuadTree( long long shiftingScale = 4 )
	{
		this->shiftingScale = shiftingScale;
		if( this->shiftingScale < 0 )
			this->shiftingScale = 0;
		if( this->shiftingScale > 10 )
			this->shiftingScale = 10;
	}
};

#endif

