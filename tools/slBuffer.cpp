#include "slBuffer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


slBuffer::slBuffer()
{
	m_buf = 0;
	m_size = 1024;
	m_pose = 0;
	resize();
}

slBuffer::~slBuffer()
{
	if( m_buf ){
		free( m_buf );
	}
}

int
slBuffer::resize()
{
	void* new_ptr = realloc( m_buf, m_size );
	if( !new_ptr ){
		perror( "realloc failed!\n" );
		return -1;
	}
	m_buf = (char*)new_ptr;
	memset( m_buf+size(), 0, m_size-size() );
	return 0;
}


int 
slBuffer::size()
{
	return m_pose;
}

char* 
slBuffer::c_str()
{
	return m_buf;
}


void 
slBuffer::put( const char* buf, const int len )
{
	if( !buf ){
		return;
	}
	while( size()+len > m_size ){
		m_size += 1024;
		if( resize() )
			m_size = m_size - 1024;
	}

	memcpy( m_buf+size(), buf, len );
	m_pose += len;
}

void 
slBuffer::clear()
{
	m_pose = 0;
}
