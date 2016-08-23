#include "slError.h"
#include "../json/cJSON.h"
#include <stdio.h>

using namespace std;

string 
slError::json( const int code )
{
	switch( code ){
	
	case SLER_SUCCESS:
		return packJson(SLER_SUCCESS, "Successed!");
		break;	
	case SLER_FAIL:
		return packJson( SLER_FAIL, "Failed!");
		break;
	case SLER_JSON_PARSE:	
		return packJson( SLER_JSON_PARSE, "Json parsed error!" );
		break;
	default:
		return "";
	}
}


string 
slError::packJson( const int code, const char* msg )
{
	cJSON *root;
	root=cJSON_CreateObject();
	if( !root ){
		perror("cJSON_CreateObject Error!\n");
		return "";	
	}
	cJSON_AddNumberToObject( root, "ErrCode", code );
	cJSON_AddStringToObject( root, "ErrMsg", msg );
	string str = cJSON_Print(root);
	cJSON_Delete(root);
	return str;
}

