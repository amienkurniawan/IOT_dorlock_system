#include <Servo.h>

Servo servoMotor;

void setup() {
  Serial.begin(9600);
  servoMotor.attach(2); 
   servoMotor.write(0); // Set posisi awal servo ke sudut 90 derajat
}

void loop() {
  Serial.println("servo 0:");
  servoMotor.write(0); // Set posisi awal servo ke sudut 90 derajat
  delay(2000); // Tunggu selama 1 detik sebelum mengulangi gerakan
  // Kembalikan servo ke posisi awal (90 derajat)
  Serial.println("servo 180:");
  servoMotor.write(180); // Set posisi awal servo ke sudut 90 derajat
  delay(2000); 
}