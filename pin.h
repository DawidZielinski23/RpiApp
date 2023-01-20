#ifndef _PIN_H
#define _PIN_H

#include"libraries.h"

#define PATH_STRING_LENGTH 40
#define PIN_STRING_LENGTH  2
#define MODE_STRING_LENGTH 3
#define PINS_COUNT         40

#define EXPORT_PATH "sys/class/gpio/export"
#define DIRECTION_PATH(_str, _i) snprintf(_str, PATH_STRING_LENGTH, "/sys/class/gpio/gpio%d/direction", _i)
#define VALUE_PATH(_str, _i) snprintf(_str, PATH_STRING_LENGTH, "/sys/class/gpio/gpio%d/value", _i)

typedef enum PIN_MODE
{
    INPUT_MODE = 0,
    OUTPUT_MODE,
    UNKNOWN_MODE = 0xFF
} PIN_MODE;

typedef struct _PIN_INFO
{
    uint8_t  Number;
    PIN_MODE Mode;
    uint8_t  Value;
} PIN_INFO;


enum status GetPinInfo(PIN_INFO *Pin, uint8_t Number);
char* GetPinModeString(PIN_MODE Mode);

#endif /* _PIN_H*/