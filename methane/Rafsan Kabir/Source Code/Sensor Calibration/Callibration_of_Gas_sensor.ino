const int mq07_pin = A0;

void setup() {
  Serial.begin(9600);
  Serial.println("Warming up MQ-07 for CO detection...");
}

void loop() {
  float sensorValue = 0;
  for(int x = 0 ; x < 100 ; x++) {
    sensorValue += analogRead(mq07_pin);
    delay(10);
  }
  sensorValue /= 100.0;

  float sensor_volt = sensorValue * (5.0 / 1023.0);
  float RS_air = (5.0 - sensor_volt) / sensor_volt; 
  

  float R0 = RS_air / 27.0; 

  Serial.print("MQ-07 R0 Value: ");
  Serial.println(R0);
  delay(2000);
}