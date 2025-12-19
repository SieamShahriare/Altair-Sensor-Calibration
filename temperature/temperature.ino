#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Assumed calibration from your readings + assumed references
float gain   = 1.005025;
float offset = -0.26633;

void setup() {
  Serial.begin(9600);
  sensors.begin();
}

void loop() {
  sensors.requestTemperatures();
  float t = sensors.getTempCByIndex(0);

  if (t == DEVICE_DISCONNECTED_C) {
    Serial.println("Sensor not detected.");
    delay(1000);
    return;
  }

  float t_cal = gain * t + offset;

  Serial.print("Raw: "); Serial.print(t, 2);
  Serial.print(" C | Cal: "); Serial.print(t_cal, 2);
  Serial.println(" C");

  delay(1000);
}
