#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
uint8_t id;

void setup() {
  Serial.begin(9600);
  finger.begin(57600);
  if (finger.verifyPassword()) { Serial.println("Sensor Found!"); }
}

void loop() {
  Serial.println("Ready to enroll a finger. Please type the ID # (1-127) you want to save this finger as...");
  id = readnumber();
  if (id == 0) return;
  while (!getFingerprintEnroll());
}

// (Standard enrollment logic to capture image twice and store in flash)
uint8_t readnumber(void) {
  uint8_t num = 0;
  while (num == 0) {
    while (! Serial.available());
    num = Serial.parseInt();
  }
  return num;
}

uint8_t getFingerprintEnroll() {
  int p = -1;
  Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
  while (p != FINGERPRINT_OK) { p = finger.getImage(); }
  p = finger.image2Tz(1);
  Serial.println("Remove finger");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) { p = finger.getImage(); }
  Serial.println("Place same finger again");
  p = -1;
  while (p != FINGERPRINT_OK) { p = finger.getImage(); }
  p = finger.image2Tz(2);
  p = finger.createModel();
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) { Serial.println("Stored!"); return true; }
  return false;
}
