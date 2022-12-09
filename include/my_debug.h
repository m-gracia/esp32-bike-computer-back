/*
 * Debug functions
 */
#ifndef _MY_DEBUG_H_
#define _MY_DEBUG_H_

#define DEBUG       // General debug switch. No data sent if commented

// Uncomment to enable
#define DEBUG_BT
//#define DEBUG_SENSOR //Ultrasonic distance sensor



// Don't change below this line
#ifdef DEBUG
    #define DEBUG_PRINT(x)  Serial.print(x)
    #define DEBUG_PRINTLN(x)  Serial.println(x)

    #ifdef DEBUG_BT
    #define DEBUG_BT_PRINT(x)  Serial.print(x)
    #define DEBUG_BT_PRINTLN(x)  Serial.println(x)
    #else
    #define DEBUG_BT_PRINT(x)
    #define DEBUG_BT_PRINTLN(x)
    #endif

    #ifdef DEBUG_SENSOR
    #define DEBUG_SENSOR_PRINT(x)  Serial.print(x)
    #define DEBUG_SENSOR_PRINTLN(x)  Serial.println(x)
    #else
    #define DEBUG_SENSOR_PRINT(x)
    #define DEBUG_SENSOR_PRINTLN(x)
    #endif

#else
    #define DEBUG_PRINT(x)
    #define DEBUG_PRINTLN(x)
    #define DEBUG_BT_PRINT(x)
    #define DEBUG_BT_PRINTLN(x)
    #define DEBUG_SENSOR_PRINT(x)
    #define DEBUG_SENSOR_PRINTLN(x)
#endif

#endif  // _MY_DEBUG_H_