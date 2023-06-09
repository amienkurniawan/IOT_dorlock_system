#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 4
#define RST_PIN 5

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Ready to read RFID tags...");
}

void loop() {
  
  if(mfrc522.PICC_IsNewCardPresent()){
  Serial.print("new Card UID: ");
  Serial.println();
  }else{
  Serial.print("jalan false new card");
  Serial.println();
  }

  if (mfrc522.PICC_ReadCardSerial()) {
    Serial.print("Card UID: ");
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println();
    mfrc522.PICC_HaltA();
  }else{
    Serial.print("jalan false Read serial");
    Serial.println();
  }
}
