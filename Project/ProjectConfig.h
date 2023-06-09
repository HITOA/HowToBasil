#ifndef CONFIG_HEADER
#define CONFIG_HEADER

#define SERIAL_ENABLE
#define SERIAL_BAUD_RATE 115200

#define EEPROM_MAX_SIZE 4096

#define STATUS_IDLE              0
#define STATUS_PUMPING_PH_DOWN   1
#define STATUS_PUMPING_PH_UP     2
#define STATUS_PUMPING_NUTRIENTS 3

static const char* STATUS_STRING[] = {"Idle", "Pumping PH Down", "Pumping PH Up", "Pumping Nutrients"};

#define LED 13

#define END_OF_TIME 4294967295

#endif
