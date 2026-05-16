#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

// Define our LED Pins
const int GREEN_LED = 25;
const int RED_LED = 26;

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      String value = pCharacteristic->getValue();
      if (value.length() > 0) {
        char command = value[0];
        
        if (command == 'G') {
          Serial.println("====== GREEN SCREEN (Organic > 90%) ======");
          // Turn Green ON, Red OFF
          digitalWrite(GREEN_LED, HIGH);
          digitalWrite(RED_LED, LOW);
          
        } else if (command == 'R') {
          Serial.println("====== RED FLASH (Other/Low Confidence) ======");
          // Turn Red ON, Green OFF
          digitalWrite(RED_LED, HIGH);
          digitalWrite(GREEN_LED, LOW);
        }
      }
    }
};

void setup() {
  Serial.begin(115200);
  
  // Initialize the pins as OUTPUTs
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  
  // Make sure both are off when the board turns on
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);

  BLEDevice::init("Waste_ESP32");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_WRITE
                                       );
  pCharacteristic->setCallbacks(new MyCallbacks());
  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  BLEDevice::startAdvertising();
  
  Serial.println("Waiting for Android App to connect...");
}

void loop() { 
  // Nothing needed here, Bluetooth runs in the background!
  delay(2000); 
}
