#include <Arduino.h>

int avgAnalogRead(int pin, int readings){
  unsigned int value = 0;

  for(int i = 0; i < readings; i++)
    value += analogRead(pin);

  return value / readings;
}
