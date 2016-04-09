/* A simple prrof of concept sketch which reads a single DS18B20
 *  temperature sensor on the given pin.
 */

#include <OneWire.h>
#include <ds18b20Lite.h>

OneWire ds(12);
ds18b20Lite sensor(&ds);

void setup()
{

  Serial.begin(115200);
  // check that the DS18B20 is present and recognised correctly
  switch (sensor.begin()) {
    case DS_ADDRESS_OK: // value = 0
      Serial.println("DS18B20 present!");
      break;
    case DS_BAD_ADD_CRC:  // value = 1
      Serial.println("DS18B20 Address CRC error!");
      while (1) delay(0);
      break;
    case DS_WRONG_FAMILY: // value = 2
      Serial.println("Not a DS18B20 device!");
      while (1) delay(0);
      break;
	case DS_INVALID_RESOLUTION:
	  Serial.println("Invalid resolution!");
      while (1) delay(0);
	  break;
  }
  // print out the DS18N20 address
  Serial.print("DS18B20 ID/Address: ");
  for (uint8_t i = 0; i < 8; i++) printHex(sensor.dsAddress[i]);
  Serial.println();
}// END_OF_SETUP

uint32_t loopCounter = 1;

void loop()
{
    // set up a counter for timing
    uint32_t startMillis = millis();
    // fetch the temperature reading
    float myTemp = sensor.read();
    // the value -128 is the error value
    if (myTemp != -128.0)
    {
      // end the timing
      uint32_t endMillis = millis() - startMillis;
      // print out the data
      Serial.print(loopCounter++);
      Serial.print(": Temperature: ");
      Serial.print(myTemp);
      Serial.print(" C returned in ");
      Serial.print(endMillis);
      Serial.print(" ms with ");
      Serial.print(sensor.resolution);
      Serial.println(" bit resolution");
    }
    else Serial.println("DS18B20 read failed!");
    delay(2000);

}// END_OF_LOOP

void printHex(uint8_t _data)
{
  Serial.print(_data < 16 ? "0" : "");
  Serial.print(_data, HEX);
  Serial.print(" ");
}

