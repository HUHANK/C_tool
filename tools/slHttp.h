#ifndef SL_HTTP_H
#define SL_HTTP_H

#include <string>
#include <map>


class slHttp{

public:
	slHttp(const char* buf, const int len);
	~slHttp();

	static int check( const char* data );

	void test_show();

	char* get_post_data();
	
	static std::string get_reply_http_package( std::string data );

private:
	void do_post_process();
	void parse_head( const char* h );

	char* m_buf;
	char* m_post_data;
	int   m_buf_len;

	std::map<std::string, std::string>
		m_head;
};

#endif //
