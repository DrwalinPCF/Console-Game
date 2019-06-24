
#ifndef PERLIN_CPP
#define PERLIN_CPP

#include "Noise.h"
#include "Utility.hpp"

#include "Perlin.h"

#include <cmath>

Noise & Perlin::GetNoise()
{
	return this->noise;
}

float Perlin::Interpolate( float t, float a, float b )
{
	if( t > 1 || t < 0 )
		printf( "\n t = %f", t );
	const float PI = 3.141592f;
	float f = sin(t*PI*0.5f);
	return (a*f) + (b*(1.0f-f));
}

/*
    a c
    b d
*/
float Perlin::Interpolate( float tx, float ty, float a, float b, float c, float d )
{
	return Perlin::Interpolate( tx, Interpolate(ty,a,b), Interpolate(ty,c,d) );
}

float Perlin::GetScale() const
{
	return float( 1 << (this->octaves) );
}

float Perlin::Noise( float _x, float _y )
{
	int power = this->octaves;
	int64_t dist = 1 << power;
	
	float fx = _x*float(dist);
	float fy = _y*float(dist);
	int64_t x = floor(fx);
	int64_t y = floor(fy);
	float value = 0.0f;
	
	int64_t bx, by, ex, ey;
	bx = floor(_x) * float(dist);
	by = floor(_y) * float(dist);
	ex = bx + dist;
	ey = by + dist;
	
	fx -= bx;
	fy -= by;
	
	float mult = 0.5f;
	
	int64_t modx = this->noise.GetRandom64( 0, 1 ), mody = this->noise.GetRandom64( 2, 3 );
	
	for( ; power > 1; --power, mult *= 0.5f )
	{
		if( dist < 1 )
			break;
		
		float a, b, c, d;
		a = this->noise.GetRandomFloat( (bx + modx), (by + mody), -1.0f, 1.0f );
		b = this->noise.GetRandomFloat( (bx + modx), (ey + mody), -1.0f, 1.0f );
		c = this->noise.GetRandomFloat( (ex + modx), (by + mody), -1.0f, 1.0f );
		d = this->noise.GetRandomFloat( (ex + modx), (ey + mody), -1.0f, 1.0f );
		
		value += Perlin::Interpolate( fx/float(dist), fy/float(dist), d, c, b, a ) * mult;
		
		dist >>= 1;
		
		if( fx < float(dist) )
		{
			ex -= float(dist);
		}
		else
		{
			bx += float(dist);
			fx -= float(dist);
		}
		
		if( fy < float(dist) )
		{
			ey -= float(dist);
		}
		else
		{
			by += float(dist);
			fy -= float(dist);
		}
		
		modx += this->noise.GetRandom64( mody, modx );
		mody += this->noise.GetRandom64( modx, mody );
	}
	
	return value;
}

void Perlin::Seed( uint64_t seed, int octaves )
{
	this->octaves = octaves;
	this->noise.Seed( seed, this->GetScale() );
	if( this->octaves > 16 )
		this->octaves = 16;
	if( this->octaves < 1 )
		this->octaves = 1;
}

Perlin::Perlin( uint64_t seed, int octaves )
{
	this->Seed( seed, octaves );
}

Perlin::Perlin()
{
	this->Seed( 8528939847, 7 );
}

#endif

