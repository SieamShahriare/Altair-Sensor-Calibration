// MQ-4 Monitoring
const int MQ_PIN = A0;
const float RL = 10000.0;
const float R0 = 27157.65;     //calibrated R0

float readRs()
{
  int adc = analogRead(MQ_PIN);
  if (adc == 0) return 0;

  float Vout = adc * (5.0 / 1023.0);
  return RL * (5.0 - Vout) / Vout;
}

void setup()
{
  Serial.begin(9600);
  Serial.println("MQ-4 Gas Monitor: ACTIVE");
}

void loop()
{
  float Rs = readRs();
  float ratio = Rs / R0;

  Serial.print("Ratio: ");
  Serial.print(ratio);

  if (ratio < 1.0)
  {
    Serial.println(" | [!!!] DANGER: Gas Leak");
  }
  else if (ratio < 3.0)
  {
    Serial.println(" | [!] WARNING: Gas Detected");
  }
  else
  {
    Serial.println(" | [OK] Clean Air");
  }

  delay(1000);
}
