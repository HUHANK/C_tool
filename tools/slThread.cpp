#include "slThread.h"
#include <stdio.h>
#include <pthread.h>

slThread::slThread()
{
	m_id = 0;
	m_canStop = 0;
}

slThread::~slThread()
{
	stop();
}

int
slThread::start()
{
	pthread_t id = 0;
	int ret = pthread_create(&id, 0, thread, (void*)this );
	m_id = id;
	if ( ret ){
		perror("Thread create Error!\n");
		return -1;
	}
	return 0;	
}

int 
slThread::run()
{
	printf("XXXXXXXXXXXXXXXXXX\n");	
}

int 
slThread::stop()
{
	m_canStop = 1;
	return m_canStop;
}

void*
slThread::thread( void* param )
{
	slThread* p=(slThread*)param;
	p->run();
}
