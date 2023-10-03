#include <Servo.h>

Servo myServo;
int releasePosition = 0;
int pressPosition = 20;
const int ButtonPin = 2;
boolean buttonState = false;

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  myServo.attach(9);
  myServo.write(releasePosition);
  delay(500);
  pinMode(ButtonPin, INPUT_PULLUP);
}

void loop() {
  boolean newButtonState = digitalRead(ButtonPin);
  
  if (newButtonState != buttonState) {
    if (!newButtonState) {  // Button is pressed (because INPUT_PULLUP inverts logic)
      myServo.write(pressPosition);
      delay(100); // Adjust this delay as needed for your application
      myServo.write(releasePosition);
      Serial.println("a");  // Send 'a' to the computer over serial
    }
    buttonState = newButtonState;
  }
}


