#ifndef _CMD_H
#define _CMD_H

#define GET_PIN_INFO_COMMAND      "pin"
#define GET_ALL_PINS_INFO_COMMAND "pin_all"
#define GET_CPU_INFO_COMMAND      "cpu"
#define GET_ALL_CPU_INFO_COMMAND  "cpu_all"
#define GET_PI_INFO_COMMAND       "pi_info"
#define SET_DEBUGLOG_COMMAND      "debuglog"

typedef enum _PI_COMMANDS
{
    GET_PIN_INFO      = 0,
    GET_ALL_PINS_INFO,
    GET_CPU_INFO,
    GET_ALL_CPU_INFO,
    GET_PI_INFO,
    SET_DEBUGLOG,
    COMMANDS_COUNT,
} _PI_COMMANDS

#endif /* _CMD_H */