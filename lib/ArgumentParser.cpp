
#ifndef ARGUMENT_PARSER_CPP
#define ARGUMENT_PARSER_CPP

#include "ArgumentParser.h"

bool ArgumentParser::Convertb( const std::string & value )
{
	if( value == "0" )
		return false;
	if( value.size() == 5 )
	{
		if( value[0] == 'f' || value[0] == 'F' )
			if( value[1] == 'a' || value[1] == 'A' )
				if( value[2] == 'l' || value[2] == 'L' )
					if( value[3] == 's' || value[3] == 'S' )
						if( value[4] == 'e' || value[4] == 'E' )
							return false;
	}
	return true;
}

char ArgumentParser::Convertc( const std::string & value )
{
	if( value.size() > 0 )
		return value[0];
	return 0;
}

unsigned char ArgumentParser::Convertuc( const std::string & value )
{
	if( value.size() > 0 )
		return value[0];
	return 0;
}

short ArgumentParser::Converts( const std::string & value )
{
	return std::stoi( value );
}

unsigned short ArgumentParser::Convertus( const std::string & value )
{
	return std::stoul( value );
}

int ArgumentParser::Converti( const std::string & value )
{
	return std::stoi( value );
}

unsigned int ArgumentParser::Convertui( const std::string & value )
{
	return std::stoul( value );
}

long long ArgumentParser::Convertll( const std::string & value )
{
	return std::stoll( value );
}

unsigned long long ArgumentParser::Convertull( const std::string & value )
{
	return std::stoull( value );
}

float ArgumentParser::Convertf( const std::string & value )
{
	return std::stof( value );
}

double ArgumentParser::Convertd( const std::string & value )
{
	return std::stod( value );
}

long double ArgumentParser::Convertld( const std::string & value )
{
	return std::stold( value );
}



std::vector < bool > ArgumentParser::Getb( const std::string & key )
{
	std::vector < bool > ret;
	auto it = this->data.find( key );
	if( it != this->data.end() )
	{
		std::vector < std::string > & source = it->second;
		for( int i = 0; i < source.size(); ++i )
		{
			ret.push_back( this->Convertb( source[i] ) );
		}
	}
	return ret;
}

std::vector < char > ArgumentParser::Getc( const std::string & key )
{
	std::vector < char > ret;
	auto it = this->data.find( key );
	if( it != this->data.end() )
	{
		std::vector < std::string > & source = it->second;
		for( int i = 0; i < source.size(); ++i )
		{
			ret.push_back( this->Convertc( source[i] ) );
		}
	}
	return ret;
}

std::vector < unsigned char > ArgumentParser::Getuc( const std::string & key )
{
	std::vector < unsigned char > ret;
	auto it = this->data.find( key );
	if( it != this->data.end() )
	{
		std::vector < std::string > & source = it->second;
		for( int i = 0; i < source.size(); ++i )
		{
			ret.push_back( this->Convertuc( source[i] ) );
		}
	}
	return ret;
}

std::vector < short > ArgumentParser::Gets( const std::string & key )
{
	std::vector < short > ret;
	auto it = this->data.find( key );
	if( it != this->data.end() )
	{
		std::vector < std::string > & source = it->second;
		for( int i = 0; i < source.size(); ++i )
		{
			ret.push_back( this->Converts( source[i] ) );
		}
	}
	return ret;
}

std::vector < unsigned short > ArgumentParser::Getus( const std::string & key )
{
	std::vector < unsigned short > ret;
	auto it = this->data.find( key );
	if( it != this->data.end() )
	{
		std::vector < std::string > & source = it->second;
		for( int i = 0; i < source.size(); ++i )
		{
			ret.push_back( this->Convertus( source[i] ) );
		}
	}
	return ret;
}

std::vector < int > ArgumentParser::Geti( const std::string & key )
{
	std::vector < int > ret;
	auto it = this->data.find( key );
	if( it != this->data.end() )
	{
		std::vector < std::string > & source = it->second;
		for( int i = 0; i < source.size(); ++i )
		{
			ret.push_back( this->Converti( source[i] ) );
		}
	}
	return ret;
}

