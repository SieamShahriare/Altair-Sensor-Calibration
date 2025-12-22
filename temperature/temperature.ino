// Include library for OneWire communication protocol
#include <OneWire.h>

// Include library for DS18B20 temperature sensor
#include <DallasTemperature.h>

// Define the Arduino pin connected to the sensor data wire
#define ONE_WIRE_BUS 2

// Create OneWire object to communicate with sensor
OneWire oneWire(ONE_WIRE_BUS);

// Create DallasTemperature object to control the sensor
DallasTemperature sensors(&oneWire);

// Calibration values to adjust raw temperature readings
float gain   = 1.005025;    // Multiply raw temperature by this
float offset = -0.26633;    // Add this to the result

// Setup function runs once when Arduino starts
void setup() {
  // Start serial communication at 9600 bits per second
  Serial.begin(9600);
  
  // Initialize the temperature sensor
  sensors.begin();
}

// Loop function runs repeatedly forever
void loop() {
  // Tell sensor to measure temperature now
  sensors.requestTemperatures();
  
  // Read temperature from first sensor (index 0)
  float t = sensors.getTempCByIndex(0);

  // Check if sensor is not connected or not responding
  if (t == DEVICE_DISCONNECTED_C) {
    // Show error message on serial monitor
    Serial.println("Sensor not detected.");
    
    // Wait 1 second before trying again
    delay(1000);
    
    // Exit loop function early
    return;
  }

  // Apply calibration: multiply raw temp by gain, then add offset
  float t_cal = gain * t + offset;

  // Print raw and calibrated temperatures to serial monitor
  Serial.print("Raw: "); Serial.print(t, 2);      // Print raw temp with 2 decimals
  Serial.print(" C | Cal: "); Serial.print(t_cal, 2);  // Print calibrated temp
  Serial.println(" C");  // End line

  // Wait 1 second before taking next reading
  delay(1000);
}