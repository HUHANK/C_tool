#ifndef SL_THREAD_H
#define SL_THREAD_H

class slThread{

public:
	slThread();
	~slThread();
	
	int start();
	
	int run();

	int stop();

private:
	unsigned long int m_id;
	int m_canStop;
	

	static void* thread( void* param );	


};

#endif //
