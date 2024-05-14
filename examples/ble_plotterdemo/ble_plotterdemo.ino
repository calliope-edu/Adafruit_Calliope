// Example for using Adafruit Bluefruit App to plot accelerometer data

// BLE Serial code Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Adafruit_Calliope.h>
// Add accelerometer support
#include "Wire.h"
#include "MMA8653.h"

Adafruit_Calliope calliope;
MMA8653 accel;

void setup() {
  Serial.begin(115200);

  Serial.println("Plotter demo ready!");

  accel.begin(false, 2); // 8-bit mode, 2g range
    
  // custom services and characteristics can be added as well
  calliope.BTLESerial.setLocalName("calliope");
  calliope.BTLESerial.begin();

  // Start LED matrix driver after radio (required)
  calliope.begin();
}

void loop() {
  calliope.BTLESerial.poll();
  
  accel.update();

  // print the data on serial port
  Serial.print(accel.getX());    Serial.print(", ");
  Serial.print(accel.getY());    Serial.print(", ");
  Serial.println(accel.getZ());

  // send it over bluetooth
  calliope.BTLESerial.print(accel.getX());   
  calliope.BTLESerial.print(",");
  calliope.BTLESerial.print(accel.getY());   
  calliope.BTLESerial.print(",");
  calliope.BTLESerial.println(accel.getZ());

  delay(100);
}
