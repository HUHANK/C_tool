#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

/*
 *get keyboard input
 *
 * */

int get_kb_input( char* buf )
{
	int i = 0;
	while( (*buf=getchar()) != '\n' )
	{
		i++;
		buf++;
	}
	return i;
}

/*判断字符串src是否包含des，如果包含返回位置，不包含返回0*/
int str_contains(const char* src, const char* des )
{
	int i = 0;
	int j = 0;
	for( i=0; i<strlen(src); ++i )
	{
		if( src[i] == des[j] )
		{
			int k = i;
			for(; j<strlen(des); ++j )
			{
				if( src[k] == des[j] ){
					k++;
					continue;
				}else{
					break;
				}
			}
			if( j == strlen(des) )
				return i+1;
		}
		j = 0;
	}
	return 0;
}

/*目录正规化，去掉最后面的/号*/
int dir_norm( char* dir )
{
	int i=0;
	for( i=0; i<strlen(dir); ++i ){
		if( dir[i] == '\\' )
			dir[i]='/';
	}
	if ( dir[strlen(dir)-1] == '/' )
		dir[strlen(dir)-1] = '\0';
	return 0;
}


//把完整的目录分成父目录和文件名
int dir_divide( const char* src, char* parent, char* child )
{
	char dir[256] = {0};
	strcpy( dir, src );
	dir_norm ( dir );

	int i = strlen( dir );
	for( ; i>=0; i-- ){
		if( dir[i] == '/' ){
			dir[i] = '\0';
			break;
		}
	}
	strcpy( parent, dir );
	strcpy( child, dir+i+1 );
	return 0;
}


//去掉文件的通配符
int dir_emask( char* file )
{
	char buf[256] = {0};
	int f =0;
	int b = 0;
	for(; f<strlen( file ); ++f ){
		if( file[f] != '*' ){
			buf[b] = file[f];
			b++;
		}
	}
	strcpy( file , buf );
	return 0;
}


//判断文件夹时候存在 0,存在，否则不存在
int isFolderExist( const char* path )
{
	DIR* dp = 0;
	if( (dp=opendir(path)) != 0 ){
		closedir( dp );
		return 0;
	}
	return -1;
}







