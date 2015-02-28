/*
 * @author 	Alexander Rüedlinger <a.rueedlinger@gmail.com>
 * @date 	28.02.2015
 *
 * A C driver for the sensor AM2315.
 *  
 */
 
#ifndef __AM2315__
#define __AM2315__
#include <stdint.h>
#include "am2315.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <linux/i2c-dev.h>
#include <time.h>
#include <math.h>
#endif

/*
 * am2315 commands
 */
#define AM2315_CMD_READ_REG 0x03
#define AM2315_CMD_WRITE_REG 0x10

/*
 * am2315 humidity register
 */
#define AM2315_REG_HUM_H 0x00

/*
 * am2315 temperature register
 */
#define AM2315_REG_TMP_H 0x02



/*
 * Define debug function.
 */

#define __AM2315_DEBUG__
#ifdef __AM2315_DEBUG__				
#define DEBUG(...)	printf(__VA_ARGS__)
#else
#define DEBUG(...)
#endif


/*
 * Shortcut to cast void pointer to aam2315_t pointer
 */
#define TO_AM(x)	(am2315_t*) x



/*
 * Basic structure for the am2315 sensor
 */
typedef struct {
	/* file descriptor */
	int file;
	
	/* i2c device address */
	int address;
	
	/* i2c device file path */
	char *i2c_device;
} am2315_t;


/*
 * Prototypes for helper functions
 */
int am2315_set_addr(void *_am);
int32_t am2315_read_raw_temperature(void *_am);
int32_t am2315_read_raw_humidty(void *_am);
unsigned short crc16(unsigned char *ptr, unsigned char len);


/*
 * Implemetation of the helper functions
 */

/*
 * Computes the crc code.
 * 
 * @param char pointer
 * @param length
 * @return crc
 */
unsigned short crc16(unsigned char *ptr, unsigned char len) {
	unsigned short crc = 0xFFFF;
	unsigned char i;
	
	while(len--) {
		crc ^= *ptr++;
		for(i = 0; i < 8; i++) {
			if(crc & 0x01) {
				crc >>= 1;
				crc ^= 0xA001;
			} else {
				crc >>= 1;
			}
		}
		
	}
	return crc;
}

/*
 * Sets the address for the i2c device file.
 */
int am2315_set_addr(void *_am) {
	am2315_t* am = TO_AM(_am);
	int error;

	if((error = ioctl(am->file, I2C_SLAVE, am->address)) < 0)
		DEBUG("error: ioctl() failed\n");

	return error;
}

/*
 * Implementation of the interface functions
 */

int32_t am2315_read_raw_temperature(void *_am) {
	am2315_t *am = TO_AM(_am); 
	// todo
	return 0;
}

int32_t am2315_read_raw_humidty(void *_am) {
	am2315_t *am = TO_AM(_am); 
	// todo
	return 0;
}


/**
 * Creates a AM2315 sensor object.
 *
 * @param i2c device address
 * @param i2c device file path
 * @return am2315 sensor
 */
void *am2315_init(int address, const char* i2c_device_filepath) {
	DEBUG("device: init using address %#x and i2cbus %s\n", address, i2c_device_filepath);
	
	// setup am2315
	void *_am = malloc(sizeof(am2315_t));
	if(_am == NULL)  {
		DEBUG("error: malloc returns NULL pointer\n");
		return NULL;
	}

	am2315_t *am = TO_AM(_am);
	am->address = address;

	// setup i2c device path
	am->i2c_device = (char*) malloc(strlen(i2c_device_filepath) * sizeof(char));
	if(am->i2c_device == NULL) {
		DEBUG("error: malloc returns NULL pointer!\n");
		return NULL;
	}

	// copy string
	strcpy(am->i2c_device, i2c_device_filepath);
	
	// open i2c device
	int file;
	if((file = open(am->i2c_device, O_RDWR)) < 0) {
		DEBUG("error: %s open() failed\n", am->i2c_device);
		return NULL;
	}
	am->file = file;

	if(am2315_set_addr(_am) < 0)
		return NULL;

	// setup i2c device
	
	DEBUG("device: open ok\n");

	return _am;
}


/**
 * Closes a AM2315 object.
 * 
 * @param am2315 sensor
 */
void am2315_close(void *_am) {
	DEBUG("close am2315 device\n");
	am2315_t *am = TO_AM(_am);
	
	if(close(am->file) < 0)
		DEBUG("error: %s close() failed\n", am->i2c_device);
	
	free(am->i2c_device); // free string
	am->i2c_device = NULL;
	free(am); // free bmp structure
	_am = NULL;
} 


/**
 * Returns the measured temperature in celsius.
 * 
 * @param am2315 sensor
 * @return temperature
 */
float am2315_temperature(void *_am) {
	return 0;
}


/**
 * Returns the measured humidity.
 * 
 * @param am2315 sensor
 * @return humidity
 */
float am2315_humidity(void *_am) {
	return 0;
}
