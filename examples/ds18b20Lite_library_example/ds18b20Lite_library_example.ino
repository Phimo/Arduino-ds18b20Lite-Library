/* A simple prrof of concept sketch which reads a single DS18B20
 * temperature sensor on the given pin. Multiple pins each with a single
 * DS18B20 sensor can be configured if required by creating additional
 * OneWire and ds18b20Lite instances.
 */

#define SENSOR_PIN 2

#include <OneWire.h>
#include <ds18b20Lite.h>

OneWire ds(SENSOR_PIN);
ds18b20Lite sensor(&ds);

void setup()
{
  Serial.begin(115200);
  // check that the DS18B20 is present and recognised correctly (true)
  // alternative resolutions can be specified by 'sensor.begin(<resolution>);'
  // where <resolution> is 9, 10, 11 or 12. See the DS18B20 datasheet for the
  // effect of resolution on the temperature readings
  if(!sensor.begin())  // if sensor.begin() is not true
  {
    switch (sensor.errorMsg)
    {
    case DS_BAD_ADD_CRC:  // value = 1
      Serial.println("DS18B20 Address CRC error!");
      while (1) delay(0);
      break;
    case DS_WRONG_FAMILY: // value = 2
      Serial.println("Not a DS18B20 device!");
      while (1) delay(0);
      break;
      case DS_INVALID_RESOLUTION:  // value = 3
      Serial.println("Invalid resolution value!");
      while (1) delay(0);
    }
  }
  else Serial.println("DS18B20 sensor started OK!");
      
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
  if (sensor.read())
  {
    // end the timing
    uint32_t endMillis = millis() - startMillis;
    // print out the data
    Serial.print(loopCounter++);
    Serial.print(": Temperature: ");
    Serial.print(sensor.tempC,3);
    Serial.print("C - ");
    Serial.print(sensor.tempF,3);
    Serial.print("F returned in ");
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



