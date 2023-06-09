/*
    Program Alarm PIR dengan Telegram
    dibuat oleh Indobot
*/
#include "CTBot.h"  //Pendeklarasian Library
CTBot myBot;
 
String ssid = "linda-meong-meong";    //nama ssid wifi kalian
String pass = "lindanesuwifinelemot";  //password wifi kalian
String token = "6120908849:AAHskIZp-ib4t3KnCJmMY5GqpY4dIwTOfRQ";    //token bot baru kalian
const int id = 1459467939;      //id telegram kalian
 
// #define ledPin D7  // Pemilihan Pin dan pendeklarasian variabel
#define pirPin 0 // PIR PIN D3
int pirValue;
 
void setup(){  //Pengaturan Pin dan Variabel
  Serial.begin(9600);
  Serial.println("Starting TelegramBot...");
  myBot.wifiConnect(ssid, pass);
  myBot.setTelegramToken(token);
  if (myBot.testConnection()) {
    Serial.println("Koneksi Bagus");
  } else {
    Serial.println("Koneksi Jelek");
  }
  // pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
  // digitalWrite(ledPin, LOW);
}
 
void loop(){ //Perulangan Program
  pirValue = digitalRead(pirPin);
  // digitalWrite(ledPin, pirValue);
  if (pirValue == HIGH)  //Apabila Terdeteksi Gerakan
  {
    Serial.println("Gerakan terdeteksi");
    myBot.sendMessage(id, "Gerakan terdeteksi");
  }
  delay(100);
}
