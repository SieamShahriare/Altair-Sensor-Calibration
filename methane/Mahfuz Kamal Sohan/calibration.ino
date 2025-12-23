// MQ-4 CALIBRATION SCRIPT
const int MQ_PIN = A0;
const float RL = 10000.0;

void setup()
{
  Serial.begin(9600);
  Serial.println("MQ-4 CALIBRATION STARTING...");
  Serial.println("Ensure sensor is in FRESH AIR.");
  delay(3000);
}

void loop()
{
  int adc = analogRead(MQ_PIN);
  if (adc > 0)
  {
    float Vout = adc * (5.0 / 1023.0);
    float Rs = RL * (5.0 - Vout) / Vout;

    // Clean air: Rs/R0 ≈ 4.4
    float R0 = Rs / 4.4;

    Serial.print("Current Rs: ");
    Serial.print(Rs);
    Serial.print(" | SUGGESTED R0: ");
    Serial.println(R0);
  }
  else
  {
    Serial.println("Error: No signal from sensor.");
  }

  delay(2000);
}
