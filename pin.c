#include"pin.h"

void GetPinInfo(PIN_INFO* Pin)
{
    int Descriptor;
    char PinNumber[PIN_STRING_LENGTH];
    char DirectionString[PATH_STRING_LENGTH];
    char ValuePath[PATH_STRING_LENGTH];
    char ModeString[MODE_STRING_LENGTH];
    char Value;
    ssize_t WrittenBytes;
    int ReadStatus;

    do
    {
        if(GetPinInfo == NULL)
        {
            break;
        }

        Descriptor = open(EXPORT_PATH, O_WRONGLY);
        if(Descriptor == -1)
        {
            break;
        }

        snprintf(PinNumber, MODE_STRING_LENGTH, "%d", Pin->Number);

        WrittenBytes = write(Descriptor, PinNumber, strlen(PinNumber) - 1);
        if(WrittenBytes != (strlen(PinNumber) - 1)
        {
            break;
        }

        close(Descriptor);

        Descriptor = open(DIRECTION_PATH(DirectionString, Pin->Number), O_WRONGLY);
        if(Descriptor == -1)
        {
            break;
        }

        ReadStatus = read(Descriptor, ModeString , sizeof(ModeString))
        if(ReadStatus == -1)
        {
            break;
        }

        close(Descriptor);

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

        Descriptor open(VALUE_PATH(ValuePath, Pin->Number), O_WRONLY);
        if(Descriptor == -1)
        {
            break;
        }

        ReadStatus = read(Descriptor, Value, sizeof(Value));
        if(ReadStatus == -1)
        {
            break;
        }

        close(Descriptor);

        Pin->Value = atoi(&Value);
    } while(0);
}