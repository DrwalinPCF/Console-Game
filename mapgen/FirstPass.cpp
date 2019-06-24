
#ifndef FIRST_PASS_CPP
#define FIRST_PASS_CPP

#include "GeneratorData.h"

#include <cstdio>
#include <ctime>
#include <cstdlib>

#include <cmath>

#include "../lib/Perlin.h"

void GeneratorData::FirstPass()
{
	Perlin perlin( 3627563242, this->octaves );
	
	printf( "\n first pass:\n" );
	unsigned long long max = this->width * this->height;
	unsigned long long progress = 0;
	for( int i = 0; i < this->width; ++i )
	{
		for( int j = 0; j < this->height; ++j, ++progress )
		{
			
			int value = (perlin.Noise( float(i)*0.02f, float(j)*0.02f )+0.27f) * 130.9f;
			
			if( value < 0 )
				value = 0;
			if( value > 255 )
				value = 255;
			
			this->heightMap[i][j] = value;
			
			if( progress%(max/100) == 0 )
			{
				printf( "\r %llu%%", progress*100/max );
			}
		}
	}
}

#endif

