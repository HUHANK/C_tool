#ifndef CSLENCODER_H_
#define	CSLENCODER_H_

typedef	struct
{
	unsigned char	* _data;
	unsigned int	_i;
	unsigned int	_capacity;
} CSL_CODER;


//void increase( CSL_ENCODER* pEnc );

void CSLEncoder_bytes( 
		CSL_CODER* pEnc, const void* val, const int len );

void CSLDecoder_bytes(
		CSL_CODER* pDec, void* val, const int len );




#endif //CSLENCODER_H_
