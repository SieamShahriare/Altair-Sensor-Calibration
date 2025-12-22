# Temperature Sensor (ds18b20)

## Hardware

- Sensor: DS18B20
- Microcontroller:
- Pins Used:

### Documentation
DS18B20 Temperature Sensor Guide
About DS18B20

The DS18B20 is a digital temperature sensor that communicates using the OneWire protocol.
1.Accurate to ±0.5°C
2.Requires only one data wire plus power
3.Each sensor has a unique 64-bit serial code
4.Temperature range: -55°C to +125°C
Pin Configuration
DS18B20 Pin	Arduino Pin
DATA	D2
VCC	5V
GND	GND
Code Overview
This project reads temperature from a DS18B20 sensor and applies calibration adjustments for more accurate readings.
What the Code Does
1.Initializes the sensor
2.Requests temperature reading
3.Checks if sensor is connected
4.Applies calibration: (raw × 1.005025) - 0.26633
5. Displays results on Serial Monitor

Calibration Values
gain = 1.005025 → Multiplies raw temperature
offset = -0.26633 → Adjusts final value
These values fine-tune the sensor readings for better accuracy.
Expected Output

On Serial Monitor (9600 baud):
Raw: 25.50 C | Cal: 25.37 C
Raw: 25.52 C | Cal: 25.39 C
...

Common Issues & Solutions
Problem: "Sensor not detected."

Check:
1.Wiring connections (VCC, GND, DATA)
2.Pull-up resistor on DATA line
3.Sensor orientation
Common Issues & Solutions
Problem: "Sensor not detected."

Problem: Strange readings (-127°C)

Solution:
1.Check DATA pin connection
2.Ensure proper power supply
3.Verify OneWire library is installed

How It Works
1.OneWire protocol allows multiple sensors on one pin
2.Digital reading → No analog conversion errors
3.Built-in calibration improves accuracy
4.Auto-detection of sensor disconnection

Applications
1. Room temperature monitoring
2.Weather stations
3.Temperature-controlled systems
4.Data logging projects

Note: The DS18B20 is waterproof when using the encapsulated version, making it suitable for outdoor or wet environments.
