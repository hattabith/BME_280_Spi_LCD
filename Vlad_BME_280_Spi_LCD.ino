/*

MIT License

Copyright (c) 2023 Dmytro Myronov <hattabith@gmail.com>

Connecting the BME280 Sensor:
Sensor              ->  Board
-----------------------------
Vin (Voltage In)    ->  5V
Gnd (Ground)        ->  Gnd
SDA (Serial Data)   ->  A4 on Arduno NANO
SCK (Serial Clock)  ->  A5 on Arduno NANO

*/

#include <BME280I2C.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>


LiquidCrystal_I2C lcd(0x27, 20, 4);                   // Set LCD
BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);  // Set temperature unit
BME280::PresUnit presUnit(BME280::PresUnit_torr);     // Set pressure unit


#define Serial_Speed 115200
#define Refresh_Period_LCD 1000
#define Refresh_Period_Serial 2000
#define Sensor_Period 500

uint32_t tmrLCD = 0;     // Timer LCD
uint32_t tmrSerial = 0;  // Timer Serial
uint32_t tmrSensor = 0;  // Timer Sensor

float temp(NAN), hum(NAN), pres(NAN);  // Variables for temperature, humidity and pressure

/* Recommended Modes -
   Based on Bosch BME280I2C environmental sensor data sheet.

Weather Monitoring :
   forced mode, 1 sample/minute
   pressure ×1, temperature ×1, humidity ×1, filter off
   Current Consumption =  0.16 μA
   RMS Noise = 3.3 Pa/30 cm, 0.07 %RH
   Data Output Rate 1/60 Hz

Humidity Sensing :
   forced mode, 1 sample/second
   pressure ×0, temperature ×1, humidity ×1, filter off
   Current Consumption = 2.9 μA
   RMS Noise = 0.07 %RH
   Data Output Rate =  1 Hz

Indoor Navigation :
   normal mode, standby time = 0.5ms
   pressure ×16, temperature ×2, humidity ×1, filter = x16
   Current Consumption = 633 μA
   RMS Noise = 0.2 Pa/1.7 cm
   Data Output Rate = 25Hz
   Filter Bandwidth = 0.53 Hz
   Response Time (75%) = 0.9 s


Gaming :
   normal mode, standby time = 0.5ms
   pressure ×4, temperature ×1, humidity ×0, filter = x16
   Current Consumption = 581 μA
   RMS Noise = 0.3 Pa/2.5 cm
   Data Output Rate = 83 Hz
   Filter Bandwidth = 1.75 Hz
   Response Time (75%) = 0.3 s

*/
BME280I2C::Settings settings(
  BME280::OSR_X1,
  BME280::OSR_X1,
  BME280::OSR_X1,
  BME280::Mode_Normal,
  BME280::StandbyTime_50ms,
  BME280::Filter_Off,
  BME280::SpiEnable_False,
  BME280I2C::I2CAddr_0x76  // I2C address. I2C specific.
);

BME280I2C bme(settings);  // Set BME280


void setup() {
  Serial.begin(Serial_Speed);  //  Init serial speed

  while (!Serial) {}  // Wait serial

  Wire.begin();  // Init Wire

  lcd.init();  // Init LCD
  lcd.backlight();

  lcd.clear();

  while (!bme.begin())  // Init BME280
  {
    Serial.println("BME280 not found or brocken");
    lcd.setCursor(0, 0);
    lcd.print("BME280 not found or brocken");
    delay(5000);
  }
  delay(2000);
  lcd.clear();
}

void loop() {
  if (millis() - tmrSensor >= Sensor_Period) {
    tmrSensor = millis();
    bme.read(pres, temp, hum, tempUnit, presUnit);
  }
  if (millis() - tmrLCD >= Refresh_Period_LCD) {
    tmrLCD = millis();
    OutLCD();
  }
  if (millis() - tmrSerial >= Refresh_Period_Serial) {
    tmrSerial = millis();
    OutSerial();
  }
}

void OutLCD() {
  lcd.setCursor(0, 0);
  if (temp > 0) {
    lcd.print("Temperature: ");  // TODO if < 0 draw "-"
    lcd.setCursor(13, 0);
    lcd.print(temp);
    lcd.setCursor(18, 0);
    lcd.print("\xDF");
    lcd.print("C");
  }
  else{
    lcd.print("Temperature: ");  // TODO if < 0 draw "-"
    lcd.setCursor(12, 0);
    lcd.print(temp);
    lcd.setCursor(18, 0);
    lcd.print("\xDF");
    lcd.print("C");
  }

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.setCursor(13, 1);
  lcd.print(hum);
  lcd.setCursor(18, 1);
  lcd.print(" %");

  lcd.setCursor(0, 2);
  lcd.print("Pressure: ");
  lcd.setCursor(10, 2);
  lcd.print(pres);
    lcd.setCursor(16, 2);
  lcd.print("Torr");
}

void OutSerial() {
  Serial.print(temp);
  Serial.print(",");
  Serial.println(hum);
}