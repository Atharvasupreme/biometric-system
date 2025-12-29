import serial
import csv
from datetime import datetime

# Configure the serial port (Virtual COM port for simulation)
ser = serial.Serial('COM3', 9600) 

def log_attendance(user_id):
    now = datetime.now()
    date_string = now.strftime("%Y-%m-%d")
    time_string = now.strftime("%H:%M:%S")
    
    with open('attendance_log.csv', 'a', newline='') as file:
        writer = csv.writer(file)
        writer.writerow([user_id, date_string, time_string])
    print(f"Logged: User {user_id} at {time_string}")

while True:
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8').strip()
        if "LOG_DATA:ID_" in line:
            user_id = line.split('_')[-1]
            log_attendance(user_id)
