#include <Adafruit_Fingerprint.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS3231 rtc;

void setup() {
  Serial.begin(9600);
  lcd.init(); lcd.backlight();
  finger.begin(57600);
  rtc.begin();
  lcd.print("Scan Finger...");
}

void loop() {
  int id = getFingerprintID();
  if (id > 0) {
    DateTime now = rtc.now();
    lcd.clear();
    lcd.print("ID: "); lcd.print(id);
    lcd.setCursor(0,1);
    lcd.print("Logged!");
    
    // IMPORTANT: Sending to Python Logger
    Serial.print("ID:"); Serial.print(id);
    Serial.print(","); Serial.println(now.timestamp());
    
    delay(3000);
    lcd.clear(); lcd.print("Scan Finger...");
  }
}

int getFingerprintID() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK) return -1;
  p = finger.image2Tz();
  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK) return -1;
  return finger.fingerID;
}
