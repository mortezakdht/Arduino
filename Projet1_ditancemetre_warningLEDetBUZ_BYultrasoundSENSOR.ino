#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // LiquidCrystal lcd(rs, enable, D4, D5, D6, D7);
int PingPin = 10;
int EchoPin = 9;
int Buz = 8;
int LED= 7;
#define STEPPER_PIN_1 13
#define STEPPER_PIN_2 6


void setup(){
 analogReference(DEFAULT); // 5v Vref 
lcd.begin(16,2); // (Sotoon, Satr);

lcd.clear();
 pinMode(PingPin, OUTPUT);
 pinMode(EchoPin, INPUT);
 pinMode(Buz, OUTPUT);
 pinMode(LED, OUTPUT);
 pinMode(STEPPER_PIN_1, OUTPUT);
 pinMode(STEPPER_PIN_2, OUTPUT);
 
 Serial.begin(9600);
  
}

void loop(){
 unsigned long duration, cm;
  
  digitalWrite(PingPin,LOW);
  delayMicroseconds(2);
  digitalWrite(PingPin,HIGH);
  delayMicroseconds(5);
  digitalWrite(PingPin, LOW);
  
  
  
  duration = pulseIn(EchoPin, HIGH); // Daryaft Zamane bazgasht Sot bar Habs Micro Saniye
  
  cm = MicroStoCm(duration);
  if (cm<=20){
    digitalWrite(Buz,HIGH);
    delayMicroseconds(500);
   digitalWrite(Buz,LOW);
    digitalWrite(LED,HIGH);
      delayMicroseconds(1000);
   digitalWrite(LED,LOW);
    digitalWrite(STEPPER_PIN_1,HIGH);
    digitalWrite(STEPPER_PIN_2,LOW);
      delayMicroseconds(1000);

  }
  
   else if (cm<=40 & cm>=30){
    digitalWrite(STEPPER_PIN_2,HIGH);
    digitalWrite(STEPPER_PIN_1,LOW);
         delayMicroseconds(1000);
  }
  
  Serial.print(cm);
  Serial.println("cm");
  delay(200);
  
  lcd.setCursor(0,0);
  lcd.print("MORTEZA");
  lcd.setCursor(0,1);
  lcd.print("dist= ");
  lcd.setCursor(7, 1);
  lcd.print(cm);
  delay(200);
  lcd.clear();
  
}
unsigned long MicroStoCm( unsigned long MicroS){
 // Soarte Soat 340 m/s
// 29 microseconds / cm

return (MicroS/29)/2;
  
}
