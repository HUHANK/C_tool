#ifndef SL_JSON_H
#define SL_JSON_H

#include <string>

class slJson{

public:
	slJson();
	~slJson();

	int parse( const char* str );

	/*主要把JSON转换成二进制包数据*/
	char*  package( int *length );

	int	type;
	std::string	RsaPublicKey;
	std::string	RsaPrivateKey;
	std::string	user;
	std::string	dir;
private:
	char* m_buf;

};

#endif //
