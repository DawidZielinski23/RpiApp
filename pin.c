#include"pin.h"

enum status GetPinInfo(PIN_INFO* Pin, uint8_t Number)
{
    char DirectionString[PATH_STRING_LENGTH] = {'\0'};
    char ModeString[MODE_STRING_LENGTH] = {'\0'};
    char ValuePath[PATH_STRING_LENGTH] = {'\0'};
    char PinNumber[PIN_STRING_LENGTH] = {'\0'};
    enum status Status = STATUS_OK;
    ssize_t WrittenBytes = 0;
    FILE* Descriptor = NULL;
    int ReadStatus = 0;
    char Value = 0;

    LOG_FUNCTION_NAME(__func__);

    do
    {
        if(Pin == NULL)
        {
            WriteDebugLog(DEBUG_LOGGING_CRITICAL_LEVEL, "Invalid parameter!");
            Status = STATUS_PARAM_ERR;
            break;
        }

        Pin->Number = Number;

        Descriptor = fopen(EXPORT_PATH, "r");
        if(Descriptor == NULL)
        {
            WriteDebugLog(DEBUG_LOGGING_CRITICAL_LEVEL, "Failed to fopen %s!", EXPORT_PATH);
            Status = STATUS_FILE_ERR;
            break;
        }

        snprintf(PinNumber, MODE_STRING_LENGTH, "%d", Pin->Number);

        WrittenBytes = write(Descriptor, PinNumber, strlen(PinNumber) - 1);
        if(WrittenBytes != (strlen(PinNumber) - 1))
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL, "Write to %s failed", EXPORT_PATH);
            Status = STATUS_WRITE_ERR;
            break;
        }

        fclose(Descriptor);

        Descriptor = fopen(DIRECTION_PATH(DirectionString, Pin->Number), "r");
        if(Descriptor == NULL)
        {
            WriteDebugLog(DEBUG_LOGGING_CRITICAL_LEVEL,
                          "Failed to fopen %s!",
                          DIRECTION_PATH(DirectionString, Pin->Number));
            Status = STATUS_FILE_ERR;
            break;
        }

        ReadStatus = read(Descriptor, ModeString , sizeof(ModeString));
        if(ReadStatus == -1)
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL,
                          "Reading %s failed",
                          DIRECTION_PATH(DirectionString, Pin->Number));
            Status = STATUS_READ_ERR;
            break;
        }

        fclose(Descriptor);

        if(!strncmp(ModeString, "in", strlen(ModeString) -1))
        {
            Pin->Mode = INPUT_MODE;
        }
        else if(!strncmp(ModeString, "out", strlen(ModeString) -1))
        {
            Pin->Mode = OUTPUT_MODE;
        }
        else
        {
            Pin->Mode = UNKNOWN_MODE;
        }

        Descriptor = fopen(VALUE_PATH(ValuePath, Pin->Number), "r");
        if(Descriptor == NULL)
        {
            WriteDebugLog(DEBUG_LOGGING_CRITICAL_LEVEL,
                          "Failed to fopen %s!",
                          VALUE_PATH(ValuePath, Pin->Number));
            Status = STATUS_FILE_ERR;
            break;
        }

        ReadStatus = read(Descriptor, Value, sizeof(Value));
        if(ReadStatus == -1)
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL,
                          "Reading %s failed",
                          VALUE_PATH(ValuePath, Pin->Number));
            Status = STATUS_READ_ERR;
            break;
        }

        fclose(Descriptor);

        Pin->Value = atoi(&Value);
    } while(0);

    LOG_FUNCTION_END(__func__);

    if(Descriptor != NULL)
    {
        fclose(Descriptor);
    }

    return Status;
}

char* GetPinModeString(PIN_MODE Mode)
{
    char * String = NULL;

    switch(Mode)
    {
    case INPUT_MODE:
        String = "Input";
        break;
    case OUTPUT_MODE:
        String = "Output";
        break;
    case UNKNOWN_MODE:
        String = "Unknown";
        break;
    }

    return String;
}
