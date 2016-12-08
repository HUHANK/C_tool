#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/tcp.h>

//Client
int main()
{
	int socket = socket( AF_INET, SOCK_STREAM, 0 );
	if( socket < 0 )
		return -1;
	
	struct sockaddr_in addr;
	memset( &addr, 0, sizeof(addr) );
	addr.sin_family = AF_INET;
	addr.sin_port = htons( 3000 );
	addr.sin_addr.s_addr = inet_addr( "10.0.0.1" );
	
	if( connect( socket, (struct sockaddr*)&addr, sizeof( addr ) )<0 )
		return -1;
	
	char* pMsg = "XXXXXXXXXXXXXXXXXXXX";
	int ret = write( socket, pMsg, strlen(pMsg) );
	
	close( socket );
	
	return 0;
}