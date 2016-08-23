#ifndef SL_ERROR_H
#define SL_ERROR_H

#define SLER_SUCCESS	0x00
#define SLER_FAIL	0x01
#define SLER_JSON_PARSE	0x02

#include <string>

class slError{

public:

	std::string json( const int code );	
private:
	std::string packJson( const int code, const char* msg );

};
#endif //
