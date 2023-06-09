byte led1 = 16; //pin D0
byte led2 = 5; // pin D1
byte led3  = 4; // pin D2
byte speakerPin = 13;
int number_of_crickets;
int chirp = 50;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(speakerPin,OUTPUT);
  number_of_crickets = 1000 * (5 / 1023.0);
}

void loop() {
  digitalWrite(led1, HIGH);
  delay(3000);
  digitalWrite(led1, LOW);
  delay(1000);

  // analogWrite(speakerPin,number_of_crickets);
  // delay(5000);
  // analogWrite(speakerPin,0);
  // delay(1000);

  digitalWrite(led2, HIGH);
  delay(3000);
  digitalWrite(led2, LOW);
  delay(1000);

  // analogWrite(speakerPin,number_of_crickets);
  // delay(5000);
  // analogWrite(speakerPin,0);
  // delay(1000);

  digitalWrite(led3, HIGH);
  delay(3000);
  digitalWrite(led3, LOW);
  delay(1000);

  // analogWrite(speakerPin,number_of_crickets);
  // delay(5000);
  // analogWrite(speakerPin,0);
  // delay(1000);
}
