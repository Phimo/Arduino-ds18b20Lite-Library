/* ds18b20Lite - A simple library to provide fast, circa 20ms
temperature readings from a single DS18B20 sensor only.

(C) 2016 Phil Morris <www'lydiard.plus.com>

No warranty either actual or implied exists with regard to this library.

ds18b20Lite is in the Public Domain and may be distributed, copied and/or modified
for non-commercial purposes. This text must remain intact and be included in all cases!
*/ 

#ifndef DS18B20LITE_H
#define DS18B20LITE_H

#include <Arduino.h>
#include <OneWire.h>

// DS18B20 resolutions
#define DS_RES_9 9
#define DS_RES_10 10
#define DS_RES_11 11
#define DS_RES_12 12

// DS18B20 OneWire commands
#define DS_START_CONVERSION 0x44
#define DS_WRITE_SCATCHPAD 0x4E
#define DS_READ_SCRATCHPAD 0xBE
#define DS_SKIP_ROM 0xCC

// DS18B20 registers & addresses
#define DS_SCRATCHPAD_NUM_REG 9
#define DS_SCRATCHPAD_CRC_REG 8
#define DS_ADDRESS_NUM_REG 8
#define DS_ADDRESS_CRC_REG 7

// errors
#define DS_ADDRESS_OK 0
#define DS_BAD_ADD_CRC 1
#define DS_WRONG_FAMILY 2
#define DS_TEMP_INVALID -128.0

// timing
#define DS_TIMEOUT 1000	// the time-out period for DS18B20 reads

class ds18b20Lite
{
private:
	OneWire* _wire;
public:
	// attach the OneWire library, start the DS18B20, set the resolution and get its ID/Address
	// success or failure is returned by the 'present' variable true = Good, false = Bad
	// false will be returned by 'present' if the DS18B20 fails to start or the resolution
	// is not 9, 10, 11, or 12
	ds18b20Lite(OneWire*);
	
	// start the DS18B20 and set the resolution
	uint8_t begin(uint8_t _resolution = DS_RES_12);
	
	// read the DS18B20 temperature and return it as a float
	float read();
	
	// the scratchPad contains the entire DS18B20 scratchPad data
	// it is filled each time a successful read occurs
	uint8_t scratchPad[DS_SCRATCHPAD_NUM_REG];
	
	// the 64bit ID/Address of the attached DS18B20
	uint8_t dsAddress[DS_ADDRESS_NUM_REG];
	
	// the current resolution of the DS18B20. Valid values are 9, 10, 11 or 12
 	uint8_t resolution;
	
	
	
};
#endif