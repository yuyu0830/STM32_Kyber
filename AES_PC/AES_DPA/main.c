#include <stdio.h>
#include <string.h>
#include <stdint.h>

// Enable both ECB and CBC mode. Note this can be done before including aes.h or at compile-time.
// E.g. with GCC by using the -D flag: gcc -c aes.c -DCBC=0 -DECB=1
#define CBC 1
#define ECB 1

#include "aes.h"

int Init();


int main(void)
{
    return 0;
}


int Init() {
	int state;

	// Connect Serial Port 
	if (state = SerialPortConnect()) {
		printf("Error code %d : Connect Serial Port Failed..\n", state);
		// return 1;
	}
	else {
		printf("Log : Connect Serial Port Successful!\n");
	}

	// Open Log File
	if (state = FileOpen()) {
		printf("Error code %d : Open File Failed..\n", state);
		// return 1;
	}
	else {
		//WriteLog(pk, sk);
		printf("Log : Open File Successful!\n");
	}

	// Send Key To Board
	if (state = SendKey(sk)) {
		printf("Error code %d : Send Key Failed..\n", state);
		// return 1;
	}
	else {
		printf("Log : Send Key Successful!\n");
	}

	printf("Log : Initialize Complete!\n\n");

	return 0;
}
