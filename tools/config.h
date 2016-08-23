#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h> 
#include <sys/types.h>



char* get_user_name(){
	struct passwd* pwd;
	pwd = getpwuid(getuid());
	return pwd->pw_name;
}

static char sl_cf_key[50][64] = {0};
static char sl_cf_val[50][124] = {0};
static int sl_cf_num = 0;
static char* config_path[2] = {
	(char*)"/home/.ecryptfs/config",
	(char*)"./config"
};

static int trim_str( char* buf ){
	if( !buf )
		return -1;
	
	char* tb = (char*)malloc(strlen(buf)+2);
	memset( tb, 0, strlen(buf) );
	char* tmp = 0;
	if( ' ' == buf[0] ){
		tmp = buf;
		while( ' ' == *tmp )
			tmp++;
		strcpy(tb, tmp);
	}else{
		strcpy(tb, buf);
	}
	
	tmp = tb + strlen(tb)-1;
	while( ' ' == *tmp ){
		*tmp = '\0';
		tmp--;
	}
	strcpy(buf, tb);
	if( tb )
		free( tb );
	return 0;
}

static int init_config(){
	FILE* fp = 0;
	fp = fopen(config_path[0], "r");
	if( 0 == fp ){
		fp = fopen(config_path[1], "r");
		if( 0 == fp ){
			perror("Can't find the config file!\n");
			return -1;
		}
	}
	
	char line[256] = {0,};
	while(fgets(line, 256, fp)!=0)
	{
		int i = 0;
		line[strlen(line)-1] = '\0';
		trim_str( line );
		if( 0 == strlen( line ) )
			continue;
		if( '#' == line[0] )
			continue;
		for(i=0; i<strlen(line); i++ )
		{
			if( '=' == line[i] )
				break;
		}
		if( i == strlen(line) )
			continue;

		for( i=0; i<strlen(line); i++ ){
			if( '=' == line[i] ){
				line[i] = '\0';
			}
		}
		strcpy(sl_cf_key[sl_cf_num],line);
		strcpy(sl_cf_val[sl_cf_num],line+strlen(line)+1);
		trim_str( sl_cf_key[sl_cf_num] );
		trim_str( sl_cf_val[sl_cf_num] );
		sl_cf_num++;
	}

	if( fp ){
		fclose( fp );
	}
	return 0;
}

static  int  has_init = 0;
char* get_config_val_str( const char* key ){
	if( !has_init )
	{
		if( init_config() )
			exit(1);
		has_init = 1;
	}
	int i=0;
	for( ; i<sl_cf_num; i++ ){
		if( strcmp(key, sl_cf_key[i]) == 0 ){
			return sl_cf_val[i];
		}
	}
	return 0;
}

long long  get_config_val_num( const char*key ){
	
	if( !has_init )
	{
		if( init_config() )
			exit(1);
		has_init = 1;
	}
	int i=0;
	for( ; i<sl_cf_num; i++ ){
		if( strcmp(key, sl_cf_key[i]) == 0 ){
			return atoll(sl_cf_val[i]);
		}
	}
	return 0;
}
