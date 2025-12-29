#include <Adafruit_Fingerprint.h>

// Simulating the sensor on Software Serial
SoftwareSerial mySerial(2, 3); 
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup() {
  Serial.begin(9600);
  while (!Serial); 
  Serial.println("--- Biometric Attendance System ---");
  
  // Initialize sensor
  finger.begin(57600);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
  }
}

void loop() {
  Serial.println("Waiting for valid finger...");
  int id = getFingerprintID(); // Function to scan
  
  if (id != -1) {
    // When a match is found, send ID to Serial
    // The Python script will catch this and log it
    Serial.print("LOG_DATA:ID_");
    Serial.println(id);
    delay(5000); // Prevent duplicate logs
  }
  delay(50); 
}

int getFingerprintID() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK) return -1;

  // Found a match!
  return finger.fingerID;
}
