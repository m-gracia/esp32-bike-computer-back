#include "bluetooth.h"
#include "my_def.h"
#include "my_debug.h"

class MyClientCallback : public BLEClientCallbacks {
  void onConnect(BLEClient* pclient) {
    DEBUG_BT_PRINTLN("BT Device connected");
  }

  void onDisconnect(BLEClient* pclient) {
    bikeBT = STATUS_CRIT;
    DEBUG_BT_PRINTLN("BT Device disconnected");
  }
};

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      DEBUG_BT_PRINT("BT Advertised Device: ");
      DEBUG_BT_PRINTLN(advertisedDevice.toString().c_str());
      
      // We have found a device, let us now see if it contains the service we are looking for.
      if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(MOTORBIKE_SERVICE_UUID)) {
        DEBUG_BT_PRINTLN("BT Device found");
        BLEDevice::getScan()->stop();
        myDevice = new BLEAdvertisedDevice(advertisedDevice);
        bikeBT = STATUS_WARN;
      }
    }
};

bool enviaBT(){
  if (bitRead(bikeDataChanged,15)){
    DEBUG_BT_PRINTLN("DIST CHG");
    pCharDistance->writeValue(bikeDistance, 1);
  }

  return true;
}

void conectaBT(){
  DEBUG_BT_PRINTLN("BT try to create client");
  pClient  = BLEDevice::createClient();
  DEBUG_BT_PRINTLN("BT client created");
  pClient->setClientCallbacks(new MyClientCallback());
  DEBUG_BT_PRINTLN("BT client callback created");
  pClient->connect(myDevice);
  DEBUG_BT_PRINTLN("BT client conn");

  pRemoteService = pClient->getService(MOTORBIKE_SERVICE_UUID);
  if (pRemoteService == nullptr) {
    DEBUG_BT_PRINTLN("BT server incorrect");
    pClient->disconnect();
    bikeBT = STATUS_CRIT;
  } else{
    DEBUG_BT_PRINTLN("BT service found");
    if((pCharDistance = pRemoteService->getCharacteristic(DISTANCE_CHARACTERISTIC_UUID)) != nullptr){
      DEBUG_BT_PRINTLN("BT chars connected");
      bikeBT = STATUS_OK;
    } else {
      bikeBT = STATUS_CRIT;
    }
  }
}

void initBT(){
  bikeBT = STATUS_CRIT;   // Initialized but without data
  delay(3000);
  BLEDevice::init(BT_DEVICE_NAME);
  BLEDevice::setMTU(256); //<<<< MTU SIZE

  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setInterval(1349);
  pBLEScan->setWindow(449);
  pBLEScan->setActiveScan(true);
  pBLEScan->start(BTSCANTIME, false);
  DEBUG_BT_PRINTLN("BT Scan initiated"); 
}