/* ds18b20Lite - A simple library to provide fast, circa 20ms
temperature readings from a single DS18B20 sensor only.

(C) 2016 Phil Morris <www'lydiard.plus.com>

No warranty either actual or implied exists with regard to this library.

ds18b20Lite is in the Public Domain and may be distributed, copied and/or modified
for non-commercial purposes. This text must remain intact and be included in all cases!
*/ 

#include <ds18b20Lite.h>

// a lookup table for the DS18B20 resolution values
static const uint8_t resolutionData[4] = {0x00,0x20,0x40,0x60};

// startup functions are performed here
ds18b20Lite::ds18b20Lite(OneWire* _OneWire)
{
	_wire = _OneWire;
}

uint8_t ds18b20Lite::begin(uint8_t _resolution)
{
	if(_resolution < 9 || _resolution > 12) return false;
	resolution = _resolution;
	_wire->reset();
	_wire->search(dsAddress);
	if(_wire->crc8(dsAddress, DS_ADDRESS_CRC_REG) != dsAddress[DS_ADDRESS_CRC_REG]) return DS_BAD_ADD_CRC;
	if (dsAddress[0] != 0x28) return DS_WRONG_FAMILY;
	else
	{
		_wire->reset();
		_wire->select(dsAddress);
		_wire->write(DS_WRITE_SCATCHPAD);  // write to device scratchpad
		_wire->write(0x00);  // write userByte1
		_wire->write(0x00);  // write userByte0
		_wire->write(resolutionData[resolution - 9]); //  write resolution bits
		_wire->reset();
	}
	read();
	read();
	return DS_ADDRESS_OK;
}

// read the DS18B20 temperature and return it as a float
float ds18b20Lite::read()
{
  // start the DS18B20 conversion
  uint8_t crc;
  int16_t rawTemp;
  _wire->reset();
  //_wire->select(dsAddress);	// slower addressing method ~20ms
  _wire->write(DS_SKIP_ROM);	// faster addressing method ~10ms
  _wire->write(DS_START_CONVERSION);
  _wire->reset();
  // wait for conversion to complete by looking for data > 0
  uint32_t timeOutMillis = millis();
  // read the DS18B20 scratchpad until the CRC is true
  while(_wire->crc8(scratchPad, DS_SCRATCHPAD_CRC_REG) != scratchPad[DS_SCRATCHPAD_CRC_REG])
  {
    //_wire->select(dsAddress);	// slower addressing method ~20ms
    _wire->write(DS_SKIP_ROM);	// faster addressing method ~10ms
	_wire->write(DS_READ_SCRATCHPAD);  // Read Scratchpad
    _wire->read_bytes(scratchPad, DS_SCRATCHPAD_NUM_REG); // fetch the DS18B20 scratchpad Bytes
	_wire->reset();
    delay(0);
    if (millis() - timeOutMillis > DS_TIMEOUT) return DS_TEMP_INVALID;
  }
  // fetch the DS18B20 temperature data
  //_wire->select(dsAddress);	// slower addressing method ~20ms
  _wire->write(DS_SKIP_ROM);	// faster addressing method ~10ms
  _wire->write(DS_READ_SCRATCHPAD);  // Read Scratchpad
  _wire->read_bytes(scratchPad, DS_SCRATCHPAD_NUM_REG); // fetch the temperature Bytes
  _wire->reset();
  if(_wire->crc8(scratchPad, DS_SCRATCHPAD_CRC_REG) == scratchPad[DS_SCRATCHPAD_CRC_REG])
  {
    rawTemp = (scratchPad[1] << 8) | scratchPad[0];  // shift the MSB left and add the LSB
	return (float)rawTemp * 0.0625;
  }
  else return DS_TEMP_INVALID;
}
