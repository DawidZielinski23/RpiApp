#include"pin.h"

enum status GetPinInfo(PIN_INFO* Pin, uint8_t Number)
{
    char DirectionPath[PATH_STRING_LENGTH] = {'\0'};
    char ModeString[MODE_STRING_LENGTH] = {'\0'};
    char ValuePath[PATH_STRING_LENGTH] = {'\0'};
    char PinNumber[PIN_STRING_LENGTH] = {'\0'};
    enum status Status = STATUS_OK;
    FILE* Descriptor = NULL;
    char* Path = NULL;
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

        Descriptor = fopen(EXPORT_PATH, "w");
        if(Descriptor == NULL)
        {
            WriteDebugLog(DEBUG_LOGGING_CRITICAL_LEVEL, "Failed to fopen %s!", EXPORT_PATH);
            Status = STATUS_FILE_ERR;
            break;
        }

        snprintf(PinNumber, MODE_STRING_LENGTH, "%d", Pin->Number);

        if(fputs(PinNumber, Descriptor) == EOF)
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL, "Write to %s failed", EXPORT_PATH);
            Status = STATUS_WRITE_ERR;
            break;
        }

        fclose(Descriptor);
        Descriptor = NULL;

        DIRECTION_PATH(DirectionPath, Pin->Number);
        Descriptor = fopen(DirectionPath, "r");
        if(Descriptor == NULL)
        {
            WriteDebugLog(DEBUG_LOGGING_CRITICAL_LEVEL,
                          "Failed to fopen %s!",
                          Path);
            Status = STATUS_FILE_ERR;
            break;
        }

        if(fgets(ModeString, MODE_STRING_LENGTH, Descriptor) == NULL)
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL, "Reading %s failed", DirectionPath);
            Status = STATUS_READ_ERR;
            break;
        }

        fclose(Descriptor);
        Descriptor = NULL;

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

        VALUE_PATH(ValuePath, Pin->Number);
        Descriptor = fopen(ValuePath, "r");
        if(Descriptor == NULL)
        {
            WriteDebugLog(DEBUG_LOGGING_CRITICAL_LEVEL,
                          "Failed to fopen %s!",
                          Path);
            Status = STATUS_FILE_ERR;
            break;
        }

        if(fgets(&Value, sizeof(Value), Descriptor) == NULL)
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL, "Reading %s failed", ValuePath);
            Status = STATUS_READ_ERR;
            break;
        }

        Pin->Value = atoi(&Value);

        fclose(Descriptor);
        Descriptor = NULL;

        Descriptor = fopen(UNEXPORT_PATH, "w");
        if(Descriptor == NULL)
        {
            WriteDebugLog(DEBUG_LOGGING_CRITICAL_LEVEL, "Failed to fopen %s!", UNEXPORT_PATH);
            Status = STATUS_FILE_ERR;
            break;
        }

        if(fputs(PinNumber, Descriptor) == EOF)
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL, "Write to %s failed", UNEXPORT_PATH);
            Status = STATUS_WRITE_ERR;
            break;
        }

        fclose(Descriptor);
        Descriptor = NULL;
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
