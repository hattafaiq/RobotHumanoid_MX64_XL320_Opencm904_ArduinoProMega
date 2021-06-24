//-------------------------------------------------------------------------------------
// HX711_ADC.h
// Arduino master library for HX711 24-Bit Analog-to-Digital Converter for Weigh Scales
// Olav Kallhovd sept2017
// Tested with      : HX711 asian module on channel A and YZC-133 3kg load cell
// Tested with MCU  : Arduino Nano
//-------------------------------------------------------------------------------------
// This is an example sketch on how to use this library for two ore more HX711 modules
// Settling time (number of samples) and data filtering can be adjusted in the config.h file

#include <HX711_ADC.h>
#include <EEPROM.h>

//pins:
const int HX711_dout_1 = 54; //mcu > HX711 no 1 dout pin
const int HX711_dout_2 = 56; //mcu > HX711 no 2 dout pin
const int HX711_dout_3 = 58; //mcu > HX711 no 3 dout pin
const int HX711_dout_4 = 60; //mcu > HX711 no 4 dout pin
const int HX711_dout_5 = 62; //mcu > HX711 no 5 dout pin
const int HX711_dout_6 = 64; //mcu > HX711 no 6 dout pin
const int HX711_dout_7 = 66; //mcu > HX711 no 7 dout pin
const int HX711_dout_8 = 68; //mcu > HX711 no 8 dout pin

const int HX711_sck = 52; //mcu > HX711 no 1 sck pin
//const int HX711_sck_2 = 7; //mcu > HX711 no 2 sck pin

//HX711 constructor (dout pin, sck pin)
HX711_ADC LoadCell_1(HX711_dout_1, HX711_sck); //HX711 1
HX711_ADC LoadCell_2(HX711_dout_2, HX711_sck); //HX711 2
HX711_ADC LoadCell_3(HX711_dout_3, HX711_sck); //HX711 3
HX711_ADC LoadCell_4(HX711_dout_4, HX711_sck); //HX711 4
HX711_ADC LoadCell_5(HX711_dout_5, HX711_sck); //HX711 5
HX711_ADC LoadCell_6(HX711_dout_6, HX711_sck); //HX711 6
HX711_ADC LoadCell_7(HX711_dout_7, HX711_sck); //HX711 7
HX711_ADC LoadCell_8(HX711_dout_8, HX711_sck); //HX711 8

const int calVal_eepromAdress_1 = 55; // eeprom adress for calibration value load cell 1 (4 bytes)
const int calVal_eepromAdress_2 = 57; // eeprom adress for calibration value load cell 2 (4 bytes)
const int calVal_eepromAdress_3 = 59;
const int calVal_eepromAdress_4 = 61;
const int calVal_eepromAdress_5 = 63;
const int calVal_eepromAdress_6 = 65;
const int calVal_eepromAdress_7 = 67;
const int calVal_eepromAdress_8 = 69;
unsigned long t = 0;

void setup() {
  Serial.begin(57600); delay(10);
  Serial.println();
  Serial.println("Starting...");

  float calibrationValue_1; // calibration value load cell 1
  float calibrationValue_2; // calibration value load cell 2
  float calibrationValue_3;
  float calibrationValue_4;
  float calibrationValue_5;
  float calibrationValue_6;
  float calibrationValue_7;
  float calibrationValue_8;
  
  calibrationValue_1 = 300.0;//696.0; 
  calibrationValue_2 = 300.0;//733.0; 
  calibrationValue_3 = 300.0;//733.0;
  calibrationValue_4 = 300.0;//733.0;
  calibrationValue_5 = 300.0;//733.0;
  calibrationValue_6 = 300.0;//733.0;
  calibrationValue_7 = 300.0;//733.0;
  calibrationValue_8 = 300.0;//733.0;
  
  LoadCell_1.begin();
  LoadCell_2.begin();
  LoadCell_3.begin();
  LoadCell_4.begin();
  LoadCell_5.begin();
  LoadCell_6.begin();
  LoadCell_7.begin();
  LoadCell_8.begin();
  
  unsigned long stabilizingtime = 2000; // tare preciscion can be improved by adding a few seconds of stabilizing time
  boolean _tare = true; //set this to false if you don't want tare to be performed in the next step
  byte loadcell_1_rdy = 0;
  byte loadcell_2_rdy = 0;
  byte loadcell_3_rdy = 0;
  byte loadcell_4_rdy = 0;
  byte loadcell_5_rdy = 0;
  byte loadcell_6_rdy = 0;
  byte loadcell_7_rdy = 0;
  byte loadcell_8_rdy = 0;
  
  while ((loadcell_1_rdy + loadcell_2_rdy + loadcell_3_rdy + loadcell_4_rdy + loadcell_5_rdy + loadcell_6_rdy + loadcell_7_rdy + loadcell_8_rdy) < 2) { //run startup, stabilization and tare, both modules simultaniously
    if (!loadcell_1_rdy) loadcell_1_rdy = LoadCell_1.startMultiple(stabilizingtime, _tare);
    if (!loadcell_2_rdy) loadcell_2_rdy = LoadCell_2.startMultiple(stabilizingtime, _tare);
    if (!loadcell_3_rdy) loadcell_3_rdy = LoadCell_3.startMultiple(stabilizingtime, _tare);
    if (!loadcell_4_rdy) loadcell_4_rdy = LoadCell_4.startMultiple(stabilizingtime, _tare);
    if (!loadcell_5_rdy) loadcell_5_rdy = LoadCell_5.startMultiple(stabilizingtime, _tare);
    if (!loadcell_6_rdy) loadcell_6_rdy = LoadCell_6.startMultiple(stabilizingtime, _tare);
    if (!loadcell_7_rdy) loadcell_7_rdy = LoadCell_7.startMultiple(stabilizingtime, _tare);
    if (!loadcell_8_rdy) loadcell_8_rdy = LoadCell_8.startMultiple(stabilizingtime, _tare);
  }
  if (LoadCell_1.getTareTimeoutFlag()) {
    Serial.println("Timeout, check MCU>HX711 no.1 wiring and pin designations");
  }
  if (LoadCell_2.getTareTimeoutFlag()) {
    Serial.println("Timeout, check MCU>HX711 no.2 wiring and pin designations");
  }
  if (LoadCell_3.getTareTimeoutFlag()) {
    Serial.println("Timeout, check MCU>HX711 no.3 wiring and pin designations");
  }
  if (LoadCell_4.getTareTimeoutFlag()) {
    Serial.println("Timeout, check MCU>HX711 no.4 wiring and pin designations");
  }
  if (LoadCell_5.getTareTimeoutFlag()) {
    Serial.println("Timeout, check MCU>HX711 no.5 wiring and pin designations");
  }
  if (LoadCell_6.getTareTimeoutFlag()) {
    Serial.println("Timeout, check MCU>HX711 no.6 wiring and pin designations");
  }
  if (LoadCell_7.getTareTimeoutFlag()) {
    Serial.println("Timeout, check MCU>HX711 no.7 wiring and pin designations");
  }
  if (LoadCell_8.getTareTimeoutFlag()) {
    Serial.println("Timeout, check MCU>HX711 no.8 wiring and pin designations");
  }
  LoadCell_1.setCalFactor(calibrationValue_1); // user set calibration value (float)
  LoadCell_2.setCalFactor(calibrationValue_2); // user set calibration value (float)
  LoadCell_3.setCalFactor(calibrationValue_3);
  LoadCell_4.setCalFactor(calibrationValue_4);
  LoadCell_5.setCalFactor(calibrationValue_5);
  LoadCell_6.setCalFactor(calibrationValue_6);
  LoadCell_7.setCalFactor(calibrationValue_7);
  LoadCell_8.setCalFactor(calibrationValue_8);
  
  Serial.println("Startup is complete");
}

