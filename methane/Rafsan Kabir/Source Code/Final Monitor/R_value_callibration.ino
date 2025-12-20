const int MQ_PIN = A0;
const float R0 = 72.5; // Calibrated value in clean air

void setup() {
  Serial.begin(9600);
  Serial.println("--- MQ-07 Gas Monitor Starting ---");
}

void loop() {
  int raw_value = analogRead(MQ_PIN);
  float v_out = raw_value * (5.0 / 1023.0);
  

  float RS_gas = (5.0 - v_out) / v_out;
  
  // Ratio
  float ratio = RS_gas / R0;

  float ppm = 100 * pow(ratio, -1.53);

  Serial.print("Raw: ");
  Serial.print(raw_value);
  Serial.print(" | Ratio: ");
  Serial.print(ratio);
  Serial.print(" | CO: ");
  Serial.print(ppm);
  Serial.println(" PPM");

  if (ppm > 250) {
    Serial.println("!!! WARNING: HIGH CO LEVELS !!!");
  }

  delay(2000);
}