std::vector < unsigned int > ArgumentParser::Getui( const std::string & key )
{
	std::vector < unsigned int > ret;
	auto it = this->data.find( key );
	if( it != this->data.end() )
	{
		std::vector < std::string > & source = it->second;
		for( int i = 0; i < source.size(); ++i )
		{
			ret.push_back( this->Convertui( source[i] ) );
		}
	}
	return ret;
}

std::vector < long long > ArgumentParser::Getll( const std::string & key )
{
	std::vector < long long > ret;
	auto it = this->data.find( key );
	if( it != this->data.end() )
	{
		std::vector < std::string > & source = it->second;
		for( int i = 0; i < source.size(); ++i )
		{
			ret.push_back( this->Convertll( source[i] ) );
		}
	}
	return ret;
}

std::vector < unsigned long long > ArgumentParser::Getull( const std::string & key )
{
	std::vector < unsigned long long > ret;
	auto it = this->data.find( key );
	if( it != this->data.end() )
	{
		std::vector < std::string > & source = it->second;
		for( int i = 0; i < source.size(); ++i )
		{
			ret.push_back( this->Convertull( source[i] ) );
		}
	}
	return ret;
}

std::vector < float > ArgumentParser::Getf( const std::string & key )
{
	std::vector < float > ret;
	auto it = this->data.find( key );
	if( it != this->data.end() )
	{
		std::vector < std::string > & source = it->second;
		for( int i = 0; i < source.size(); ++i )
		{
			ret.push_back( this->Convertf( source[i] ) );
		}
	}
	return ret;
}

std::vector < double > ArgumentParser::Getd( const std::string & key )
{
	std::vector < double > ret;
	auto it = this->data.find( key );
	if( it != this->data.end() )
	{
		std::vector < std::string > & source = it->second;
		for( int i = 0; i < source.size(); ++i )
		{
			ret.push_back( this->Convertd( source[i] ) );
		}
	}
	return ret;
}

std::vector < long double > ArgumentParser::Getld( const std::string & key )
{
	std::vector < long double > ret;
	auto it = this->data.find( key );
	if( it != this->data.end() )
	{
		std::vector < std::string > & source = it->second;
		for( int i = 0; i < source.size(); ++i )
		{
			ret.push_back( this->Convertld( source[i] ) );
		}
	}
	return ret;
}

std::vector < std::string > ArgumentParser::Getstr( const std::string & key )
{
	std::vector < std::string > ret;
	auto it = this->data.find( key );
	if( it != this->data.end() )
	{
		std::vector < std::string > & source = it->second;
		for( int i = 0; i < source.size(); ++i )
		{
			ret.push_back( source[i] );
		}
	}
	return ret;
}

std::vector < const char* > ArgumentParser::Getcstr( const std::string & key )
{
	std::vector < const char* > ret;
	auto it = this->data.find( key );
	if( it != this->data.end() )
	{
		std::vector < std::string > & source = it->second;
		for( int i = 0; i < source.size(); ++i )
		{
			ret.push_back( source[i].c_str() );
		}
	}
	return ret;
}



ArgumentParser::ArgumentParser( int argc, char ** argv )
{
	for( int i = 1; i < argc; ++i )
	{
		if( argv[i][0] == '-' )
		{
			int j = 1;
			for( ; argv[i][j] != 0; ++j )
			{
				if( argv[i][j] == 0 )
					break;
				if( argv[i][j] == '=' )
					break;
			}
			if( argv[i][j] == '=' )
			{
				if( j == 1 )
					data[""].push_back( argv[i]+2 );
				else
					data[ std::string( argv[i]+1, j-1 ) ].push_back( std::string( argv[i]+j+1 ) );
			}
			else
			{
				data[std::string(argv[i]+1)].push_back( "" );
			}
		}
		else
		{
			data[""].push_back( argv[i] );
		}
	}
}

#endif

