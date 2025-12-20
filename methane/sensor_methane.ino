int mqDigital = A0;   

int iut = 500 ; 

void setup() {
  pinMode(mqDigital, INPUT);
  Serial.begin(9600);
}

void loop() {
  int state = analogRead(mqDigital);
  float voltage = (5.0/1023.0) * state ; 
     
    if(state >= iut){
    Serial.print("Fire: HIGH-> ");
    Serial.println(state);
    Serial.print("The voltage : ") ;
    Serial.println(voltage) ;
    }

    else 
    {
      Serial.print("Nothing special :LOW-> ") ;
      Serial.println(state) ;
      Serial.print("The voltage : ") ;
      Serial.println(voltage) ;
    }
  delay(1000);
}