import serial
import csv

# Change 'COM3' to your Arduino's port
ser = serial.Serial('COM3', 9600)
print("Listening for attendance data...")

while True:
    try:
        line = ser.readline().decode('utf-8').strip()
        if "ID:" in line:
            # Data format: ID:1,2025-05-20T10:30:00
            data = line.replace("ID:", "").split(",")
            user_id = data[0]
            timestamp = data[1]
            
            with open('attendance.csv', 'a', newline='') as f:
                writer = csv.writer(f)
                writer.writerow([user_id, timestamp])
            
            print(f"User {user_id} logged at {timestamp}")
    except KeyboardInterrupt:
        break
