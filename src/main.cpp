#include <Arduino.h>
#include "my_def.h"
#include "my_debug.h"
#include "distance.h"
#include "bluetooth.h"

void setup() {
  #ifdef DEBUG
    Serial.begin(115200);
  #endif
  DEBUG_PRINTLN("Manuel Gracia.Apr-2024");
  DEBUG_PRINTLN("https://github.com/m-gracia");
  DEBUG_PRINTLN("esp32-bike-computer-back_20240429");
  
  initDistance();
  initBT();

  DEBUG_PRINTLN("Setup end");
}

void loop() {
  if (timerDistance < millis()){
    getDistance();
    timerDistance = millis() + 200; // 200ms
  }
  
  if (bikeBT == STATUS_OK){
    if (bikeDataChanged != 0){
      if (sendBT()){ bikeDataChanged=0; DEBUG_BT_PRINTLN("BT SENT");}
    }
  } else if (bikeBT == STATUS_WARN){
    DEBUG_BT_PRINTLN("BT WARNING. Connecting");
    connectBT();
  } else if (timerBT < millis()){
    timerBT = millis() + 5000; // 5sec
    DEBUG_BT_PRINTLN("BT CRIT. Initalyzinng");
    initBT();
  }
}