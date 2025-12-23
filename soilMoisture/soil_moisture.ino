#include <DHT.h>

// -------- DHT11 --------
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// -------- Soil Probe --------
// Wiring:
// D7 -> probe pin 1 (power control)
// A0 -> probe pin 2 (analog read)
// 10k resistor between A0 and GND
const int PROBE_POWER_PIN = 7;
const int PROBE_ADC_PIN   = A0;

// Your rover calibration (Option B)
int DRY_RAW = 41;    // air/dry
int WET_RAW = 298;   // wet reference

int readSoilRawAveraged(int samples = 25) {
  long sum = 0;

  digitalWrite(PROBE_POWER_PIN, HIGH);
  delay(15);

  for (int i = 0; i < samples; i++) {
    sum += analogRead(PROBE_ADC_PIN);
    delay(5);
  }

  digitalWrite(PROBE_POWER_PIN, LOW);
  return (int)(sum / samples);
}

int rawToPercent(int raw) {
  int low  = min(DRY_RAW, WET_RAW);
  int high = max(DRY_RAW, WET_RAW);
  raw = constrain(raw, low, high);

  float pct = 100.0f * (raw - DRY_RAW) / (float)(WET_RAW - DRY_RAW);
  if (pct < 0) pct = 0;
  if (pct > 100) pct = 100;
  return (int)(pct + 0.5f);
}

void setup() {
  Serial.begin(9600);

  pinMode(PROBE_POWER_PIN, OUTPUT);
  digitalWrite(PROBE_POWER_PIN, LOW);

  dht.begin();

  Serial.println("Soil + DHT11 (Option B: Relative Moisture)");
}

void loop() {
  int raw = readSoilRawAveraged(25);
  int soilPct = rawToPercent(raw);

  float t = dht.readTemperature();
  float h = dht.readHumidity();

  Serial.print("Soil raw=");
  Serial.print(raw);
  Serial.print(" soil=");
  Serial.print(soilPct);
  Serial.print("%");

  if (isnan(t) || isnan(h)) {
    Serial.println(" | DHT: failed");
  } else {
    Serial.print(" | T=");
    Serial.print(t);
    Serial.print("C H=");
    Serial.print(h);
    Serial.println("%");
  }

  delay(500);
}
