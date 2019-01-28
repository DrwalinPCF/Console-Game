
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstdlib>

typedef long long loctype;

inline loctype Rand()
{
	loctype ret;
	short * ptr = (short*)(&ret);
	*ptr = rand();		++ptr;
	*ptr = rand();		++ptr;
	*ptr = rand();		++ptr;
	*ptr = rand();
	return ret;
}

inline loctype Rand( loctype min, loctype max )
{
	if( min > max )
	{
		loctype t = min;
		min = max;
		max = min;
	}
	else if( min == max )
		return min;
	return ( Rand() % ( max - min ) ) + min;
}

	
class Vector
{
public:
	
	loctype x, y;
	
	
	inline Vector operator + ( const Vector & other ) const
	{
		return Vector( this->x + other.x, this->y + other.y );
	}
	
	inline Vector operator - ( const Vector & other ) const
	{
		return Vector( this->x - other.x, this->y - other.y );
	}
	
	inline Vector operator / ( const float val ) const
	{
		return Vector( this->x / val, this->y / val );
	}
	
	inline Vector operator * ( const float val ) const
	{
		return Vector( this->x * val, this->y * val );
	}
	
	
	inline Vector & operator += ( const Vector & other )
	{
		this->x += other.x;
		this->y += other.y;
		return *this;
	}
	
	inline Vector & operator -= ( const Vector & other )
	{
		this->x -= other.x;
		this->y -= other.y;
		return *this;
	}
	
	inline Vector & operator /= ( const float val )
	{
		this->x /= val;
		this->y /= val;
		return *this;
	}
	
	inline Vector & operator *= ( const float val )
	{
		this->x *= val;
		this->y *= val;
		return *this;
	}
	
	
	inline Vector & operator = ( const Vector & other )
	{
		this->x = other.x;
		this->y = other.y;
		return *this;
	}
	
	
	inline bool operator < ( const Vector & other ) const
	{
		if( this->x < other.x )
			return true;
		else if( this->x == other.x && this->y < other.y )
			return true;
		return false;
	}
	
	inline bool operator > ( const Vector & other ) const
	{
		if( this->x > other.x )
			return true;
		else if( this->x == other.x && this->y > other.y )
			return true;
		return false;
	}
	
	inline bool operator <= ( const Vector & other ) const
	{
		if( this->x < other.x )
			return true;
		else if( this->x == other.x && this->y <= other.y )
			return true;
		return false;
	}
	
	inline bool operator >= ( const Vector & other ) const
	{
		if( this->x > other.x )
			return true;
		else if( this->x == other.x && this->y >= other.y )
			return true;
		return false;
	}
	
	inline bool operator == ( const Vector & other ) const
	{
		return this->x == other.x && this->y == other.y;
	}
	
	inline bool operator != ( const Vector & other ) const
	{
		return this->x != other.x || this->y != other.y;
	}
	
	static inline bool BoundInBound( const Vector & mina, const Vector & maxa, const Vector & minb, const Vector & maxb )
	{
		if( mina.x <= maxb.x )
			if( maxa.x >= minb.x )
				if( mina.y <= maxb.y )
					if( maxa.y >= minb.y )
						return true;
		return false;
	}
	
	
	inline Vector & Random( const Vector & min, const Vector & max )
	{
		this->x = Rand( min.x, max.x );
		this->y = Rand( min.y, max.y );
		return *this;
	}
	
	static inline Vector MakeRandom( const Vector & min, const Vector & max )
	{
		return Vector( Rand( min.x, max.x ), Rand( min.y, max.y ) );
	}
	
	inline Vector & Randomize( const Vector & min, const Vector & max )
	{
		this->operator+=( Vector::MakeRandom( min, max ) );
		return *this;
	}
	
	
	inline Vector & Clamp( const Vector & min, const Vector & max )
	{
		if( this->x < min.x )
			this->x = min.x;
		if( this->y < min.y )
			this->y = min.y;
		if( this->x > max.x )
			this->x = max.x;
		if( this->y > max.y )
			this->y = max.y;
		return *this;
	}
	
	inline Vector Clamped( const Vector & min, const Vector & max ) const
	{
		Vector ret;
		if( ret.x < min.x )
			ret.x = min.x;
		if( ret.y < min.y )
			ret.y = min.y;
		if( ret.x > max.x )
			ret.x = max.x;
		if( ret.y > max.y )
			ret.y = max.y;
		return ret;
	}
	
	
	Vector( const Vector & other )
	{
		x = other.x;
		y = other.y;
	}
	Vector( loctype a, loctype b )
	{
		x = a;
		y = b;
	}
	Vector( loctype a )
	{
		x = a;
		y = a;
	}
	Vector()
	{
		x = 0;
		y = 0;
	}
};

#endif

