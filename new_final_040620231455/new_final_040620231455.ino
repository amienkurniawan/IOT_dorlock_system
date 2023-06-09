// Kode untuk NodeMCU ESP8266 dengan sensor RFID dan PIR menggunakan logika fuzzy
#include <SPI.h>
#include <MFRC522.h>
#include "CTBot.h"  //Pendeklarasian Library
#include <Servo.h>

Servo servoMotor;
// Pin RFID
#define RST_PIN 5 // RFID PIN D1
#define SDA_PIN 4 // RFID PIN D2

// Pin PIR
#define pirPin 0 // PIR PIN D3

// Output Relay
// #define RELAY_PIN 2 // RELAY PIN D4

// chat variabel
CTBot myBot;
String ssid = "linda-meong-meong";    //nama ssid wifi kalian
String pass = "lindanesuwifinelemot";  //password wifi kalian
String token = "6120908849:AAHskIZp-ib4t3KnCJmMY5GqpY4dIwTOfRQ";    //token bot baru kalian
const int id = 1459467939;      //id telegram kalian

// Fuzzy Logic Variables
float rfidValue;
float pirValue;
float fuzzyOutput;

MFRC522 mfrc522(SDA_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  
  // Servo Motor pin D4
  servoMotor.attach(2); 
  servoMotor.write(0); // Set posisi awal servo ke sudut 0 derajat

  // Inisialisasi RFID
  SPI.begin();
  mfrc522.PCD_Init();
  
  // Set pin PIR sebagai input
  pinMode(pirPin, INPUT);

  // Set pin Relay sebagai output
  // pinMode(RELAY_PIN, OUTPUT);
    
  myBot.wifiConnect(ssid, pass);
  myBot.setTelegramToken(token);
  if (myBot.testConnection()) {
    Serial.println("Koneksi Bagus");
    Serial.println("Put your card to the reader...");
  } else {
    Serial.println("Koneksi Jelek");
    Serial.println("Put your card to the reader...");
  }
  Serial.println("Starting Program...");
}

void loop() {
  //  digitalWrite(RELAY_PIN, LOW); 
   if(!mfrc522.PICC_IsNewCardPresent()){
    //  Serial.println("PICC Is New Card Present");
    return;
  }

  if(!mfrc522.PICC_ReadCardSerial()){
    Serial.println("PICC Read Card Serial");
    return;
  }

  // Baca sensor RFID
  rfidValue = calculateRFIDValue(); // Menghitung nilai RFID dengan fungsi khusus Anda
  Serial.println("RFID value...");
  Serial.println(rfidValue);
  Serial.println();

  // Baca sensor PIR
  pirValue = digitalRead(pirPin);
  Serial.println("PIR value...");
  Serial.println(pirValue);
  Serial.println();
  // Proses logika fuzzy
  fuzzyOutput = performFuzzyLogic(rfidValue, pirValue); // Melakukan operasi logika fuzzy dengan fungsi khusus Anda
  Serial.println("fuzzyOutput...");
  Serial.println(fuzzyOutput);
  Serial.println();

  // Aktifkan atau nonaktifkan relay berdasarkan hasil logika fuzzy
  if (fuzzyOutput == 1.0) {
    // digitalWrite(RELAY_PIN, HIGH); // Aktifkan relay
    Serial.println("servo 180:");
    myBot.sendMessage(id, "Pintu terbuka");
    servoMotor.write(180); // Set posisi awal servo ke sudut 90 derajat
    delay(5000); // Jeda antar-pembacaan
    Serial.println("servo 0:");
    servoMotor.write(0); // Set posisi awal servo ke sudut 90 derajat
  } else {
    // digitalWrite(RELAY_PIN, LOW); // Nonaktifkan relay
    myBot.sendMessage(id, "Maaf Kunci Salah");
    delay(2000); // Jeda antar-pembacaan
  }
  
}

float calculateRFIDValue() {
  // Implementasikan fungsi khusus Anda untuk menghitung nilai RFID berdasarkan tag yang terbaca
  // Misalnya, Anda dapat menggunakan perbandingan UID dengan nilai-nilai yang sudah diketahui
  // Mengembalikan nilai antara 0 hingga 1, dengan 1 menunjukkan kecocokan yang sempurna
  // UID tag yang sudah diketahui sebelumnya
    
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
    Serial.println("Isi RFID...");
    content.toUpperCase(); 
    Serial.println(content.substring(1));
    Serial.println();


    // Bandingkan UID tag dengan UID yang sudah diketahui
    if (content.substring(1) == "9A BE 1B B0" ) {
      return 1.0; // Kecocokan sempurna, nilai RFID adalah 1.0
    } else {
      return 0.0; // Tidak ada kecocokan, nilai RFID adalah 0.0
    }
}

float performFuzzyLogic(float rfidValue, float pirValue) {
  // Implementasikan fungsi khusus Anda untuk melakukan operasi logika fuzzy
  // Gunakan nilai rfidValue dan pirValue sebagai input untuk menghasilkan nilai output fuzzy
  // Gunakan metode fuzzy yang sesuai, seperti aturan-aturan IF-THEN atau model matematis
  // Mengembalikan nilai antara 0 hingga 1, yang merupakan hasil dari operasi logika fuzzy
  // Variabel input
  float rfidMembership = 0.0;
  float pirMembership = 0.0;
  
  // Variabel output
  float fuzzyOutput = 0.0;
  
  // Menentukan keanggotaan untuk variabel input RFID
  if (rfidValue == 1.0) {
    rfidMembership = 1.0;
  } else{
    rfidMembership = 0.0;
  }
  
  // Menentukan keanggotaan untuk variabel input PIR
  if (pirValue == 1.0 ) {
    pirMembership = 1.0;
  } else {
    pirMembership = 0.0;
  }
  
  // Menggunakan aturan IF-THEN sederhana untuk menghasilkan output fuzzy
  if (rfidMembership == 1.0 && pirMembership == 1.0) {
    fuzzyOutput = 1.0;
  } else {
    fuzzyOutput = 0.0;
  }
  
  return fuzzyOutput;
}