//Servidor
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLEServer* pServer = NULL;                        // Pointer to the server
BLECharacteristic* pCharacteristic = NULL;
BLEDescriptor *pDescr;
BLE2902* pBLE2902;

bool deviceConnected = false;
bool oldDeviceConnected = false;

String num="0";
bool flagPruWrite = false;
bool flagAlt = true;

#define SERVICE_UUID          "b6784b11-65ff-46a8-bc8b-0273aaf6ec1a"
#define CHARACTERISTIC_UUID   "e38932cd-1ff1-42cf-b0cd-b0764da03093"

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };
    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};
//class MyCallbacks: public BLECharacteristicCallbacks {
//    void onWrite(BLECharacteristic *pCharacteristic) {
//      std::string rxValue = pCharacteristic->getValue();
//      Serial.print("Valor recibido: ");
//      Serial.println(rxValue.c_str());
//      num = rxValue.c_str();
//      if (num == "1") {
//        flagPruWrite = true;
//      }
//    }
//};

void setup() {
  Serial.begin(115200);

  BLEDevice::init("ESP32Serv");

  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY 
                    );
  pDescr = new BLEDescriptor((uint16_t)0x2901);
  pDescr->setValue("ContadorPasos");
  pCharacteristic->addDescriptor(pDescr);

  pBLE2902 = new BLE2902();
  pBLE2902->setNotifications(true);
  pCharacteristic->addDescriptor(pBLE2902);

  pService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);
  BLEDevice::startAdvertising();
  Serial.println("Waiting a client connection to notify...");
  pinMode(2,OUTPUT);
}
void loop() {
  if (deviceConnected) {
    if(flagPruWrite == true){
      digitalWrite(2,flagAlt);
      flagAlt=!flagAlt;
      flagPruWrite == false;
    }
  }
  if (!deviceConnected && oldDeviceConnected) {
    delay(500); // give the bluetooth stack the chance to get things ready
    pServer->startAdvertising(); // restart advertising
    Serial.println("start advertising");
    oldDeviceConnected = deviceConnected;
  }
  if (deviceConnected && !oldDeviceConnected) {
    // do stuff here on connecting
    oldDeviceConnected = deviceConnected;
  }
}
