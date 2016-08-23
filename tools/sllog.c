#include "sllog.h"


void init_log( const char* name )
{
	static int hasInit = 0;
	if( hasInit == 0 ){
		if( name )
			openlog( name , LOG_CONS|LOG_PID|LOG_NOWAIT, 0 );
		else
			openlog( "Sanlen", LOG_CONS|LOG_PID, 0 );
		hasInit = 1;
	}
}


void sl_log( const char* msg )
{
	syslog( LOG_NOTICE, "%s\n", msg );
}
