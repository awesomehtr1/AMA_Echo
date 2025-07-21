#include "Wire.h"    
#include "TFLI2C.h"  

TFLI2C sensor;

void setup() {
  Serial.begin(9600);  
  Wire.begin(); 

  pinMode(2, OUTPUT);  // For dist2 (0x10)
  pinMode(3, OUTPUT);  // For dist1 (0x18)
}

void loop() {
  int16_t dist1, dist2;
  bool ok1 = sensor.getData(dist2, 0x10);  // dist2 from 0x10
  bool ok2 = sensor.getData(dist1, 0x18);  // dist1 from 0x18

  // Output to serial
  Serial.print("dist2: ");
  Serial.print(ok1 ? String(dist2) : "fail");
  Serial.print(" | dist1: ");
  Serial.println(ok2 ? String(dist1) : "fail");

  // Control pins
  if (ok1 && dist2 < 50) {
    digitalWrite(2, HIGH);
  } else {
    digitalWrite(2, LOW);
  }

  if (ok2 && dist1 < 50) {
    digitalWrite(3, HIGH);
  } else {
    digitalWrite(3, LOW);
  }

  delay(100);
}
