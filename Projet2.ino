#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>
#define RST_PIN         5          // Configurable, see typical pin layout above
#define SS_PIN          10  
#define BUZZER_PIN 9
LiquidCrystal lcd(7, 6, 8, 4, 3, 2); // LiquidCrystal lcd(rs, enable, D4, D5, D6, D7);
MFRC522 mfrc522(SS_PIN, RST_PIN);
bool cardPresent = false;
void setup(){
 analogReference(DEFAULT); // 5v Vref 
 lcd.begin(16,2); // (Sotoon, Satr);
  lcd.setCursor(0,0);
  lcd.print("CART PLEASE");
pinMode(BUZZER_PIN, OUTPUT);
 Serial.begin(9600);
 	while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();		// Init MFRC522
	delay(4);				// Optional delay. Some board do need more time after init to be ready, see Readme
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
  
}

void loop(){
  	// Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
 if (!mfrc522.PICC_IsNewCardPresent()) {
    // Card is not present
    if (cardPresent) {
      // If the card was present and has been removed, turn off the buzzer
      digitalWrite(BUZZER_PIN, LOW);
       
      cardPresent = false;
    }
    return;
  }

  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Card is present
  if (!cardPresent) {
    // If the card was not present and is now detected, turn on the buzzer
    digitalWrite(BUZZER_PIN, HIGH);
     
    cardPresent = true;
  }


  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("YOU CAN PASS");

  delay(2000);
  lcd.setCursor(0, 1);
  lcd.print("                ");
	// Dump debug info about the card; PICC_HaltA() is automatically called
	mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}
