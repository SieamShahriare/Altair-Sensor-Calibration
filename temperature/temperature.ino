#include <OneWire.h>
#include <DallasTemperature.h>
const int SENSOR_PIN = 2;
OneWire sensorWire(SENSOR_PIN);
DallasTemperature tempSensor(&sensorWire);

const float MULTIPLIER = 1.005;  
const float ADJUSTMENT = -0.266; 

void setup() {
  Serial.begin(9600);
  tempSensor.begin();
  Serial.println("Sensor ready!!");
}

void loop() {
  tempSensor.requestTemperatures();
  float measuredTemp = tempSensor.getTempCByIndex(0);
  if (measuredTemp == DEVICE_DISCONNECTED_C) {
    Serial.println("Error: No sensor found");
    delay(1000);
    return;
  }
  float adjustedTemp = (measuredTemp * MULTIPLIER) + ADJUSTMENT;
  Serial.print("Measured: ");
  Serial.print(measuredTemp);
  Serial.print("°C → Adjusted: ");
  Serial.print(adjustedTemp);
  Serial.println("°C");

  delay(1000);
}
