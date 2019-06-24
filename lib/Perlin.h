
#ifndef PERLIN_H
#define PERLIN_H

#include <cinttypes>

#include "Noise.h"

class Perlin
{
private:
	
	Noise noise;
	int octaves;
	
	float GetScale() const;
	
public:
	
	Noise & GetNoise();
	
	static float Interpolate( float t, float a, float b );
	static float Interpolate( float tx, float ty, float a, float b, float c, float d );
	float Noise( float _x, float _y );
	
	void Seed( uint64_t seed, int octaves );
	
	Perlin( uint64_t seed, int octaves );
	Perlin();
};

#endif

