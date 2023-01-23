#include "cmd.h"

static char Global_CommandsString[COMMANDS_COUNT][COMMAND_LENGTH] =
{
    { SET_DEBUGLOG_COMMAND },
    { APP_HELP_COMMAND },
    { GET_PIN_INFO_COMMAND },
    { GET_ALL_PINS_INFO_COMMAND },
    { GET_CPU_INFO_COMMAND },
    { GET_ALL_CPU_INFO_COMMAND },
    { GET_PI_INFO_COMMAND }
};

static bool Global_CommandsActive[COMMANDS_COUNT] =
{
    false,
    false,
    false,
    false,
    false,
    false,
    false
};

static uint32_t Global_CommandsValues[COMMANDS_COUNT] =
{
    0,
    0,
    0,
    0,
    0,
    0,
    0
};

bool CheckCommand(char* Command)
{
    char* AuxiliaryCommand = NULL;
    bool EqualSignFound = false;
    bool CommandValid = false;
    char* Pointer = NULL;
    uint32_t Length = 0;
    uint32_t Index = 0;
    uint32_t Value = 0;

    LOG_FUNCTION_NAME(__func__);

    do
    {
        if((Command == NULL) || (strlen(Command) == 0))
        {
            printf("Wrong command passed!\n");
        }

        if((Command[0] == '-') || (Command[0] == '/'))
        {
            Command++;
        }

        for(Index = 0; Index < strlen(Command); Index++)
        {
            if(Command[Index] == '=')
            {
                Pointer = Command + Index + 1;
                Value = atoi(Pointer);
                EqualSignFound = true;
                break;
            }
        }

        if(EqualSignFound == true)
        {
            Length = Index;
        }
        else
        {
            Length = strlen(Command);
        }

        AuxiliaryCommand = malloc(sizeof(char) * (Length + 1));
        if(AuxiliaryCommand == NULL)
        {
            WriteDebugLog(DEBUG_LOGGING_CRITICAL_LEVEL, "Memory error");
            break;
        }

        memcpy(AuxiliaryCommand, Command, Length);
        AuxiliaryCommand[Length] = '\0';

        UpperChars(AuxiliaryCommand, Length);

        for(Index = 0; Index < COMMANDS_COUNT; Index++)
        {
            if(!strncmp(AuxiliaryCommand, Global_CommandsString[Index], COMMAND_LENGTH))
            {
                Global_CommandsActive[Index] = true;
                if(EqualSignFound == true)
                {
                    Global_CommandsValues[Index] = Value;
                }
                CommandValid = true;
                break;
            }
        }

        if(CommandValid == false)
        {
            printf("Invalid command %s!\n", Command);
        }
    } while(0);

    if(AuxiliaryCommand != NULL)
    {
        free(AuxiliaryCommand);
    }

    return CommandValid;
}

enum status CopyCommandArray(bool* Array, uint8_t ArraySize)
{
    enum status Status = STATUS_OK;

    if((Array != NULL) && (ArraySize == COMMANDS_COUNT))
    {
        memcpy(Array, Global_CommandsActive, sizeof(bool) * COMMANDS_COUNT);
    }
    else
    {
        WriteDebugLog(DEBUG_LOGGING_CRITICAL_LEVEL, "Invalid array or array size!");
        Status = STATUS_PARAM_ERR;
    }

    return Status;
}

enum status CopyValueArray(uint32_t* Array, uint8_t ArraySize)
{
    enum status Status = STATUS_OK;

    if((Array != NULL) && (ArraySize == COMMANDS_COUNT))
    {
        memcpy(Array, Global_CommandsValues, sizeof(uint32_t) * COMMANDS_COUNT);
    }
    else
    {
        WriteDebugLog(DEBUG_LOGGING_CRITICAL_LEVEL, "Invalid array or array size!");
        Status = STATUS_PARAM_ERR;
    }

    return Status;
}

void UpperChars(char* Word, uint32_t Length)
{
    uint32_t Index;

    if((Word != NULL) && Length != 0)
    {
        for(Index = 0; Index <= Length; Index++)
        {
            if((Word[Index] >= 'a') && (Word[Index] <= 'z'))
            {
                Word[Index]+= ('A' - 'a');
            }
        }
    }
}