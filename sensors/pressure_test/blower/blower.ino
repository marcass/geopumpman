#include <Wire.h>
#include <Adafruit_BMP085.h>

/*************************************************** 
  This is an example for the BMP085 Barometric Pressure & Temp Sensor

  Designed specifically to work with the Adafruit BMP085 Breakout 
  ----> https://www.adafruit.com/products/391

  These displays use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

// Connect VCC of the BMP085 sensor to 3.3V (NOT 5.0V!)
// Connect GND to Ground
// Connect SCL to i2c clock - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 5
// Connect SDA to i2c data - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 4
// EOC is not used, it signifies an end of conversion
// XCLR is a reset pin, also not used here

// Variable declarations
const int FAN = 6;
unsigned long dead_time_start = 0;
const long DEAD_TIME = 5000;
const int STATE_IDLE = 0;
const int STATE_BLOWING = 1;
const int STATE_PRESSURED = 2;
const int  STATE_PAUSE = 3;
int state = STATE_IDLE;
int pressure_in;
int pressure_out;

Adafruit_BMP085 bmp;
  
void setup() {
  Serial.begin(9600);
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1) {}
  }
  pinMode(FAN, OUTPUT);
  digitalWrite(FAN, LOW);
}

void proc_idle() {
  if (pressure_in - pressure_out > PRESSURE_THRESH) {
    state = STATE_PRESSURED;
  }
  if (pressure_in - pressure_out < PRESSURE_THRESH) {
    state = STATE_BLOWING;
  }
}

void proc_blowing() {
  if (pressure_in - pressure_out > PRESSURE_THRESH) {
    dead_time_start = millis();
    digitalWrite(FAN, LOW);
    state = STATE_PRESSURED;
  }
  else {
    digitalWrite(FAN, HIGH); //blow baby
  }
}

void proc_pressured() {
  if (pressure_in - pressure_out < PRESSURE_THRESH) {
    state = STATE_PAUSE;
  }
}
  
void loop() {
  switch (state) {
    case STATE_IDLE:
      proc_idle();
      break;
    case STATE_BLOWING:
      proc_blowing();
      break;
    case STATE_PRESSURED:
      proc_pressured();
      break;
    case STATE_PAUSE:
      if (millis() - dead_time_start > DEAD_TIME) {
        state = STATE_IDLE;
      }
  }

  
    Serial.print("Pressure = ");
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");
    
    // Calculate altitude assuming 'standard' barometric
    // pressure of 1013.25 millibar = 101325 Pascal
    Serial.print("Altitude = ");
    Serial.print(bmp.readAltitude());
    Serial.println(" meters");

    Serial.print("Pressure at sealevel (calculated) = ");
    Serial.print(bmp.readSealevelPressure());
    Serial.println(" Pa");

  // you can get a more precise measurement of altitude
  // if you know the current sea level pressure which will
  // vary with weather and such. If it is 1015 millibars
  // that is equal to 101500 Pascals.
    Serial.print("Real altitude = ");
    Serial.print(bmp.readAltitude(101500));
    Serial.println(" meters");
    
    Serial.println();
    delay(500);
}
