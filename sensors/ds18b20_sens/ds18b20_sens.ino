
#include <OneWire.h>
#include <DallasTemperature.h>
// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS A2
#define EXCHANGER 1 //1/2/3/4
const String POSITION = "start"; //start || end
String filename = EXCHANGER+"_"+POSITION+".csv";

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

/* Address of 1-wire sensors can be found by following the tutorial at
 * http://henrysch.capnfatz.com/henrys-bench/arduino-tempera#define FRIDGE_RELAY 10
ture-measurements/ds18b20-arduino-user-manual-introduction-and-contents/ds18b20-user-manual-part-2-getting-the-device-address/
 */
DeviceAddress TOP_TEMP_SENSOR =     {0x28, 0xFF, 0x16, 0x8D, 0x87, 0x16, 0x03, 0x50}; //checked - sensor with breadboard wires on it
DeviceAddress BOTTOM_TEMP_SENSOR =  {0x28, 0xFF, 0xE8, 0x8F, 0x70, 0x16, 0x05, 0x79}; //checked


void setup() {
  // start serial port
  Serial.begin(9600);
  // Start up the library
  // sensors.begin();
  // set the resolution to 9 bit - Valid values are 9, 10, or 11 bit.
  sensors.setResolution(TOP_TEMP_SENSOR, 11);
  sensors.setResolution(BOTTOM_TEMP_SENSOR, 11);
  // confirm that we set that resolution by asking the DS18B20 to repeat it back
  Serial.print("Sensor Resolution: Top - ");
  Serial.print(sensors.getResolution(TOP_TEMP_SENSOR), DEC);
  Serial.print(", Bottom - ");
  Serial.println(sensors.getResolution(BOTTOM_TEMP_SENSOR), DEC);
  Serial.println();
}

void loop() {
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
//  Serial.print(" Requesting temperatures...");
  // Tell the Sensor to Measure and Remember the Temperature it Measured
  // http://henrysbench.capnfatz.com/henrys-bench/arduino-temperature-measurements/ds18b20-arduino-user-manual-introduction-and-contents/ds18b20-arduino-users-manual-part-3-reading-a-single-temperature/
  sensors.requestTemperaturesByAddress(TOP_TEMP_SENSOR);// Send the command to get temperatures
  float top = sensors.getTempC(TOP_TEMP_SENSOR);
  delay(500);
  sensors.requestTemperaturesByAddress(BOTTOM_TEMP_SENSOR);
  float bottom = sensors.getTempC(BOTTOM_TEMP_SENSOR);
//  Serial.println("DONE");
  /********************************************************************/
//  Serial.print("Top temperature is: ");
//  Serial.print(top, 4); // The four just increases the resolution that is printed
//  Serial.print("; Bottom temperature is: ");
//  Serial.println(bottom, 4);
  //Paylod for python3
  Serial.print("DATA/");
  Serial.print(EXCHANGER);
  Serial.print("/");
  Serial.print(POSITION);
  Serial.print("/");
  Serial.print(top, 4); // The four just increases the resolution that is printed
  Serial.print("/");
  Serial.println(bottom, 4);
  delay(5000);
}
