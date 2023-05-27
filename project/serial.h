#ifndef SERIAL_HEADER
#define SERIAL_HEADER

#include <arduino.h>

#ifdef SERIAL_ENABLE

#define SERIAL_INIT(baud_rate) Serial.begin(baud_rate)
#define SERIAL_PRINT(v) Serial.print(v)
#define SERIAL_PRINTLN(v) Serial.println(v)

#else

#define SERIAL_INIT()
#define SERIAL_PRINT(v)
#define SERIAL_PRINTLN(v)

#endif

#endif
