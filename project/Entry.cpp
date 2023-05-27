#include <arduino.h>
#include "ProjectConfig.h"
#include "Serial.h"
#include "Storage.h"

void setup() {
  SERIAL_INIT(SERIAL_BAUD_RATE);
  Storage::Init();
}

void loop() {}
