#include "am2315.h"
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv){
	char *i2c_device = "/dev/i2c-1";
	int address = 0x5c;
	
	void *am = am2315_init(address, i2c_device);
	
	
	if(am != NULL){
		int i;
		for(i = 0; i < 10; i++) {
			float temperature = am2315_temperature(am);
			float humidity = am2315_humidity(am);
			printf("t = %f, h = %f\n", temperature, humidity);
			usleep(2 * 1000 * 1000);
		}
	
		am2315_close(am);
	}
	
	return 0;
}
