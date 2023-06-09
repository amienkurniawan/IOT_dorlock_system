#define RELAY_PIN 16  // D0

void setup() {
  pinMode(RELAY_PIN, OUTPUT);  // Set pin sebagai OUTPUT
}

void loop() {
  digitalWrite(RELAY_PIN, HIGH);   // Aktifkan relay
  delay(1000);                     // Tahan relay selama 5 detik
  digitalWrite(RELAY_PIN, LOW);    // Matikan relay
  delay(5000);                     // Tahan relay selama 5 detik
}