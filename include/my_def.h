#ifndef _MY_DEF_H_
#define _MY_DEF_H_
#include <Arduino.h>

// Bluetooth
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <BLERemoteCharacteristic.h>
#include <BLEAddress.h>
#define BTSCANTIME 5
#define BT_GENERIC_DISPLAY 320
#define BT_VEHICLE_MOTORBIKE 2244
#define BT_DEVICE_NAME "Jarvis-back"     // BLE device name
static const BLEUUID MOTORBIKE_SERVICE_UUID = BLEUUID("cb99fdf2-bebe-cafe-b1bf-bf9803b2df01");
static const BLEUUID DISTANCE_CHARACTERISTIC_UUID = BLEUUID("cb99fdf2-bebe-cafe-b1bf-bf9803b2df01");    //Distance
extern BLEAdvertisedDevice* myDevice;
extern BLEClient*  pClient;
extern BLERemoteService* pRemoteService;
extern BLERemoteCharacteristic* pCharDistance;
extern BLEScan* pBLEScan;

// Ultrasonic HC-SR04
#define DIST_PIN_TRIGG 17   // USonic Trigger pin
#define DIST_PIN_ECHO 16    // USonic Echo pin
// Distance marks for showing bars
static unsigned char distanceMark = 100;    // Detected mark
static unsigned char distanceMark1 = 30;    // Closest mark
static unsigned char distanceMark2 = 50;    // Close mark
static unsigned char distanceMark3 = 70;    // Far mark
static unsigned char distanceMark4 = 100;   // Farthest mark

//Status IDs
#define STATUS_UNK 8        // Unknown
#define STATUS_CRIT 2       // Critical
#define STATUS_WARN 1       // Warning
#define STATUS_OK 0         // OK

//Status variables
extern unsigned char bikeBT;        // Bluetooth Status
extern unsigned char bikeDistance;  // Distance Status

/* To show changes on LCD's
 *
 * The bits are set when a new information needs to be updated on the LCD's
 * 1 - GPS Speed (Not used here)
 * 2 - GPRS Status (Not used here)
 * 3 - TPMS Front (Not used here)
 * 4 - TPMS Rear (Not used here)
 * 5 - GPS Heigh (Not used here)
 * 6 - Hour,minute (Not used here)
 * 7 - Date (Not used here)
 * 8 - CPU status (Not used here)
 * 9 - GPS Status (Not used here)
 * 10 - Phone battery (Not used here)
 * 11 - Street name (Not used here)
 * 12 - Speed limit (Not used here)
 * 13 - GPS Satellites (Not used here)
 * 14 - City and weather (Not used here)
 * 15 - USonic distance
 */
extern unsigned long bikeDataChanged;

// Run timers
extern unsigned long timerBT;

// Task
extern TaskHandle_t T_loopOthers;

#endif  // _MY_DEF_H_