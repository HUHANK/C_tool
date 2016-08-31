#include "CSLRsa.h"
//#include "rsa.h"
//#include "commFunc.h"
#include "SWWError.h"
#include "CSLCoder.h"

rsa_context* CSLRsa_ImportPrivKey( UCHAR*  pKey, ULONG dwKeyLen )
{
	if( !pKey )
	{
		return 0;
	}
	
	ULONG	dwErr;
	rsa_context*	m_pRsaCtx = (rsa_context*)malloc(sizeof(rsa_context));
	memset( m_pRsaCtx, 0, sizeof(rsa_context) );

	dwErr = SLRsa_ImportPrivKey( m_pRsaCtx, pKey, dwKeyLen );
	if( dwErr != SLERR_OK )
	{
		if( m_pRsaCtx )
		{
			rsa_free( m_pRsaCtx );
			free( m_pRsaCtx );
			m_pRsaCtx = 0;
		}
	}
	return m_pRsaCtx;
}

rsa_context*  CSLRsa_ImportPubKey ( UCHAR*  pKey, ULONG dwKeyLen )
{
	if( !pKey )
		return 0;
	ULONG	dwErr;
	rsa_context*	m_pRsaCtx = (rsa_context*)malloc(sizeof(rsa_context));
	memset( m_pRsaCtx, 0, sizeof( rsa_context ) );

	dwErr = SLRsa_ImportPubKey( m_pRsaCtx, pKey, dwKeyLen );
	if( dwErr != SLERR_OK )
	{
		if( m_pRsaCtx )
		{
			rsa_free( m_pRsaCtx );
			free( m_pRsaCtx );
			m_pRsaCtx  = 0;
		}
	}
	return m_pRsaCtx;
}

ULONG CSLRsa_GetAlign( const rsa_context* m_pRsaCtx )
{
	if( m_pRsaCtx )
		return m_pRsaCtx->len;
	return 0;
}


static ULONG CSLRsa_ExportMpi( void* pEnc, void* pMpi )
{
	if( !pEnc || !pMpi )
		return -1;

	CSL_CODER	*pSLEncoder = (CSL_CODER*)pEnc;
	mpi	*pRsaMpi	= (mpi*)pMpi;
	UCHAR	buff[1024];
	int i = 0;

	i = pRsaMpi->n * sizeof( int );
	if( mpi_export(pRsaMpi, buff, &i ) != 0 )
		return -1;
	CSLEncoder_bytes(pSLEncoder, &i, sizeof(int) );
	CSLEncoder_bytes(pSLEncoder, buff, i);
	return SLERR_OK;
}
static ULONG CSLRsa_ImportMpi( void* pDec, void* pMpi )
{
	if( !pDec || !pMpi )
		return -1;
	CSL_CODER*	pSLDecoder = (CSL_CODER*)pDec;
	mpi	*pRsaMpi = (mpi*)pMpi;
	UCHAR	buff[1024];
	int i = 0;

	CSLDecoder_bytes(pSLDecoder, &i, sizeof(int) );
	CSLDecoder_bytes(pSLDecoder, buff, i );
	if( mpi_import(pRsaMpi, buff, i ) != 0 )
		return  -1;
	return SLERR_OK;
}


