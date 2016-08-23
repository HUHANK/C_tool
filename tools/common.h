#ifndef COMMON_H_
#define COMMON_H_




int get_hostname( char* buf, int  buf_len );

int get_mac( char* buf, int  buf_len  );

int exec_shell(const char* shell, char* buf, int buf_len );

int str_contains(const char* src, const char* des );

int check_mount( const char* dir );

int dir_norm( char* dir );

int dir_divide( const char* src, char* parent, char* child);

int dir_emask( char* file );

int check_network();

int isFolderExist( const char* path );


#endif
