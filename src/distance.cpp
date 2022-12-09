#include "distance.h"
#include "my_def.h"
#include "my_debug.h"

void consultaDistancia(){
  int tiempoEcho;
  unsigned char tbikeDistance;

  digitalWrite(DIST_PIN_TRIGG,LOW);
  delayMicroseconds(2);
  
  digitalWrite(DIST_PIN_TRIGG,HIGH); // Throw trigger
  delayMicroseconds(20);  
  digitalWrite(DIST_PIN_TRIGG,LOW);
  tiempoEcho=pulseIn(DIST_PIN_ECHO,HIGH,14790); //14790us = 255cm

  if (tiempoEcho == 0) distanciaEcho = 255;
  else distanciaEcho=tiempoEcho/58;

  DEBUG_SENSOR_PRINT("Distance: ");
  DEBUG_SENSOR_PRINTLN(distanciaEcho);

  if (distanciaEcho < distanciaMostrar1) tbikeDistance = 5;      // Closest
  else if (distanciaEcho < distanciaMostrar2) tbikeDistance = 4; 
  else if (distanciaEcho < distanciaMostrar3) tbikeDistance = 3;
  else if (distanciaEcho < distanciaMostrar4) tbikeDistance = 2;
  else if (distanciaEcho < distanciaMostrar) tbikeDistance = 1;  // Farthest
  else tbikeDistance = STATUS_OK; // No detection or too far
  
  DEBUG_SENSOR_PRINT("Distance mark: ");
  DEBUG_SENSOR_PRINTLN(tbikeDistance);

  if (tbikeDistance != bikeDistance){
    bitSet(bikeDataChanged,15);
    bikeDistance = tbikeDistance;
  }  
}
