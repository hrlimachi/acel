#include "BLEDevice.h"

static BLEUUID serviceUUID("b6784b11-65ff-46a8-bc8b-0273aaf6ec1a");
static BLEUUID    charUUID("e38932cd-1ff1-42cf-b0cd-b0764da03093");

static boolean doConnect = false;
static boolean connected = false;
static boolean doScan = false;

static BLEAdvertisedDevice* myDevice;
BLERemoteCharacteristic* pRemoteChar;

static void notifyCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic,
                            uint8_t* pData,
                            size_t length,
                            bool isNotify) {
  if(pBLERemoteCharacteristic->getUUID().toString() == charUUID.toString()) {
    Serial.print("Data: ");
    for(int i=0; i<length;i++)
      Serial.print((char)pData[i]);
    Serial.println(".");

 
  }
}
class MyClientCallback : public BLEClientCallbacks {
  void onConnect(BLEClient* pclient) {
  }

  void onDisconnect(BLEClient* pclient) {
    connected = false;
    Serial.println("onDisconnect");
  }
};

bool connectToServer() {
  Serial.print("Forming a connection to ");
  Serial.println(myDevice->getAddress().toString().c_str());
  
  BLEClient*  pClient  = BLEDevice::createClient();
  Serial.println(" - Created client");

  pClient->setClientCallbacks(new MyClientCallback());

  // Connect to the remove BLE Server.
  pClient->connect(myDevice);  // if you pass BLEAdvertisedDevice instead of address, it will be recognized type of peer device address (public or private)
  Serial.println(" - Connected to server");

  // Obtain a reference to the service we are after in the remote BLE server.
  BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
  if (pRemoteService == nullptr) {
    Serial.print("Failed to find our service UUID: ");
    Serial.println(serviceUUID.toString().c_str());
    pClient->disconnect();
    return false;
  }
  Serial.println(" - Found our service");

  connected = true;
  pRemoteChar = pRemoteService->getCharacteristic(charUUID);
  if(connectCharacteristic(pRemoteService, pRemoteChar) == false)
    connected = false;

  if(connected == false) {
    pClient-> disconnect();
    Serial.println("At least one characteristic UUID not found");
    return false;
  }
  return true;
}

bool connectCharacteristic(BLERemoteService* pRemoteService, BLERemoteCharacteristic* l_BLERemoteChar) {
  // Obtain a reference to the characteristic in the service of the remote BLE server.
  if (l_BLERemoteChar == nullptr) {
    Serial.print("Failed to find one of the characteristics");
    Serial.print(l_BLERemoteChar->getUUID().toString().c_str());
    return false;
  }
  Serial.println(" - Found characteristic: " + String(l_BLERemoteChar->getUUID().toString().c_str()));

  if(l_BLERemoteChar->canNotify())
    l_BLERemoteChar->registerForNotify(notifyCallback);

  return true;
}

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  //Called for each advertising BLE server.
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.print("BLE Advertised Device found: ");
    Serial.println(advertisedDevice.toString().c_str());
    digitalWrite(2,advertisedDevice.isAdvertisingService(serviceUUID));
    // We have found a device, let us now see if it contains the service we are looking for.
    if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(serviceUUID)) {
      
      BLEDevice::getScan()->stop();
      myDevice = new BLEAdvertisedDevice(advertisedDevice);
      doConnect = true;
      doScan = true;
      
    } // Found our server
  } // onResult
}; // MyAdvertisedDeviceCallbacks

void setup() {
  Serial.begin(115200);
  Serial.println("Starting Arduino BLE Client application...");
  BLEDevice::init("");

  // Retrieve a Scanner and set the callback we want to use to be informed when we
  // have detected a new device.  Specify that we want active scanning and start the
  // scan to run for 5 seconds.
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setInterval(1349);
  pBLEScan->setWindow(449);
  pBLEScan->setActiveScan(true);
  pBLEScan->start(5, false);
  pinMode(2,OUTPUT);
}

void loop() {
  
  // If the flag "doConnect" is true then we have scanned for and found the desired
  // BLE Server with which we wish to connect.  Now we connect to it.  Once we are 
  // connected we set the connected flag to be true.
  if (doConnect == true) {
    if (connectToServer()) {
      Serial.println("We are now connected to the BLE Server.");
      
    } else {
      Serial.println("We have failed to connect to the server; there is nothin more we will do.");
    }
    doConnect = false;
  }

  // If we are connected to a peer BLE Server, update the characteristic each time we are reached
  // with the current time since boot.
  if (connected) {
    String txValue = "1";
    Serial.println("Characteristic 2 (writeValue): " + txValue);
    
    // Set the characteristic's value to be the array of bytes that is actually a string.
    pRemoteChar->writeValue(txValue.c_str(), txValue.length());
    
  }else if(doScan){
    BLEDevice::getScan()->start(0);  // this is just example to start scan after disconnect, most likely there is better way to do it in arduino
  }

  // In this example "delay" is used to delay with one second. This is of course a very basic 
  // implementation to keep things simple. I recommend to use millis() for any production code
  delay(1000);
}
