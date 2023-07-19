#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <esp32-hal-cpu.h>
#include <BLE2902.h>
//#include <HardwareSerial.h>

// Define los UUIDs para el servicio y la característica BLE
#define SERVICE_UUID        "00110011-4455-6677-8899-AABBCCDDEEFF"
#define CHARACTERISTIC_UUID "00112233-4455-6677-8899-AABBCCDDEEFF"

// Crea un servidor BLE y una característica para enviar caracteres
BLEServer *pServer = NULL;
BLECharacteristic *pCharacteristic = NULL;
BLEAdvertising *pAdvertising;
void setup() {
  // Inicializa el módulo Bluetooth y crea un servidor BLE
  //  rtc_clk_cpu_freq_set(RTC_CPU_FREQ_80M);
  // setCpuFrequencyMhz(80);
  Serial.begin(9600);
  BLEDevice::init("ESP32");

  pServer = BLEDevice::createServer();

  // Crea un servicio BLE y añade una característica para enviar caracteres
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_WRITE);

  // Configura el servidor BLE para que empiece a escuchar conexiones
  pService->start();
  pAdvertising = pServer->getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x03);  //03 tiempo mínimo en milisegundos antes de que el cliente prefiera este dispositivo
  pAdvertising->setMinPreferred(0x06);  //06 tiempo máximo en milisegundos antes de que el cliente prefiera este dispositivo
  pAdvertising->start();

  // Configura las funciones de callback para manejar las conexiones y las características
  class MyServerCallbacks: public BLEServerCallbacks {
      void onConnect(BLEServer* pServer) {
        // se llama cuando un dispositivo se conecta al servidor BLE
        pAdvertising->stop();
      };

      void onDisconnect(BLEServer* pServer) {
        // se llama cuando un dispositivo se desconecta del servidor BLE
        pAdvertising->start();

      }
  };

  class MyCallbacks: public BLECharacteristicCallbacks {
      void onWrite(BLECharacteristic *pCharacteristic) {
        std::string value = pCharacteristic->getValue();
        Serial.print("Valor recibido: ");
        Serial.println(value.c_str());
        String num = value.c_str();
        if (num == "3") {
          digitalWrite(2, HIGH);
        }

      }
  };

  pServer->setCallbacks(new MyServerCallbacks());
  pCharacteristic->setCallbacks(new MyCallbacks());

  // Inicializa el puerto serial

  pinMode(2, OUTPUT);
}

void loop() {
  //  Lee el puerto serial y envía los caracteres por BLE
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    pCharacteristic->setValue(input.c_str());
    pCharacteristic->notify();
  }
}
