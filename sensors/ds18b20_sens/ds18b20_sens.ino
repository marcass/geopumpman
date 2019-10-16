
#include <OneWire.h>
#include <DallasTemperature.h>
// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2
#define EXCHANGER 1 //1/2/3/4
const String POSITION = "start"; //start || end
const String DEPTH = "bottom"; //bottom||top

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

/* Address of 1-wire sensors can be found by following the tutorial at
 * http://henrysch.capnfatz.com/henrys-bench/arduino-tempera#define FRIDGE_RELAY 10
ture-measurements/ds18b20-arduino-user-manual-introduction-and-contents/ds18b20-user-manual-part-2-getting-the-device-address/
 */
DeviceAddress TOP_TEMP_SENSOR = {0x28, 0xCC, 0x02, 0xAF, 0x03, 0x00, 0x00, 0xA8};
DeviceAddress BOTTOM_TEMP_SENSOR = {0x28, 0xCC, 0x02, 0xAF, 0x03, 0x00, 0x00, 0xA8};


void setup() {
  // start serial port
  Serial.begin(115200);
  // Start up the library
  // sensors.begin();
  // set the resolution to 9 bit - Valid values are 9, 10, or 11 bit.
  sensors.setResolution(tempSensor, 9);
  // confirm that we set that resolution by asking the DS18B20 to repeat it back
  Serial.print("Sensor Resolution: ");
  Serial.println(sensors.getResolution(tempSensor), DEC);
  Serial.println();
}

void loop() {
 // call sensors.requestTemperatures() to issue a global temperature
 // request to all devices on the bus
/********************************************************************/
 Serial.print(" Requesting temperatures...");
 float top = sensors.requestTemperaturesByAddress(TOP_TEMP_SENSOR);
 delay(500);
 float bottom = sensors.requestTemperaturesByAddress(BOTTOM_TEMP_SENSOR);
 delay(500);
 float bottomC = sensors.getTempC(BOTTOM_TEMP_SENSOR);
 float topC = sensors.getTempC(TOP_TEMP_SENSOR);
 Serial.println("DONE");
/********************************************************************/
 Serial.print("Top temperature is: ");
 Serial.print(topC);
 Serial.print("; Bottom temperature is: ");
 Serial.print(bottomC);
 // Serial.print(sensors.getTempCByIndex(0)); // Why "byIndex"?
 //   // You can have more than one DS18B20 on the same bus.
 //   // 0 refers to the first IC on the wire
   delay(1000);
}
