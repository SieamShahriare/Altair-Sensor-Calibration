#include "utils.h"

//PIN DEFINITIONS
const int UV_OUT = A4;      //ML8511 OUT pin
const int REF_3V3 = A3;     //Arduino UNO 3.3V pin (ADC reference)

/*
CALIBRATION COEFFICIENTS
from regression using atmospheric UV index data:
*/
float m = 3.27;    //slope
float c = -0.1;   //offset

void setup(){
  Serial.begin(9600);
}

void loop(){
  //READ SENSOR AND REFERENCE
  int uv = avgAnalogRead(UV_OUT, 8);     //Sensor ADC reading
  int ref = avgAnalogRead(REF_3V3, 8);   //3.3V ADC reading

  //SELF CALIBRATION
  float outputVoltage = 3.3 / (float)ref * (float)uv;  //Converts ADC ratio into true sensor voltage

  //VOLTAGE -> RAW UV
  float uvRaw = outputVoltage - 1.0;   //ML8511 outputs ~1.0V even at zero UV, so substract the baseline
  if (uvRaw < 0)    //Convert negative values to zero
    uvRaw = 0;

  //ATMOSPHERIC CALIBRATION
  float uvIndex = m * uvRaw + c;   //y = mx + c
  if (uvIndex < 0)
    uvIndex = 0;
  
  //PRINT RESULTS
  Serial.print("ADC: ");
  Serial.print(uv);

  Serial.print(" | Voltage: ");
  Serial.print(outputVoltage, 3);

  Serial.print(" V | Raw UV: ");
  Serial.print(uvRaw, 3);

  Serial.print(" | UV Index: ");
  Serial.println(uvIndex, 2);

  delay(1000);
}