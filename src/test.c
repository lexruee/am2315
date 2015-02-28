#include "am2315.h"
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv){
	char *i2c_device = "/dev/i2c-1";
	int address = 0x5c;
	
	void *am = am2315_init(address, i2c_device);
	
	
	if(am != NULL){
		am2315_test(am);
		am2315_close(am);
	}
	
	return 0;
}
