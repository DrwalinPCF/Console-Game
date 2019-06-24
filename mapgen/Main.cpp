
#include "../lib/Utility.hpp"
#include "../lib/ArgumentParser.h"
#include "../thrdlib/LodePNG.h"

#include "GeneratorData.h"

#include <fstream>
#include <cstdio>

struct RGBA
{
	unsigned char r, g, b, a;
	RGBA()
	{
		r = g = b = 0;
		a = 255;
	}
};

void GeneratorData::Save( const char * fileName )
{
	std::vector < RGBA > imgData;
	imgData.resize( this->width * this->height );
	
	for( int i = 0; i < this->width; ++i )
	{
		for( int j = 0; j < this->height; ++j )
		{
			unsigned char c = this->heightMap[i][j];
			RGBA color;
			color.r = c;
			color.g = c;
			color.b = c;
			imgData[(j*this->width)+i] = color;
		}
	}
	
	lodepng::encode( fileName, (const unsigned char*)(&(imgData[0])), this->width, this->height );
}

void GeneratorData::Init()
{
	this->heightMap.resize( this->width );
	for( int i = 0; i < this->width; ++i )
	{
		this->heightMap[i].resize( this->height );
		for( int j = 0; j < this->height; ++j )
		{
			this->heightMap[i][j] = 0;
		}
	}
}

int main( int argc, char ** argv )
{
	ArgumentParser args( argc, argv );
	GeneratorData data;
	
	std::string fileName = args.Getstr("o")[0];
	data.width = args.Geti("w")[0];
	data.height = args.Geti("h")[0];
	data.octaves = args.Geti("oct")[0];
	
	data.Init();
	data.FirstPass();
	data.Save( fileName.c_str() );
	
	return 0;
}

