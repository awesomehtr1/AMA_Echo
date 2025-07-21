// This sketch permanently changes the I2C address of TF-Luna from 0x10 to 0x1E (30 in decimal)
// and saves it to EEPROM so the change persists after power cycles.

#include <Wire.h>

#define OLD_ADDRESS 0x10  // Default TF-Luna I2C address
#define NEW_ADDRESS 0x18  // Desired new I2C address

void setup() {
  Wire.begin(); // Start I2C as master
  Serial.begin(115200);
  delay(100);
  Serial.println("Changing TF-Luna I2C address...");

  // Step 1: Set new address (not yet saved to EEPROM)
  Wire.beginTransmission(OLD_ADDRESS);
  Wire.write(0x5A); // Frame header
  Wire.write(0x05); // Data length
  Wire.write(0x0B); // Function: Set I2C address
  Wire.write(NEW_ADDRESS); // New I2C address
  Wire.write(0x00); // Checksum (not used here)
  Wire.endTransmission();
  delay(100); // Wait for TF-Luna to process

  // Step 2: Save new address to EEPROM
  Wire.beginTransmission(NEW_ADDRESS);
  Wire.write(0x5A); // Frame header
  Wire.write(0x04); // Data length
  Wire.write(0x11); // Function: Save parameters to EEPROM
  Wire.write(0x6F); // Save all parameters
  Wire.endTransmission();
  delay(100); // Allow EEPROM write to complete

  Serial.print("Address changed and saved to EEPROM. New address: 0x");
  Serial.println(NEW_ADDRESS, HEX);
}

void loop() {
  // Nothing needed in loop
}