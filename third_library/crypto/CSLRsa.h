#ifndef CSLRSA_H_
#define	CSLRSA_H_

#include "SWWTypeDefine.h"
#include "rsa.h"

#ifdef __cplusplus
extern "C"{
#endif

ULONG	CSLRsa_GetAlign( const rsa_context* m_pRsaCtx );

rsa_context*	CSLRsa_ImportPrivKey( UCHAR*	pKey,	ULONG	dwKeyLen );
rsa_context*	CSLRsa_ImportPubKey ( UCHAR*	pKey,	ULONG	dwKeyLen );

ULONG	CSLRsa_ExportPrivKey( const rsa_context* m_pRsaCtx, UCHAR**	ppKey, ULONG* dwKeyLen );
ULONG	CSLRsa_ExportPubKey( const rsa_context* m_pRsaCtx, UCHAR**	ppKey, ULONG*	dwKeyLen );

ULONG	CSLRsa_PrivDec( const rsa_context* m_pRsaCtx, UCHAR* pData, ULONG*	dwDataLen );
//ULONG CSLRsa_ExportMpi( void* pEnc, void* pMpi );
ULONG	CSLRsa_PubEnc( const rsa_context* m_pRsaCtx, UCHAR*	pData, ULONG* dwDataLen, ULONG	dwBuffLen );

#ifdef __cplusplus
}
#endif

#endif //CSLRSA_H_
