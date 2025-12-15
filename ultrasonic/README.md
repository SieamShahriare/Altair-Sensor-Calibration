# Ultrasonic Sensor (HCRSR04) 

## Overview 

This folder contains a simple Arduino-based distance-measurement project using an HCRSR04 (HC-SR04 compatible) ultrasonic sensor. The sensor emits an ultrasonic pulse and measures the time it takes for the echo to return; the microcontroller converts this time-of-flight into distance.



---

## Parts & Requirements 

- HCRSR04 (HC-SR04 compatible) ultrasonic distance sensor
- Arduino board (I used Mega 2560)
- Jumper wires and a breadboard 


## Pinout (HCRSR04 / HC-SR04) 

- VCC  : +5V
- TRIG : Digital output from microcontroller 
- ECHO : Digital input to microcontroller 
- GND  : Ground

see `ultrasonic_sensor.png` for visual reference.


## How it works 

1. The MCU sets TRIG HIGH for ~10 microseconds → module sends an ultrasonic burst.
2. The ECHO pin goes HIGH while the transmitted sound wave travels, hits an object, and returns.
3. The pulse width on ECHO (in microseconds) equals the round-trip time.
4. Distance is calculated as: distance = (time * speed_of_sound) / 2.

- Typical speed of sound used: ~343 m/s (0.0343 cm/µs at 20°C). The commonly-used constant in many examples is 0.034 (cm/µs); you may use a more precise value and compensate for temperature if accuracy is important.

## Wiring (example) 📎

- `VCC` → `5V`
- `GND` → `GND`
- `TRIG` → digital pin 6
- `ECHO` → digital pin 7 

Diagram (textual): Arduino 5V —>VCC, Arduino GND —>GND, D6 —>TRIG, D7 —>ECHO
see `wiring.png` for visual reference.

## Code (see `ultrasonic.ino`)

The repository includes `ultrasonic.ino` — a compact example adapted from common HC-SR04 code. Upload it to your Arduino and open the Serial Monitor at 9600 baud.

Key points in the sketch:

- TRIG is held LOW, then HIGH for 10 µs to initiate a pulse. 
- `pulseIn(echo, HIGH)` measures the round-trip time in microseconds.
- Distance (cm) is computed from the measured time and printed.

## Calculation:

distance = totaltime * 0.034 / 2; 

Where 0.034 is the speed of sound in cm/µs (approx.).

## Accuracy & Calibration 

- Ambient temperature affects the speed of sound; for precise measurements, adjust the constant for local temperature.
- Objects that poorly reflect ultrasound (soft, angled, or absorptive surfaces) can give unreliable readings.
- Minimum reliable distance for HC-SR04 is usually a few centimeters; maximum is commonly ~400 cm but varies with sensor and environment.

## Troubleshooting 

- No values or constant 0: check wiring (especially TRIG/ECHO and power).
- Sporadic/noisy values: add small delays, average multiple readings, avoid obstructions or reflective interference.



## How to run 

1. Connect the sensor as above.
2. Open `ultrasonic.ino` in the Arduino IDE and upload to your board.
3. Open the Serial Monitor at 9600 baud to view measurements.


---

Author: Azmain 