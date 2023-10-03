#include<LedControl.h>
#include<Wire.h>
#include<MPU6050_tockn.h>
#include<Servo.h>
#define DATA 11
#define CLOCK 12
#define CS 10
LedControl lc = LedControl(DATA,CLOCK,CS,1);
MPU6050 mpu6050(Wire);
Servo myservo;

const byte leftarrow[8] ={
  B00010000,
  B00110000,
  B01110000,
  B11111111,
  B11111111,
  B01110000,
  B00110000,
  B00010000
};
const byte rightarrow[8] ={
  B00001000,
  B00001100,
  B00001110,
  B11111111,
  B11111111,
  B00001110,
  B00001100,
  B00001000
};
void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
  myservo.attach(3);

}

void loop() {
  mpu6050.update();
  float angleY = mpu6050.getAngleY();
  if (angleY > 10) {
    drawarrow(leftarrow);
  }
  else if (angleY < -10) {
    drawarrow(rightarrow);
  }
mpu6050.update();
int angleX = mpu6050.getAngleX();
angleX= map(angleX , 85 , -85 , 0 ,180);
myservo.write(angleX);
delay(10);

}


void drawarrow(byte array[8]){
  for(int i=0 ; i<8 ; i++){
    lc.setColumn(0,i,array[i]);
  }
}
