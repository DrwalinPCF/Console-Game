
#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <ctime>
#include <string>

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

#include <fstream>
#include <map>

#include <typeinfo>

struct MEMORYSTRUCT
{
	unsigned long long elements;
	unsigned long long sizeofelement;
	std::string typeString;
};
std::map < void*, MEMORYSTRUCT > * DEBUG_MEMORY_USED = new std::map < void*, MEMORYSTRUCT >();

template < typename T >
inline T * Allocate( unsigned long long elements = 1)
{
	T * ret = new T[elements];
	DEBUG_MEMORY_USED->operator[](ret).elements = elements;
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


#endif

