#include <Arduino.h>
#include "my_def.h"
#include "my_debug.h"
#include "distance.h"
#include "bluetooth.h"


// TASKS ON CORE 0 //
void loopOthers (void * parameter){
for(;;) {
  consultaDistancia();
  delay(250); //Para alimentar el WDog.
}
}
// -------------- //


void setup() {
  #ifdef DEBUG
    Serial.begin(115200);
  #endif
  DEBUG_PRINTLN("Manuel Gracia.Nov-2022");
  DEBUG_PRINTLN("https://github.com/m-gracia");
  DEBUG_PRINTLN("esp32-bike-computer_20221104");
  
  // Ultrasonic 
  pinMode(DIST_PIN_TRIGG,OUTPUT);
  pinMode(DIST_PIN_ECHO,INPUT_PULLUP);

  initBT();

  xTaskCreatePinnedToCore(
      loopOthers, // Function to implement the task
      "loopOthers", // Name of the task
      20000,  // Stack size in words
      NULL,  // Task input parameter
      1,  // Priority of the task
      &T_loopOthers,  // Task handle.
      0); // Core where the task should run

  DEBUG_PRINTLN("Setup end");
}

void loop() {
  if (bikeBT == STATUS_OK){
    if (bikeDataChanged != 0){
      if (enviaBT()){ bikeDataChanged=0; DEBUG_BT_PRINTLN("BT SENT");}
    }
  } else if (bikeBT == STATUS_WARN){
    DEBUG_BT_PRINTLN("BT WARNING. Connecting");
    conectaBT();
  } else if (timerBT < millis()){
    timerBT = millis() + 5000; // 5sec
    DEBUG_BT_PRINTLN("BT CRIT. Initalyzinng");
    initBT();
  }
}