#ifndef _CMD_H
#define _CMD_H

#include "libraries.h"

#define GET_PIN_INFO_COMMAND      "PIN"
#define GET_ALL_PINS_INFO_COMMAND "GPIO_ALL"
#define GET_CPU_INFO_COMMAND      "CPU"
#define GET_ALL_CPU_INFO_COMMAND  "ALL"
#define GET_PI_INFO_COMMAND       "PI_INFO"
#define SET_DEBUGLOG_COMMAND      "DEBUGLOG"
#define APP_HELP_COMMAND              "HELP"

#define COMMAND_LENGTH 10

typedef enum PI_COMMANDS
{
    SET_DEBUGLOG      = 0,
    SHOW_HELP,
    GET_PIN_INFO,
    GET_ALL_PINS_INFO,
    GET_CPU_INFO,
    GET_ALL_CPU_INFO,
    GET_PI_INFO,
    COMMANDS_COUNT
} PI_COMMANDS;

bool CheckCommand(char* Command);
enum status CopyCommandArray(bool* Array, uint8_t ArraySize);
enum status CopyValueArray(uint32_t* Array, uint8_t ArraySize);
void UpperChars(char* Word, uint32_t Length);

#endif /* _CMD_H */