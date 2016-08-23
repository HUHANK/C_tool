#include "slJson.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../json/cJSON.h"
#include "../business/slpackets.h"
//#include "../crypto/m_PrivKey.h"
//#include "../crypto/m_PubKey.h"

extern unsigned long  m_PrivKeyLen;
extern unsigned char  m_PrivKey[];
extern unsigned long  m_PubKeyLen;
extern unsigned char  m_PubKey[];

using namespace std;

slJson::slJson()
{
	type = -1;
	RsaPublicKey = "";
	RsaPrivateKey = "";
	user = "";
	dir = "";
	m_buf = 0;
}

slJson::~slJson()
{
	if( m_buf ) {
		free( m_buf );
		m_buf = 0;
	}
}

int 
slJson::parse( const char* str )
{
	if( !str ){
		
		return -1;
	}

	int ret = 0;
	cJSON* root = cJSON_Parse( str );
	if( !root ){
		perror("json parse error!\n");
		return -1;
	}
	cJSON* jtype = cJSON_GetObjectItem( root, "type" );
	if( jtype ){
		type = jtype->valueint;
	}
	
	if( type == SL_STORE_RSA_KEY ){
		cJSON* js = cJSON_GetObjectItem( root, "RsaPublicKey" );
		if( js ){
			RsaPublicKey = js->valuestring;
		}
		js = cJSON_GetObjectItem( root, "RsaPrivateKey" );
		if( js ){
			RsaPrivateKey = js->valuestring;
		}

		goto out;
	}

	if( type == SL_DIR_SET_ENCRYPT ||
			type == SL_DIR_SET_UN_ENCRYPT ){
		cJSON* js = cJSON_GetObjectItem( root, "user" );
		if( js ){
			user = js->valuestring;
		}
		js = cJSON_GetObjectItem( root, "dir" );
		if( js ){
			dir = js->valuestring;
		}

		goto out;
	}
	
out:
	cJSON_Delete( root );
	return ret;
}


char*  
slJson::package( int* length )
{
	if( type == SL_STORE_RSA_KEY ){
		*length = sizeof(sl_client_session)+
                        sizeof(sl_rsa_key)*2 + m_PubKeyLen + m_PrivKeyLen
                        + sizeof( sl_packet );

		m_buf = (char*)malloc( *length + 40 );
		
		sl_packet *pack = (sl_packet*)m_buf ;
		pack->type = SL_USERSPACE_PACKET;
		pack->len = sizeof(sl_client_session)+
			sizeof(sl_rsa_key)*2 + m_PubKeyLen + m_PrivKeyLen;


		sl_client_session* sess = (sl_client_session*)pack->data;
		sess->opt = type;
		sess->len = sizeof(sl_rsa_key)*2 + m_PubKeyLen + m_PrivKeyLen;

		sl_rsa_key* pub , *prv;
		
		pub = (sl_rsa_key*)sess->data;
		pub->flag = SL_RSA_PUBLIC_KEY;
		pub->len = m_PubKeyLen;
		memcpy( pub->data, m_PubKey, pub->len );
		
		prv = (sl_rsa_key*)(pub->data + pub->len);
		prv->flag = SL_RSA_PRIVATE_KEY;
		prv->len = m_PrivKeyLen;
		memcpy( prv->data, m_PrivKey, prv->len );

		return m_buf;
	}
	if( type == SL_DIR_SET_ENCRYPT ||
		type == SL_DIR_SET_UN_ENCRYPT ){
		sl_packet pack;
		pack.type = SL_USERSPACE_PACKET;
		pack.len = sizeof( sl_client_session );

		sl_client_session sess;
		sess.opt = type;

		strcpy( (char*)sess.user, user.c_str() );
		strcpy( (char*)sess.dir,  dir.c_str()  );
			
		m_buf = (char*)malloc(sizeof(pack)+sizeof(sess)+20);
		int pos = 0;
		memcpy( m_buf+pos, &pack, sizeof(pack));
		pos += sizeof(pack);
		memcpy( m_buf+pos, &sess, sizeof(sess));
		pos += sizeof(sess);
		*length = pos;

		return m_buf;
	}
	return 0;
}
