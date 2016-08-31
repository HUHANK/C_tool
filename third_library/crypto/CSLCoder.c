#include "CSLCoder.h"


static void increase( CSL_CODER* pEnc )
{
	pEnc->_data = (unsigned char*)realloc(
			pEnc->_data, pEnc->_capacity + 256 );
	pEnc->_capacity += 256;
}


void CSLEncoder_bytes( 
		CSL_CODER* pEnc, const void* val, const int len )
{
	if( val == 0 ) return;

	while( pEnc->_i + len+1 > pEnc->_capacity )
		increase( pEnc );
	
	memcpy( pEnc->_data + pEnc->_i, val,  len );
	pEnc->_i += len;
}

void CSLDecoder_bytes(
		CSL_CODER* pDec, void* val, const int len )
{
	if( val == 0 ) return;

	memcpy( val, pDec->_data+pDec->_i, len );
	pDec->_i += len;
}































