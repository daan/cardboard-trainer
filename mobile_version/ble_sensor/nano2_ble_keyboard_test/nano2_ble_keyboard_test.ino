#include <SPI.h>
#include <BLEHIDPeripheral.h>
#include <BLEKeyboard.h>

BLEHIDPeripheral bleHIDPeripheral = BLEHIDPeripheral();
BLEKeyboard bleKeyboard;

int testLEDPin = 13;

long gHeartBeatTimer = 0;
bool gHeartBeatStatus = false;


void setup() {
  Serial.begin(115200);
  Serial.println("BLE keyboard");
  pinMode(testLEDPin, OUTPUT);

  bleHIDPeripheral.clearBondStoreData();

  bleHIDPeripheral.setLocalName("VR Trainer Keyboard");
  bleHIDPeripheral.addHID(bleKeyboard);

  bleHIDPeripheral.begin();

}

void loop() {
  BLECentral central = bleHIDPeripheral.central();
  if (central) {
    // central connected to peripheral
    Serial.print(F("Connected to central: "));
    Serial.println(central.address());

    while (central.connected()) {
      if (Serial.available() > 0) {
        // read in character
        char c = Serial.read();

        Serial.print(F("c = "));
        Serial.println(c);

        bleKeyboard.print(c);
      }
    }

    // central disconnected
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }

  long m = millis();
  if(m > gHeartBeatTimer) {
    gHeartBeatTimer = m + 500;
    gHeartBeatStatus = ! gHeartBeatStatus;
    digitalWrite(testLEDPin, gHeartBeatStatus);
  }
}
