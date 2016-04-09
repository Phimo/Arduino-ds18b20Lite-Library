# Arduino-ds18b20Lite-Library

For AVR and ESP8266 devices...

ds18b20Lite is a simply library to read a single Dallas DS18B20 temperature sensor as quickly as possible. In fact, the average time taken to fetch a reading from the DS18B20 is 10 milliseconds which is a vast improvement over the circa 750ms required using the Dallas library.

An instance of ds18b20Lite fetches readings from a single DS18B20 device on a single pin of the MCU although, of course, multiple instances may be created to read single DS18B20s on more than one pin.

Only two methods are provided as follows:

uint8_t begin(<optional resolution>)

The 'begin()' method sets the resolution of the attached DS18B20 to 9, 10, 11 or 12 bits but, if <optional resolution> is not specified the default resolution is 12 bits. 'begin()' also fetches the 64 bit ROM ID/Address and stores it in a uint8_t array called dsAddress. The 'OneWire' library is required and used thus:

'begin()' returns one of four results:

DS_ADDRESS_OK ,the DS18B20 address was retrieved successfully and stored in sensor.dsAddress

DS_BAD_ADD_CRC ,the DS18B20 address CRC chack failed

DS_WRONG_FAMILY ,the device is NOT a member of the DS18B20 family

DS_INVALID_RESOLUTION ,the <optional resolution> specified was not 9, 10, 11 or 12

float read(void)

The read() method reads the temperature data from the DS18B20 as a float. If the read fails -128.0 is returned. The data is fully CRC checked and read twice to ensure that the data is valid.

/* USER VARIABLES */

uint8_t dsAddress[8]      // the 64 bit (8 Bytes) ROM ID/Address
uint8_t scratchPad[9]     // the 9 Byte scaratchpad copied from the DS18B20 during each read() event.
