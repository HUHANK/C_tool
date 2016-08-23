#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

int exec_shell(const char* shell, char* buf, int buf_len )
{
	FILE* fp = popen(shell, "r");
	if( !fp ){
		return -1;
	}
	fgets( buf, buf_len, fp );
	pclose( fp );
}

/*
 *These call return the number of bytes hostname,
 or -1 if an error occurred.
 * */
int get_hostname( char* buf, int  buf_len )
{
	return exec_shell("hostname", buf, buf_len ); 
}

/*
 *These call return the number of bytes MAC,
 *or -1 if an error occurred.
 * */

int get_mac( char* buf, int  buf_len )
{
	return exec_shell("ifconfig -a|grep 'HWaddr.*$' -o|awk '{print $2}'", buf, buf_len );
}

/*
 *check the dir has been mounted or not
 * */
int check_mount( const char* dir )
{
	char cmd[512]={0};
	char msg[1024] = {0};
	sprintf(cmd, "mount -l | grep %s", dir );
	exec_shell( cmd, msg, 1024 );
	
	return strlen(msg);
}

/*Check the net work has started!
 return 0 successd, or failed!*/
int check_network()
{
	char msg[512] = {0};
	char* cmd = (char*)"ping 127.0.0.1 -c 3 -w 3 | wc -l";
	exec_shell( cmd, msg, 512 );
	int ret = atoi( msg );
	if( ret < 6 ){
		return -1;
	}
	if( ret > 5 ){
		return 0;
	}
	return -1;
}
