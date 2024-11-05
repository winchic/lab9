//this is the python gui file 

import tkinter as tk
import serial  # use pyserial to communicate with the microcontroller
import time

# function to start distance measurement
def start_measurement():
    global running
    running = True
    update_distance()

# function to stop distance measurement
def stop_measurement():
    global running
    running = False

# function to update the distance in the gui
def update_distance():
    if running:
        # read distance from the microcontroller (example code, adjust as needed)
        try:
            ser.write(b'S')  # send a command to start measurement
            distance = ser.readline().decode().strip()  # read the response
            distance_label.config(text=f"distance: {distance} cm")
        except:
            distance_label.config(text="error reading distance")

        # schedule the next update
        window.after(200, update_distance)  # update every 200 ms

# initialize the gui window
window = tk.Tk()
window.title("ping))) distance measurement")

# add a label to display the distance
distance_label = tk.Label(window, text="distance: -- cm", font=("Helvetica", 16))
distance_label.pack(pady=20)

# add start and stop buttons
start_button = tk.Button(window, text="start", command=start_measurement)
start_button.pack(pady=10)

stop_button = tk.Button(window, text="stop", command=stop_measurement)
stop_button.pack(pady=10)

# serial communication setup (adjust the port and baud rate)
ser = serial.Serial('COM3', 9600)  # replace 'COM3' with your serial port
running = False

# run the tkinter main loop
window.mainloop()
