int ledPin5 = 5;  // Pin 5 controls one LED
int ledPin6 = 6;  // Pin 6 controls another LED

void setup() {
  pinMode(ledPin5, OUTPUT);
  pinMode(ledPin6, OUTPUT);
  Serial.begin(9600);  // Set the baud rate to match the Python script
  Serial.println("Arduino is ready.");
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();

    if (command == 'o' || command == 'O') { // Accept both 'open' and 'closed'
      digitalWrite(ledPin5, HIGH);  // Turn on LED on pin 5
      delay(300);
      digitalWrite(ledPin6, HIGH);  // Turn on LED on pin 6
      delay(300);
      Serial.println("LEDs turned ON.");
    } else if (command == 'c' || command == 'C') {
      digitalWrite(ledPin5, LOW);  // Turn off LED on pin 5
      delay(300);
      digitalWrite(ledPin6, LOW);  // Turn off LED on pin 6
      delay(300);
      Serial.println("LEDs turned OFF.");
    }
  }
}