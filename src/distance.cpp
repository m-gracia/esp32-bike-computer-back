#include "distance.h"
#include "my_def.h"
#include "my_debug.h"

void getDistance(){
  int timeEcho;
  unsigned char tbikeDistance;
  unsigned char distanceEcho;   // Distance measured

  digitalWrite(DIST_PIN_TRIGG,LOW);
  delayMicroseconds(2);
  
  digitalWrite(DIST_PIN_TRIGG,HIGH);  // Throw trigger
  delayMicroseconds(20);  
  digitalWrite(DIST_PIN_TRIGG,LOW);
  timeEcho=pulseIn(DIST_PIN_ECHO,HIGH,14790); //14790us = 255cm

  if (timeEcho == 0) distanceEcho = 255;
  else distanceEcho=timeEcho/58;

  DEBUG_SENSOR_PRINT("Distance: ");
  DEBUG_SENSOR_PRINTLN(distanceEcho);

  if (distanceEcho < distanceMark1) tbikeDistance = 5;      // Closest
  else if (distanceEcho < distanceMark2) tbikeDistance = 4; 
  else if (distanceEcho < distanceMark3) tbikeDistance = 3;
  else if (distanceEcho < distanceMark4) tbikeDistance = 2;
  else if (distanceEcho < distanceMark) tbikeDistance = 1;  // Farthest
  else tbikeDistance = STATUS_OK; // No detection or too far
  
  DEBUG_SENSOR_PRINT("Distance mark: ");
  DEBUG_SENSOR_PRINTLN(tbikeDistance);

  if (tbikeDistance != bikeDistance){
    bitSet(bikeDataChanged,15);
    bikeDistance = tbikeDistance;
  }  
}
