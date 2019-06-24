
#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

#include <string>
#include <map>
#include <vector>
#include <typeinfo>

/*

main.exe -a=13 -b c=13 --d=13 e --f=asd -gh=1 --ijk=2 -b=324 --b=
{
	{ "", {"c=13","e"} },
	{ "a", {"13"} },
	{ "b", {"","324",""} },
	{ "-d", {"13"} },
	{ "-f", {"asd"} },
	{ "gh", {"1"} },
	{ "-ijk", {"2"} },
	{ "-b", {""} }
}

*/

class ArgumentParser
{
private:
	
	std::map < std::string, std::vector<std::string> > data;
	
public:
	
	bool Convertb( const std::string & value );
	char Convertc( const std::string & value );
	unsigned char Convertuc( const std::string & value );
	short Converts( const std::string & value );
	unsigned short Convertus( const std::string & value );
	int Converti( const std::string & value );
	unsigned int Convertui( const std::string & value );
	long long Convertll( const std::string & value );
	unsigned long long Convertull( const std::string & value );
	float Convertf( const std::string & value );
	double Convertd( const std::string & value );
	long double Convertld( const std::string & value );
	
	std::vector < bool > Getb( const std::string & value );
	std::vector < char > Getc( const std::string & value );
	std::vector < unsigned char > Getuc( const std::string & value );
	std::vector < short > Gets( const std::string & value );
	std::vector < unsigned short > Getus( const std::string & value );
	std::vector < int > Geti( const std::string & value );
	std::vector < unsigned int > Getui( const std::string & value );
	std::vector < long long > Getll( const std::string & value );
	std::vector < unsigned long long > Getull( const std::string & value );
	std::vector < float > Getf( const std::string & value );
	std::vector < double > Getd( const std::string & value );
	std::vector < long double > Getld( const std::string & value );
	std::vector < std::string > Getstr( const std::string & value );
	std::vector < const char* > Getcstr( const std::string & value );
	
	ArgumentParser( int argc, char ** argv );
};

#endif

