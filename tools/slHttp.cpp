#include "slHttp.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

slHttp::slHttp(const char* buf, const int len)
{
	if( !buf )
		return ;
	m_buf_len = len;
	m_buf = (char*)malloc(m_buf_len);
	memcpy( m_buf, buf, len );
	do_post_process();
}

slHttp::~slHttp()
{
	if( m_buf ){
		free( m_buf );
	}
}


int 
slHttp::check( const char* data )
{
	if( data[0] == 'G' &&
		data[1] == 'E' &&
		data[2] == 'T' ){
		return 0;
	}

	if( data[0] == 'P' &&
		data[1] == 'O' &&
		data[2] == 'S' &&
		data[3] == 'T' ){
		return 0;
	}

	return 1;
}

vector<string>
split( string str, string pattern )
{
	string::size_type pos;
	vector<string> result;
	str += pattern;
	int size = str.size();

	for( int i =0; i<size; i++ ){
		pos = str.find( pattern, i );
		if( pos < size ){
			string s = str.substr(i, pos-i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}

void 
slHttp::do_post_process()
{
	if( m_buf[0] == 'P' &&
		m_buf[1] == 'O' &&
		m_buf[2] == 'S' &&
		m_buf[3] == 'T' ){

	}else{
		return ;
	}
	
	char str_head[1024] = {0};
	for( int i=0; i<m_buf_len; i++ ){
		if( !strncmp("\r\n\r\n", m_buf+i, 4) ){
			strncpy(str_head, m_buf, i);
			m_post_data = m_buf + i + 4;
		}
	}


	char* p = strtok( str_head, "\r\n" );
	vector<string> v = split( p, " " );
	if( v.size() < 3 ){
		return;
	}
	m_head["method"] = v[0];
	m_head["path"] = v[1];
	m_head["protocol"] = v[2];
	


	while( p = strtok( 0, "\r\n" ) ){
		if( !p )
			break;
		if( string(p) == "" )
			break;
		v = split( p, ": " );
		m_head[v[0]] = v[1];
	}
}

void 
slHttp::parse_head( const char* h )
{
	vector<string> vsa = split(	h, "\r\n");
	vector<string> v1 = split( vsa[0], " " );
	if( v1.size() < 3 ){
		return;
	}
	m_head["method"] = v1[0];
	m_head["path"] = v1[1];
	m_head["protocol"] = v1[2];

	for( int i=1; i<vsa.size(); i++ ){
		vector<string> v = split( vsa[i], ": " );
		m_head[v[0]] = v[1];
	}
}

void 
slHttp::test_show()
{
	map<string, string>::iterator it ;
	for( it=m_head.begin(); it != m_head.end(); it++ )
	{
		cout<< it->first << "\t" << it->second << endl;
	}
	printf("Data: %s----\n", m_post_data );
}


char* 
slHttp::get_post_data()
{
	return m_post_data;
}

string 
slHttp::get_reply_http_package( string data )
{
	string ret = "";
	ret += "HTTP/1.1 200 OK\r\n";
	ret += "Access-Control-Allow-Origin: *\r\n";
	ret += "Content-Type: application/x-www-form-urlencoded; charset=UTF-8\r\n";
	char slen[20] = {0};
	sprintf( slen, "%d", (int)data.length() );
	ret += "Content-Length: "+string(slen)+"\r\n";
	ret += "\r\n";
	ret += data;
	return ret;
}