void loop() {
  static boolean newDataReady = 0;
  const int serialPrintInterval = 0; //increase value to slow down serial print activity

  // check for new data/start next conversion:
  if (LoadCell_1.update()) newDataReady = true;
  LoadCell_2.update();
  LoadCell_3.update();
  LoadCell_4.update();
  LoadCell_5.update();
  LoadCell_6.update();
  LoadCell_7.update();
  LoadCell_8.update();

  //get smoothed value from data set
  if ((newDataReady)) {
    if (millis() > t + serialPrintInterval) {
      float a = LoadCell_1.getData();
      float b = LoadCell_2.getData();
      float c = LoadCell_3.getData();
      float d = LoadCell_4.getData();
      float e = LoadCell_5.getData();
      float f = LoadCell_6.getData();
      float g = LoadCell_7.getData();
      float h = LoadCell_8.getData();
      //Serial.println("Data Kiri");
      Serial.print("Load_cell 1= ");
      Serial.println(a);
      Serial.print("Load_cell 2=");
      Serial.println(b);
      Serial.print("Load_cell 3=");
      Serial.println(c);
      Serial.print("Load_cell 4=");
      Serial.println(d);
      //Serial.println("Data Kanan");
      Serial.print("Load_cell 5=");
      Serial.println(e);
      Serial.print("Load_cell 6=");
      Serial.println(f);
      Serial.print("Load_cell 7=");
      Serial.println(g);
      Serial.print("Load_cell 8=");
      Serial.println(h);
      newDataReady = 0;
      t = millis();
    }
  }

  // receive command from serial terminal, send 't' to initiate tare operation:
  if (Serial.available() > 0) {
    char inByte = Serial.read();
    if (inByte == 't') {
      LoadCell_1.tareNoDelay();
      LoadCell_2.tareNoDelay();
      LoadCell_3.tareNoDelay();
      LoadCell_4.tareNoDelay();
      LoadCell_5.tareNoDelay();
      LoadCell_6.tareNoDelay();
      LoadCell_7.tareNoDelay();
      LoadCell_8.tareNoDelay();
    }
  }

  //check if last tare operation is complete
  if (LoadCell_1.getTareStatus() == true) {
    Serial.println("Tare load cell 1 complete");
  }
  if (LoadCell_2.getTareStatus() == true) {
    Serial.println("Tare load cell 2 complete");
  }
  if (LoadCell_3.getTareStatus() == true) {
    Serial.println("Tare load cell 2 complete");
  }
  if (LoadCell_4.getTareStatus() == true) {
    Serial.println("Tare load cell 2 complete");
  }
  if (LoadCell_5.getTareStatus() == true) {
    Serial.println("Tare load cell 2 complete");
  }
  if (LoadCell_6.getTareStatus() == true) {
    Serial.println("Tare load cell 2 complete");
  }
  if (LoadCell_7.getTareStatus() == true) {
    Serial.println("Tare load cell 2 complete");
  }
  if (LoadCell_8.getTareStatus() == true) {
    Serial.println("Tare load cell 2 complete");
  }

}
