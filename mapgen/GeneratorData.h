
#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include "../lib/Utility.hpp"
#include "../lib/Perlin.h"

#include <vector>

class GeneratorData
{
public:
	
	int octaves;
	int width, height;
	std::vector < std::vector < unsigned int > > heightMap;
	
	void FirstPass();
	void Save( const char * fileName );
	void Init();
	
};

#endif

