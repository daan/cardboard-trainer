
int testLEDPin = 13;

void setup() {
  Serial.begin(115200);
  Serial.println("BLE test");
  pinMode(testLEDPin, OUTPUT);

}

void loop() {
  // put your main code here,
  delay(100);
  digitalWrite(testLEDPin, HIGH);
  delay(100);
  digitalWrite(testLEDPin, LOW);

  Serial.println("xx");
}
