/*
    Program Alarm PIR dengan Telegram
    dibuat oleh Indobot
*/

#include <SPI.h>
#include <MFRC522.h>
#include "CTBot.h"  //Pendeklarasian Library

#define RST_PIN 5 // RFID PIN D1
#define SDA_PIN 4 // RFID PIN D2
#define pirPin 0 // PIR PIN D3
#define RELAY_PIN 2  //RELAY PIN D4

CTBot myBot;

 
String ssid = "linda-meong-meong";    //nama ssid wifi kalian
String pass = "lindanesuwifinelemot";  //password wifi kalian
String token = "6120908849:AAHskIZp-ib4t3KnCJmMY5GqpY4dIwTOfRQ";    //token bot baru kalian
const int id = 1459467939;      //id telegram kalian
int pirValue;
 
MFRC522 mfrc522(SDA_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  Serial.println("Starting TelegramBot...");
  // myBot.wifiConnect(ssid, pass);
  // myBot.setTelegramToken(token);
  // if (myBot.testConnection()) {
  //   Serial.println("Koneksi Bagus");
  //   Serial.println("Put your card to the reader...");
  // } else {
  //   Serial.println("Koneksi Jelek");
  //   Serial.println("Put your card to the reader...");
  // }

  pinMode(pirPin, INPUT); // PIR INPUT
  pinMode(RELAY_PIN, OUTPUT);  // Set pin sebagai OUTPUT
  
}


void loop() {
  if(!mfrc522.PICC_IsNewCardPresent()){
    //  Serial.println("PICC Is New Card Present");
    return;
  }

  if(!mfrc522.PICC_ReadCardSerial()){
    Serial.println("PICC Read Card Serial");
    return;
  }

  Serial.print("UID tag :");
  String content = "";
  byte letter;

  for(byte i = 0; i < mfrc522.uid.size; i++){
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  Serial.println();
  Serial.print("Pesan : ");
  content.toUpperCase();

  if(content.substring(1) == "9A BE 1B B0"){
    Serial.println("Kartu cocok");
    Serial.println();
    delay(1000);
  }

  // else if(content.substring(1) == "D3 BC D1 A9"){
  //   Serial.println("Kartu cocok");
  //   Serial.println();
  //   delay(1000);
  // }
  else{
    Serial.println("Kartu Tidak cocok");
    delay(1000);
  }

}


