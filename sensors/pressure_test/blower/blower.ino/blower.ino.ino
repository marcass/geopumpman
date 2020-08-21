/***************************************************************************
  This is a library for the BMP280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BMP280 Breakout
  ----> http://www.adafruit.com/products/2651

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

//Set pressure
float pressure_out = 98267.00;
//Set threshold for blowing
float PRESSURE_THRESH = 50;

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)

Adafruit_BMP280 bmp; // I2C
//Adafruit_BMP280 bmp(BMP_CS); // hardware SPI
//Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

//Change line in Adafruit_BMP280.h to make sure address is 77 (not 76) when using chinese module

// Variable declarations
const int FAN = 18;
unsigned long dead_time_start = 0;
const long DEAD_TIME = 5000;
const unsigned long DATA_THRESH = 2000;
const int STATE_IDLE = 0;
const int STATE_BLOWING = 1;
const int STATE_PRESSURED = 2;
const int  STATE_TRANS = 3;
const int STATE_ERROR = 4;
int target_state;
int state = STATE_IDLE;
float pressure_in;
unsigned long data_print_thresh;

void setup() {
  Serial.begin(9600);
  Serial.println(F("BMP280 test"));

  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }
  pinMode(FAN, OUTPUT);
  digitalWrite(FAN, LOW);

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

 data_print_thresh = millis();
}

void proc_idle() {
  if (pressure_in - pressure_out > PRESSURE_THRESH) {
//    do nothing;
  }
  if (pressure_in - pressure_out < PRESSURE_THRESH) {
    target_state = STATE_BLOWING;
    state = STATE_TRANS;
  }else{
//    state = STATE_ERROR;
  }
}

void proc_blowing() {
  if (pressure_in - pressure_out > PRESSURE_THRESH) {
    dead_time_start = millis();
    target_state = STATE_PRESSURED;
    state = STATE_TRANS;
  }
  else {
    digitalWrite(FAN, HIGH); //blow baby
  }
}

void proc_pressured() {
  if (pressure_in - pressure_out < PRESSURE_THRESH) {
    digitalWrite(FAN, LOW);
    target_state = STATE_IDLE;
    state = STATE_TRANS;
  }
}

void display_data() {
  Serial.print(F("Temperature = "));
  Serial.print(bmp.readTemperature());
  Serial.print(" C");

  Serial.print(F("; Pressure = "));
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");
  Serial.print("State = ");
  Serial.println(state);
  Serial.print("pressure inside - pressure outside = ");
  Serial.println(pressure_in - pressure_out);
  
//  Serial.print(F("Approx altitude = "));
//  Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
//  Serial.println(" m");
  data_print_thresh = millis();
}

void loop() {
  pressure_in = bmp.readPressure();
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
    case STATE_TRANS:
      if (millis() - dead_time_start > DEAD_TIME) {
        state = target_state;
        dead_time_start = millis();
      }
      break;
    case STATE_ERROR:
      Serial.println("AAAArgh. In error");
      digitalWrite(FAN, LOW);
      break;
  }
  if (millis() - data_print_thresh > DATA_THRESH ) {
    display_data();
  }
  
}
