
#ifndef PERLIN_HPP
#define PERLIN_HPP

// based on: https://mrl.nyu.edu/~perlin/noise/
// JAVA REFERENCE IMPLEMENTATION OF IMPROVED NOISE - COPYRIGHT 2002 KEN PERLIN.

namespace Perlin
{
	inline float Fade( float t )
	{
		return t * t * t * (t * (t * 6 - 15) + 10);
	}
	
	inline float Lerp( float t, float a, float b )
	{
		return a + t * (b - a);
	}
	
	inline float Grad( int hash, float x, float y, float z )
	{
		int h = hash & 15;			// CONVERT LO 4 BITS OF HASH CODE
		float u = h<8 ? x : y,		// INTO 12 GRADIENT DIRECTIONS.
			  v = h<4 ? y : (((h==12)||(h==14)) ? x : z);
		return (((h&1) == 0) ? u : -u) + (((h&2) == 0) ? v : -v);
	}
	
	float Noise( float x, float y, float z );
	
	class Initer
	{
	public:
		Initer();
	};
};

#endif

