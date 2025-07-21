#include "Wire.h"    
#include "TFLI2C.h"  

TFLI2C sensor;

void setup() {
  Serial.begin(9600);  
  Wire.begin();          
}

void loop() {
  int16_t dist1, dist2;
  bool ok1 = sensor.getData(dist1, 0x10);
  bool ok2 = sensor.getData(dist2, 0x18);

  Serial.print("dist2: ");
  Serial.print(ok1 ? String(dist1) : "fail");
  Serial.print(" | dist1: ");
  Serial.println(ok2 ? String(dist2) : "fail");

  delay(100);
}
