#include <DHT.h>

// -------- DHT11 --------
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// -------- Soil Probe --------
const int PROBE_POWER_PIN = 7;
const int PROBE_ADC_PIN   = A0;

// Your rover calibration (Option B)
int DRY_RAW = 41;    // air/dry
int WET_RAW = 298;   // your wet reference

// -------- Rover output --------
const int WET_FLAG_PIN = 9; // connect to rover controller input/LED

// Hysteresis thresholds (soil%)
const int WET_ON_AT  = 70;  // enter WET mode
const int WET_OFF_AT = 50;  // exit WET mode

// Debounce (how many consecutive confirmations needed)
const int CONFIRM_COUNT = 3;

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

  pinMode(WET_FLAG_PIN, OUTPUT);
  digitalWrite(WET_FLAG_PIN, LOW);

  dht.begin();

  Serial.println("Rover Soil + DHT11 (Wet/Dry decision with hysteresis)");
}

void loop() {
  static bool wetMode = false;
  static int wetConfirm = 0;
  static int dryConfirm = 0;

  int raw = readSoilRawAveraged(25);
  int soilPct = rawToPercent(raw);

  float t = dht.readTemperature();
  float h = dht.readHumidity();

  // --- Hysteresis + confirmation ---
  if (!wetMode) {
    if (soilPct >= WET_ON_AT) {
      wetConfirm++;
      if (wetConfirm >= CONFIRM_COUNT) {
        wetMode = true;
        wetConfirm = 0;
        dryConfirm = 0;
      }
    } else {
      wetConfirm = 0;
    }
  } else {
    if (soilPct <= WET_OFF_AT) {
      dryConfirm++;
      if (dryConfirm >= CONFIRM_COUNT) {
        wetMode = false;
        dryConfirm = 0;
        wetConfirm = 0;
      }
    } else {
      dryConfirm = 0;
    }
  }

  digitalWrite(WET_FLAG_PIN, wetMode ? HIGH : LOW);

  // --- Print ---
  Serial.print("Soil raw=");
  Serial.print(raw);
  Serial.print(" soil=");
  Serial.print(soilPct);
  Serial.print("%  Ground=");
  Serial.print(wetMode ? "WET" : "DRY");

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
