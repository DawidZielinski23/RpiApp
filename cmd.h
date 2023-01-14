#ifndef _CMD_H
#define _CMD_H

#define GET_PIN_INFO_COMMAND      "pin"
#define GET_ALL_PINS_INFO_COMMAND "gpio_all"
#define GET_CPU_INFO_COMMAND      "cpu"
#define GET_ALL_CPU_INFO_COMMAND  "all"
#define GET_PI_INFO_COMMAND       "pi_info"
#define SET_DEBUGLOG_COMMAND      "debuglog"

#define COMMAND_LENGTH 10

typedef enum PI_COMMANDS
{
    GET_PIN_INFO      = 0,
    GET_ALL_PINS_INFO,
    GET_CPU_INFO,
    GET_ALL_CPU_INFO,
    GET_PI_INFO,
    SET_DEBUGLOG,
    COMMANDS_COUNT
} PI_COMMANDS;

bool CheckCommand(char* Command);
enum status CopyCommandArray(bool* Array, uint8_t ArraySize);
void UpperChars(char* Word, uint32_t Length);

#endif /* _CMD_H */