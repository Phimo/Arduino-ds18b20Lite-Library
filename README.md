# Arduino-ds18b20Lite-Library

For AVR and ESP8266 devices...

ds18b20Lite is a simply library to read a single Dallas DS18B20 temperature sensor as quickly as possible. In fact, the average time taken to fetch a reading from the DS18B20 is 10 milliseconds which is a vast improvement over the circa 750ms required using the Dallas library.

An instance of ds18b20Lite fetches readings from a single DS18B20 device on a single pin of the MCU although, of course, multiple instances may be created to read single DS18B20s on more than one pin.

Only two methods are provided as follows:

uint8_t begin(optional resolution)

The 'begin()' method sets the resolution of the attached DS18B20 to 9, 10, 11 or 12 bits but, if <optional resolution> is not specified the default resolution is 12 bits. 'begin()' also fetches the 64 bit ROM ID/Address and stores it in a uint8_t array called dsAddress. The 'OneWire' library is required and used thus:

'begin()' returns true if successful. If begin() fails 'errorMsg' contains the reason for the failure

value = 1 DS_BAD_ADD_CRC ,the DS18B20 address CRC chack failed

value = 2 DS_WRONG_FAMILY ,the device is NOT a member of the DS18B20 family

value = 3 DS_INVALID_RESOLUTION ,the 'optional resolution' specified was not 9, 10, 11 or 12

float read(void)

The read() method reads the temperature data from the DS18B20 and stores it in two variable, tempC and tempF as a float. If the read fails false is returned. The data is fully CRC checked and read twice to ensure that the data is valid.

/* USER VARIABLES */

uint8_t dsAddress[8] ,the 64 bit (8 Bytes) ROM ID/Address

uint8_t scratchPad[9] ,the 9 Byte scaratchpad copied from the DS18B20 during each read() event.

uint8_t errorMsg , the failure reason for the 'begin()' method

float tempC , the temperature in degrees Celcius

float temF ,  the temperature in degrees Farenheit
