
#ifndef VECTOR_CPP
#define VECTOR_CPP

#include <cstdlib>

#include "Vector.hpp"

Vector::Vector( const Vector & other )
{
	x = other.x;
	y = other.y;
}

Vector::Vector( loctype a, loctype b )
{
	x = a;
	y = b;
}

Vector::Vector( loctype a )
{
	x = a;
	y = a;
}

Vector::Vector()
{
	x = 0;
	y = 0;
}

Vector::~Vector()
{
	x = 0;
	y = 0;
}

#endif

