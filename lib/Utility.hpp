
#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <ctime>
#include <string>
#include <fstream>
#include <map>
#include <typeinfo>
#include <vector>

#include "Vector.hpp"

struct MEMORYSTRUCT
{
	unsigned long long elements;
	unsigned long long sizeofelement;
	std::string typeString;
};

inline std::string GetDateString()
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[256];
	
	time( &rawtime );
	timeinfo = localtime( &rawtime );
	
	strftime( buffer, sizeof(buffer), "%Y%m%d%H%M%S", timeinfo );
	return std::string( buffer );
}



extern "C" std::map < void*, MEMORYSTRUCT > * DEBUG_MEMORY_USED;

template < typename T, typename... Args >
inline T * Allocate( unsigned long long elements = 1, Args... args )
{
	T * ret = new T[elements](args...);
	DEBUG_MEMORY_USED->operator[](ret).elements = elements;
	DEBUG_MEMORY_USED->operator[](ret).sizeofelement = sizeof(T);
	DEBUG_MEMORY_USED->operator[](ret).typeString = typeid(T).name();
	return ret;
}

template < typename T, typename... Args >
inline T * AllocateArgs( Args... args )
{
	T * ret = new T[1](args...);
	DEBUG_MEMORY_USED->operator[](ret).elements = 1;
	DEBUG_MEMORY_USED->operator[](ret).sizeofelement = sizeof(T);
	DEBUG_MEMORY_USED->operator[](ret).typeString = typeid(T).name();
	return ret;
}

template < typename T >
inline void Free( T * ptr )
{
	DEBUG_MEMORY_USED->erase( ptr );
	if( ptr )
		delete[] ptr;
}

inline void PrintMemoryAllocatedToFile( std::string fileName )
{
	std::ofstream file( fileName );
	
	for( auto it = DEBUG_MEMORY_USED->begin(); it != DEBUG_MEMORY_USED->end(); ++it )
	{
		file << "\nAllocated: " << it->second.elements << " elements at pointer " << ((unsigned long long)(it->first)) << " of type: " << it->second.typeString << "      " << it->second.elements * it->second.sizeofelement << " bytes";
	}
	
	file.close();
}



template < class T >
inline std::string MethodName( const std::string& prettyFunction )
{
	std::string ret = prettyFunction;
	size_t index = 0;
	
	while( true )
	{
		index = ret.find( "::__cxx11" );
		if( index == std::string::npos )
			break;
		ret.replace( index, 9, "" );
	}
	
	index = ret.find( " [" );
	if( index != std::string::npos )
		ret.resize( index );
	
	return ret;
}
#define __METHOD_NAME__ (MethodName<int>(__PRETTY_FUNCTION__))
extern "C" std::ofstream DBGFL;
#define DEBUG(MSG) {DBGFL << "\n " << __FILE__ << ":" << __LINE__ << " -> " << __METHOD_NAME__ << " : " << MSG; DBGFL.flush(); Sleep(10);}



inline std::vector < std::string > SubdivideString( const std::string & str )
{
	std::vector < std::string > ret;
	unsigned i=0, b=0, e=0;
	
	for( ; i < str.size(); ++i )
	{
		if( str[i] == '\"' || str[i] == '\'' )
		{
			if( e > b )
			{
				if( e > str.size() )
					e = str.size();
				ret.emplace_back( str.substr( b, e-b ) );
			}
			b = i+1;
			e = i+1;
			
			if( i+1 < str.size() )
			{
				for( ++i; i < str.size(); ++i )
				{
					if( str[i] == '\"' || str[i] == '\'' )
					{
						break;
					}
					else
					{
						e = i+1;
					}
				}
				
				if( e > b )
				{
					if( e > str.size() )
						e = str.size();
					ret.resize( ret.size() + 1 );
					ret.back() = str.substr( b, e-b );
				}
				e = i+1;
				b = i+1;
			}
			else
			{
				return ret;
			}
		}
		else if( str[i] == ' ' )
		{
			if( e > b )
			{
				if( e > str.size() )
					e = str.size();
				ret.resize( ret.size() + 1 );
				ret.back() = str.substr( b, e-b );
			}
			e = i+1;
			b = i+1;
		}
		else
		{
			e = i+1;
		}
	}
	
	if( e > b )
	{
		if( e > str.size() )
			e = str.size();
		ret.resize( ret.size() + 1 );
		ret.back() = str.substr( b, e-b );
	}
	
	return ret;
}

bool IsKeyDown( int keyId );
std::string GetLastErrorAsString();
Vector GetMousePosition();

#endif

