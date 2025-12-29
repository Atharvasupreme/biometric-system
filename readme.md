# Biometric Attendance System using Arduino

A standalone biometric attendance system that identifies users via fingerprint and logs attendance with real-time timestamps.

## Features
- Fingerprint identification using R307/AS608 sensor.
- Real-time clock (DS3231) for accurate logging.
- I2C LCD interface for user feedback.
- Python-based data logger to save attendance in Excel/CSV.

## Hardware Required
- Arduino Uno/Nano
- AS608 Optical Fingerprint Sensor
- DS3231 RTC Module
- 16x2 I2C LCD Display
- Active Buzzer

## How to Use
1. Upload `Enroll_Finger.ino` to register your fingerprints.
2. Upload `Attendance_System.ino` for daily operation.
3. Run `logger.py` on your PC to save data to `attendance.csv`.
