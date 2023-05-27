#include <arduino.h>
#include "config.h"
#include "serial.h"
#include "storage.h"

void setup() {
  SERIAL_INIT(SERIAL_BAUD_RATE);
  Storage::Init();
}

void loop() {}
