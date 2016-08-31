#ifndef SWWTypeDefine_h__
#define SWWTypeDefine_h__

#include <stdio.h>
/*********************************/

#define SWWFS_MAX_KEY_NUM_GET_FROM_CERT 9
#define	MAX_NAME 65
#define	SWWFS_SECTOR_LEN  512
#define	SWWFS_SECTOR_LEN_BIT  9

#define	SWWFS_SPLIT_LEN 64
#define	SWWFS_BASE_ATTACH_LEN  512
#define	SWWFS_BASE_VALID_ATTACH_LEN (SWWFS_BASE_ATTACH_LEN - SWWFS_SPLIT_LEN)

#define SWWFS_MIN_TOTAL_ATTACH_LEN 1024
//char SWWFS_KEY_ITEM_SIGN[7] /*= {83,87,87,75,69,89,0}*/;
#define	SWWFS_KEY_ITEM_SIGN_LEN  7
//char SWWFS_ATTACH_SIGN[4] /*= {"SJH"}*/;

#define	SWWFS_ATTACH_SIGN_LEN 4
#define SWWFS_VERIFYSRC_LEN 32

#define	SWWFS_VERIFY_SRC_FILL 90
#define	SWWFS_VERIFY_RESULT_FILL 74
#define	SLAes_BLOCK_LEN 16
#define	SLAes_BLOCK_LEN_BIT 4

#define	SLAes_KEY_LEN32 32

#define	SWWFS_EC_AES 120

//主版本号
#define	SWWFS_MJVER_2 2
//次版本号
#define	SWWFS_MNVER_5 5
#define	SWWFS_MNVER_6	6
#define	SWWFS_MNVER_7	7
//当前版本号
#define	SWWFS_MJVER_CUR SWWFS_MJVER_2
//当前次版本号
#define	SWWFS_MNVER_CUR	SWWFS_MNVER_7

//编译号
#define	SWWFS_BLDNUM_7	7
#define	SWWFS_BLDNUM_8	8
//当前编译号
#define	SWWFS_BLDNUM_CUR	SWWFS_BLDNUM_8

#define	SWWFS_KEY_ACE_TYPE	0x00000001
#define	SWWFS_KEY_ACE_EXTAND_TYPE	0x00000002

/*********************************/

/* Define NULL pointer value */
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef OPTIONAL
#define OPTIONAL
#endif

#ifndef VOID
#define VOID void
typedef char CHAR;
typedef short SHORT;
typedef long LONG;
#endif

#ifndef BASETYPES
#define BASETYPES
typedef unsigned long ULONG;
typedef ULONG *PULONG;
typedef unsigned short USHORT;
typedef USHORT *PUSHORT;
typedef unsigned char UCHAR;
typedef UCHAR *PUCHAR;
typedef char *PSZ;
#endif  /* !BASETYPES */

#ifndef CONST
#define CONST               const
#endif

#ifndef  _WINDOWS_
typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef FLOAT               *PFLOAT;

typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned int        *PUINT;

typedef SHORT				LONG16;
typedef LONG				LONG32;
typedef long long			LONG64;
typedef USHORT				ULONG16;
typedef ULONG				ULONG32;
typedef unsigned long long	ULONG64;
typedef ULONG64				ULONGLONG;
typedef LONG32				INT32;
typedef LONG64				INT64;

typedef BYTE *				PBYTE;
typedef LONG *				PLONG;
//typedef ULONG *				PULONG;
typedef SHORT *				PSHORT;
//typedef USHORT *			PUSHORT;
typedef INT *				PINT;
//typedef UINT *				PUINT;
typedef LONG16 *			PLONG16;
typedef LONG32 *			PLONG32;
typedef LONG64 *			PLONG64;
typedef INT32 *				PINT32;
typedef INT64 *				PINT64;
#endif

#ifndef ASSERT
#define ASSERT(exper) assert(exper)
#endif

#ifndef EqualMemory
#define EqualMemory(Destination,Source,Length) (!memcmp((Destination),(Source),(Length)))
#endif

#ifndef MoveMemory
#define MoveMemory(Destination,Source,Length) memmove((Destination),(Source),(Length))
#endif

#ifndef CopyMemory
#define CopyMemory(Destination,Source,Length) memcpy((Destination),(Source),(Length))
#endif

#ifndef FillMemory
#define FillMemory(Destination,Length,Fill) memset((Destination),(Fill),(Length))
#endif

#ifndef ZeroMemory
#define ZeroMemory(Destination,Length) memset((Destination),0,(Length))
#endif

#define SLExAllocatePool(pool, size) malloc(size)
#define SLExFreePool(p) free(p)

#ifndef _SLRING3
#define _SLRING3
#endif

#ifndef SLCatchErr
#define SLCatchErr(file, msg, line, errNum) std::wcout << "In" << file << ":" << msg << " at line " << line << "with error data" << errNum << std::endl
#endif

#ifndef _WINDOWS_

#ifndef OutputDebugString
#ifdef DEBUG
#define OutputDebugString(msg) /*std::wcout << msg << std::endl*/printf("%s\n",msg);
#else
#define OutputDebugString(msg)
#endif
#endif

#ifndef __fastcall
#define __fastcall
#endif

#endif

#endif // SWWTypeDefine_h__