ULONG	CSLRsa_ExportPrivKey( const rsa_context* m_pRsaCtx, UCHAR**	ppKey, ULONG* dwKeyLen )
{
	ULONG	dwErr = SLERR_UNDEFINE;
	CSL_CODER	oEncoder;
	memset( &oEncoder, 0, sizeof(CSL_CODER) );

	*ppKey = 0;
	*dwKeyLen = 0;
	do
	{
		CSLEncoder_bytes( &oEncoder, &(m_pRsaCtx->ver), sizeof(m_pRsaCtx->ver) );
		CSLEncoder_bytes( &oEncoder, &(m_pRsaCtx->len), sizeof(m_pRsaCtx->len) );
		
		dwErr = CSLRsa_ExportMpi(&oEncoder,&m_pRsaCtx->N);      /*!<  public modulus    */
		if(dwErr != SLERR_OK)
			break;
		dwErr = CSLRsa_ExportMpi(&oEncoder,&m_pRsaCtx->E);      /*!<  public exponent   */
		if(dwErr != SLERR_OK)
			break;
		dwErr = CSLRsa_ExportMpi(&oEncoder,&m_pRsaCtx->D);      /*!<  private exponent  */
		if(dwErr != SLERR_OK)
			break;

		dwErr = CSLRsa_ExportMpi(&oEncoder,&m_pRsaCtx->P);      /*!<  1st prime factor  */
		if(dwErr != SLERR_OK)
			break;
		dwErr = CSLRsa_ExportMpi(&oEncoder,&m_pRsaCtx->Q);      /*!<  2nd prime factor  */
		if(dwErr != SLERR_OK)
			break;
		dwErr = CSLRsa_ExportMpi(&oEncoder,&m_pRsaCtx->DP);     /*!<  D mod (P - 1)     */
		if(dwErr != SLERR_OK)
			break;
		dwErr = CSLRsa_ExportMpi(&oEncoder,&m_pRsaCtx->DQ);     /*!<  D mod (Q - 1)     */
		if(dwErr != SLERR_OK)
			break;
		dwErr = CSLRsa_ExportMpi(&oEncoder,&m_pRsaCtx->QP);     /*!<  inverse of Q % P  */
		if(dwErr != SLERR_OK)
			break;
	
		*dwKeyLen = oEncoder._i;
		*ppKey = (UCHAR*)malloc(*dwKeyLen);

		memcpy( *ppKey, oEncoder._data, *dwKeyLen );
		dwErr = SLERR_OK;
	}while(0);
	return dwErr;
}

ULONG	CSLRsa_ExportPubKey( const rsa_context* m_pRsaCtx, UCHAR**	ppKey, ULONG*	dwKeyLen )
{
	ULONG	dwErr = SLERR_UNDEFINE;
	CSL_CODER	oEncoder;
	
	*ppKey = 0;
	*dwKeyLen = 0;
	do
	{
		CSLEncoder_bytes(&oEncoder, &(m_pRsaCtx->ver), sizeof(m_pRsaCtx->ver) );
		CSLEncoder_bytes(&oEncoder, &(m_pRsaCtx->len), sizeof(m_pRsaCtx->len) );

		dwErr = CSLRsa_ExportMpi( &oEncoder, &m_pRsaCtx->N );
		if( dwErr != SLERR_OK )
			break;
		dwErr = CSLRsa_ExportMpi( &oEncoder, &m_pRsaCtx->E );
		if( dwErr != SLERR_OK )
			break;

		*dwKeyLen = oEncoder._i;
		*ppKey = (UCHAR*)malloc(*dwKeyLen);
		memcpy( *ppKey, oEncoder._data, *dwKeyLen );
		dwErr = SLERR_OK;
	}while( 0 );
	return dwErr;
}


ULONG CSLRsa_PrivDec( const rsa_context* m_pRsaCtx, UCHAR* pData, ULONG*  dwDataLen )
{
	if( !m_pRsaCtx )
		return 1;
	ULONG	dwAlign = CSLRsa_GetAlign( m_pRsaCtx );
	if( *dwDataLen != dwAlign )
		return 1;

	UCHAR* pTemp = (UCHAR*)malloc(dwAlign);
	int nRes = rsa_pkcs1_decrypt( m_pRsaCtx, pData, *dwDataLen, pTemp, (int*)dwDataLen );
	if( nRes == 0 )
	{
		memcpy( pData, pTemp, *dwDataLen );
		if( pTemp )
			free( pTemp );
		return 0;
	}else{
		if( pTemp )
			free( pTemp );
		return 1;
	}
}


ULONG CSLRsa_PubEnc( const rsa_context* m_pRsaCtx, UCHAR* pData, ULONG* dwDataLen, ULONG  dwBuffLen )
{
	if( !m_pRsaCtx )
		return 1;
	ULONG	dwAlign = CSLRsa_GetAlign( m_pRsaCtx );
	if( dwBuffLen != dwAlign )
		return 1;

	UCHAR*	pTemp = (UCHAR*)malloc(dwAlign);
	memset( pTemp, 0, dwAlign );
	memcpy( pTemp, pData, *dwDataLen );
	int nRes = rsa_pkcs1_encrypt( m_pRsaCtx, pData, *dwDataLen, pTemp, dwAlign );
	if( nRes == 0 )
	{
		memcpy( pData, pTemp, dwAlign );
		*dwDataLen = dwAlign;
	}
	if( pTemp )
		free( pTemp );

	return 0;
}






