#include <Arduino.h>
#include "my_def.h"

BLEAdvertisedDevice* myDevice = NULL;
BLEClient*  pClient = NULL;
BLERemoteService* pRemoteService = NULL;
BLERemoteCharacteristic* pCharDistance = NULL;
BLEScan* pBLEScan = NULL;

unsigned char bikeBT = STATUS_UNK;
unsigned char bikeDistance = STATUS_OK;

unsigned long bikeDataChanged = 0xFFFFFFFF;

unsigned long timerBT = millis() + 10000;
unsigned long timerDistance = millis();

TaskHandle_t T_loopOthers = NULL;