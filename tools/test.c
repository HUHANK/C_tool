#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "sllog.h"

int main(){
	
	char msg[512] = {0};
	exec_shell("ping 127.0.0.1 -c 3 -w 3 | wc -l", msg, 512);
			
	printf("%d\n", atoi(msg));
	return 0;
}
