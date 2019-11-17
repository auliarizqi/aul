#include <SoftwareSerial.h>
int vibrationSensorPin = 2;
int indikatorHijau = 3;
int indikatorMerah = 4; 
int indikatorBuzzer = 5;
SoftwareSerial mySerial(10, 11);

long TP_init(){
  delay(10);
  unsigned long measurement = pulseIn (vibrationSensorPin, HIGH); 
  return measurement;
}

void nyala_mati(){
  digitalWrite(indikatorBuzzer, HIGH);
  delay(1000);
  digitalWrite(indikatorBuzzer, LOW);
  delay(1000);
  }

void setup() {
  mySerial.begin(9600);
  pinMode(vibrationSensorPin, INPUT); 
  pinMode(indikatorHijau, OUTPUT); 
  pinMode(indikatorMerah, OUTPUT); 
  pinMode(indikatorBuzzer, OUTPUT); 
}

void loop() {
  unsigned long measurement = TP_init();
  delay(50);
  Serial.println(measurement);
  if(mySerial.available()>0){
    if (measurement > 1000) { 
    digitalWrite(indikatorHijau, HIGH);
    digitalWrite(indikatorMerah, LOW); 
    digitalWrite(indikatorBuzzer, HIGH);
    mySerial.write(measurement);
    delay(8000); 
    digitalWrite(indikatorHijau, LOW); 
    digitalWrite(indikatorMerah, HIGH); 
    delay(1000); 
  } 
  else {
    digitalWrite(indikatorHijau, LOW); 
    digitalWrite(indikatorMerah, HIGH);
    digitalWrite(indikatorBuzzer, LOW);
    mySerial.write(measurement);
    delay(1000);
  }
  }
  
}
