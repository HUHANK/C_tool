#ifndef SL_BUFFER_H_
#define SL_BUFFER_H_

class slBuffer{

public:
	slBuffer();
	~slBuffer();

	void put( const char* buf, const int len );
	int  size();
	void clear();
	char* c_str();
	
private:
	int resize();

	char* m_buf;
	int   m_size;
	int   m_pose;

};

#endif
