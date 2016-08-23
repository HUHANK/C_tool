#ifndef SLLOG_H_
#define SLLOG_H_
#include <syslog.h>

void init_log( const char* name );

void sl_log( const char* msg );

#define sl_syslog(type, fmt, arg...) \
	syslog(type, "%s: " fmt, __FUNCTION__, ## arg);



#endif
