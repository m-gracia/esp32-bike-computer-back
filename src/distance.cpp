#include "distance.h"
#include "my_def.h"
#include "my_debug.h"

void initDistance(){
  if(!tofDev.begin()) DEBUG_SENSOR_PRINTLN("Sensor init failed. Not found");
  else DEBUG_SENSOR_PRINTLN("Sensor init OK");
}

void getDistance(){
  VL53L0X_RangingMeasurementData_t measure;
  unsigned char distanceEcho;   // Distance measured in cm
  unsigned char tbikeDistance;
  
  tofDev.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) distanceEcho = measure.RangeMilliMeter/10;
  else distanceEcho = 255;

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

  delay(100);  // This is a waste of time
}
