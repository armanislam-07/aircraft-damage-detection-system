#include <bluefruit.h>
#include <Wire.h>
#include "INA226.h"

BLEUart bleuart;

INA226 INA(0x40); //address where of the INA internal chip for I2C 

typedef struct __attribute__((packed)) {
  float r;
  float v;
  float i;
} Packet;

Packet p;

void setup() {
  Serial.begin(115200); 
  //Future to impliment time stamps
  // Initialize BLE
  Bluefruit.begin();
  Bluefruit.setTxPower(4); // MAX TX power for max range
  Bluefruit.setName("SMART_MAT");
  bleuart.begin();
  Wire.begin();

  // Advertising setup
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addService(bleuart);
  Bluefruit.ScanResponse.addName();
  Bluefruit.Advertising.start(0); // 0 = forever
  Serial.println("BLE UART Ready");


  if (!INA.begin() )
  {
    Serial.println("Could not connect. Fix and Reboot");
    bleuart.print("INA226 Init Failed. Fix and Reboots"); //make a case here that if it cannot begin we loop into this print statment like we keep printing this and shut off after few seconds 
  }

  INA.setAverage(2);
  delay(100);
  INA.setMaxCurrentShunt(0.5, 0.1);

}

void loop() {
  // Only send if connected
  if (Bluefruit.connected()) {
    float bv = INA.getBusVoltage();
    float cu = INA.getCurrent_mA();
    float res = 0;
    if(cu != 0) 
    {
      res = bv / (cu / 1000);
    }
    else
    {
      res = -1;
    }
    
    p.r = res;
    p.v = bv;
    p.i = cu;
  

    bleuart.write((uint8_t*)&p, sizeof(p)); // Send over BLE
    //Serial.print(msg); // Debug
    //Serial.println();
    delay(500);
  }
}