#include"cpu.h"

static PI_INFO Global_RevisionCodeInfo[PI_NUMBER_OF_REVISIONS] =
{
    {"900021", PI_MODEL_AP,   PI_REV_1_1, PI_RAM_512MB, PI_MAN_SONY_UK   },
    {"900032", PI_MODEL_BP,   PI_REV_1_2, PI_RAM_512MB, PI_MAN_SONY_UK   },
    {"900092", PI_MODEL_0,    PI_REV_1_2, PI_RAM_512MB, PI_MAN_SONY_UK   },
    {"900093", PI_MODEL_0,    PI_REV_1_3, PI_RAM_512MB, PI_MAN_SONY_UK   },
    {"9000c1", PI_MODEL_0W,   PI_REV_1_1, PI_RAM_512MB, PI_MAN_SONY_UK   },
    {"9020e0", PI_MODEL_3AP,  PI_REV_1_0, PI_RAM_512MB, PI_MAN_SONY_UK   },
    {"900092", PI_MODEL_0,    PI_REV_1_2, PI_RAM_512MB, PI_MAN_EMBEST    },
    {"900093", PI_MODEL_0,    PI_REV_1_3, PI_RAM_512MB, PI_MAN_EMBEST    },
    {"900061", PI_MODEL_CM1,  PI_REV_1_1, PI_RAM_512MB, PI_MAN_SONY_UK   },
    {"a01040", PI_MODEL_2B,   PI_REV_1_0, PI_RAM_1GB,   PI_MAN_SONY_UK   },
    {"a01041", PI_MODEL_2B,   PI_REV_1_1, PI_RAM_1GB,   PI_MAN_SONY_UK   },
    {"a02082", PI_MODEL_3B,   PI_REV_1_2, PI_RAM_1GB,   PI_MAN_SONY_UK   },
    {"a020a0", PI_MODEL_CM3,  PI_REV_1_0, PI_RAM_1GB,   PI_MAN_SONY_UK   },
    {"a020d3", PI_MODEL_3BP,  PI_REV_1_3, PI_RAM_1GB,   PI_MAN_SONY_UK   },
    {"a02042", PI_MODEL_2B,   PI_REV_1_2, PI_RAM_1GB,   PI_MAN_SONY_UK   },
    {"a21041", PI_MODEL_2B,   PI_REV_1_1, PI_RAM_1GB,   PI_MAN_EMBEST    },
    {"a22042", PI_MODEL_2B,   PI_REV_1_2, PI_RAM_1GB,   PI_MAN_EMBEST    },
    {"a22082", PI_MODEL_3B,   PI_REV_1_2, PI_RAM_1GB,   PI_MAN_EMBEST    },
    {"a220a0", PI_MODEL_CM3,  PI_REV_1_0, PI_RAM_1GB,   PI_MAN_EMBEST    },
    {"a32082", PI_MODEL_3B,   PI_REV_1_2, PI_RAM_1GB,   PI_MAN_SONY_JAPAN},
    {"a52082", PI_MODEL_3B,   PI_REV_1_2, PI_RAM_1GB,   PI_MAN_STADIUM   },
    {"a22083", PI_MODEL_3B,   PI_REV_1_2, PI_RAM_1GB,   PI_MAN_EMBEST    },
    {"a02100", PI_MODEL_CM3P, PI_REV_1_0, PI_RAM_1GB,   PI_MAN_SONY_UK   },
    {"a03111", PI_MODEL_4B,   PI_REV_1_1, PI_RAM_1GB,   PI_MAN_SONY_UK   },
    {"b03111", PI_MODEL_4B,   PI_REV_1_1, PI_RAM_2GB,   PI_MAN_SONY_UK   },
    {"b03112", PI_MODEL_4B,   PI_REV_1_2, PI_RAM_2GB,   PI_MAN_SONY_UK   },
    {"b03114", PI_MODEL_4B,   PI_REV_1_4, PI_RAM_2GB,   PI_MAN_SONY_UK   },
    {"b03115", PI_MODEL_4B,   PI_REV_1_5, PI_RAM_2GB,   PI_MAN_SONY_UK   },
    {"c03111", PI_MODEL_4B,   PI_REV_1_1, PI_RAM_4GB,   PI_MAN_SONY_UK   },
    {"c03112", PI_MODEL_4B,   PI_REV_1_2, PI_RAM_4GB,   PI_MAN_SONY_UK   },
    {"c03114", PI_MODEL_4B,   PI_REV_1_4, PI_RAM_4GB,   PI_MAN_SONY_UK   },
    {"c03115", PI_MODEL_4B,   PI_REV_1_5, PI_RAM_4GB,   PI_MAN_SONY_UK   },
    {"d03114", PI_MODEL_4B,   PI_REV_1_4, PI_RAM_8GB,   PI_MAN_SONY_UK   },
    {"d03115", PI_MODEL_4B,   PI_REV_1_5, PI_RAM_8GB,   PI_MAN_SONY_UK   },
    {"c03130", PI_MODEL_400,  PI_REV_1_0, PI_RAM_4GB,   PI_MAN_SONY_UK   },
    {"a03140", PI_MODEL_CM4,  PI_REV_1_0, PI_RAM_1GB,   PI_MAN_SONY_UK   },
    {"b03140", PI_MODEL_CM4,  PI_REV_1_0, PI_RAM_2GB,   PI_MAN_SONY_UK   },
    {"c03140", PI_MODEL_CM4,  PI_REV_1_0, PI_RAM_4GB,   PI_MAN_SONY_UK   },
    {"d03140", PI_MODEL_CM4,  PI_REV_1_0, PI_RAM_8GB,   PI_MAN_SONY_UK   },
    {"902120", PI_MODEL_02W,  PI_REV_1_0, PI_RAM_512MB, PI_MAN_SONY_UK   }
};

static char Global_PiModelString[PI_MODEL_COUNT][PI_MODEL_STRING_LENGTH] =
{
    "A",
    "A+",
    "B",
    "B+",
    "CM1",
    "CM3",
    "CM3+",
    "CM4",
    "Zero",
    "Zero W",
    "Zero 2 W",
    "2A",
    "2B",
    "3A",
    "3A+",
    "3B",
    "3B+",
    "4B",
    "Pi 400",
    "Unknown"
};

static char Global_PiRevisionString[PI_REV_COUNT][PI_REV_STRING_LENGTH] =
{
    "1.0",
    "1.1",
    "1.2",
    "1.3",
    "1.4",
    "1.5",
    "Unknown"
};

static char Global_PiRamString[PI_RAM_COUNT][PI_RAM_STRING_LENGTH] =
{
    "512 MB",
    "1 GB",
    "2 GB",
    "4 GB",
    "8 GB",
    "Unknown"
};

static char Global_PiManufacturerString[PI_MAN_COUNT][PI_MAN_STRING_LENGTH] =
{
    "Embest",
    "Egoman",
    "Qisda",
    "Sony UK",
    "Sony Japan",
    "Stadium",
    "Unknown"
};

char* GetPiRevisionCode(uint8_t Index)
{
    char* RevisionCode = NULL;

    if(Index < PI_NUMBER_OF_REVISIONS)
    {
        RevisionCode = Global_RevisionCodeInfo[Index].RevisionCode;
    }
    else
    {
        RevisionCode = "Unknown";
    }

    return RevisionCode;
}

PI_MODEL GetPiModel(uint8_t Index)
{
    PI_MODEL Model = PI_MODEL_UNKNOWN;

    if(Index < PI_NUMBER_OF_REVISIONS)
    {
        Model = Global_RevisionCodeInfo[Index].Model;
    }

    return Model;
}

PI_REVISION GetPiRevision(uint8_t Index)
{
    PI_REVISION Revision = PI_REV_UNKNOWN;

    if(Index < PI_NUMBER_OF_REVISIONS)
    {
        Revision = Global_RevisionCodeInfo[Index].Revision;
    }

    return Revision;
}

PI_RAM GetPiRam(uint8_t Index)
{
    PI_RAM Ram = PI_RAM_UNKNOWN;

    if(Index < PI_NUMBER_OF_REVISIONS)
    {
        Ram = Global_RevisionCodeInfo[Index].Ram;
    }

    return Ram;
}

PI_MANUFACTURER GetPiManufacturer(uint8_t Index)
{
    PI_MANUFACTURER Manufacturer = PI_MAN_UNKNOWN;

    if(Index < PI_NUMBER_OF_REVISIONS)
    {
        Manufacturer = Global_RevisionCodeInfo[Index].Manufacturer;
    }

    return Manufacturer;
}

char* GetPiModelString(uint8_t Index)
{
    char* PiModelString = NULL;

    if(Index < PI_MODEL_COUNT)
    {
        PiModelString = Global_PiModelString[Index];
    }
    else
    {
        PiModelString = Global_PiModelString[PI_MODEL_COUNT - 1];
    }

    return PiModelString;
}

char* GetPiRevisionString(uint8_t Index)
{
    char* PiRevisionString = NULL;

    if(Index < PI_REV_COUNT)
    {
        PiRevisionString = Global_PiRevisionString[Index];
    }
    else
    {
        PiRevisionString = Global_PiRevisionString[PI_REV_COUNT - 1];
    }

    return PiRevisionString;
}

char* GetPiRamString(uint8_t Index)
{
    char* PiRamString = NULL;

    if(Index < PI_RAM_COUNT)
    {
        PiRamString = Global_PiRamString[Index];
    }
    else
    {
        PiRamString = Global_PiRamString[PI_RAM_COUNT - 1];
    }

    return PiRamString;
}

char* GetPiManufacturerString(uint8_t Index)
{
    char* PiManufacturerString = NULL;

    if(Index < PI_MAN_COUNT)
    {
        PiManufacturerString = Global_PiManufacturerString[Index];
    }
    else
    {
        PiManufacturerString = Global_PiManufacturerString[PI_MAN_COUNT - 1];
    }

    return PiManufacturerString;
}

enum status GetPiBasicInfo(PI_INFO* PiInfo, char* Bcm, char* Serial)
{
    char ReadLine[MAX_LINE_LENGTH] = {'\0'};
    enum status Status = STATUS_OK;
    FILE* FileDescriptor = NULL;
    bool HardwareFound = false;
    bool RevisionFound = false;
    char* RevisionCode = NULL;
    bool SerialFound = false;
    char* String = NULL;
    uint8_t Index = 0;

    LOG_FUNCTION_NAME(__func__);

    do
    {
        if(PiInfo == NULL || Bcm == NULL || Serial == NULL)
        {
            WriteDebugLog(DEBUG_LOGGING_CRITICAL_LEVEL, "Invalid parameter!");
            Status = STATUS_PARAM_ERR;
            break;
        }

        FileDescriptor = fopen(CPUINFO_PATH, "r");
        if(FileDescriptor == NULL)
        {
            WriteDebugLog(DEBUG_LOGGING_CRITICAL_LEVEL, "Failed to open %s!", CPUINFO_PATH);
            Status = STATUS_FILE_ERR;
            break;
        }

        while(fgets(ReadLine, MAX_LINE_LENGTH, FileDescriptor) != NULL)
        {
            if(!strncmp(ReadLine, HARDWARE_STRING, HARDWARE_STRING_LENGTH))
            {
                WriteDebugLog(DEBUG_LOGGING_INFO_LEVEL, "\"%s\" found.", HARDWARE_STRING);
                HardwareFound = true;
                break;
            }
        }

        if(HardwareFound == false)
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL,
                          "\"%s\" not found in %s.",
                          HARDWARE_STRING,
                          CPUINFO_PATH);
            Status = STATUS_READ_ERR;
            break;
        }

        String = ReadLine + HARDWARE_STRING_LENGTH;
        String = strstr(String, ":");
        if(String == NULL)
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL, "\":\" not found.");
            Status = STATUS_STR_ERR;
            break;
        }

        String = String + 2;
        strncpy(Bcm, String, BCM_STRING_LENGTH - 1);
        if(Bcm == NULL)
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL, "String operation failed.");
            Status = STATUS_STR_ERR;
            break;
        }

        Bcm[BCM_STRING_LENGTH] = '\0';

        rewind(FileDescriptor);

        while(fgets(ReadLine, MAX_LINE_LENGTH, FileDescriptor) != NULL)
        {
            if(!strncmp(ReadLine, REVISION_STRING, REVISION_STRING_LENGTH))
            {
                WriteDebugLog(DEBUG_LOGGING_INFO_LEVEL, "\"%s\" found.", REVISION_STRING);
                RevisionFound = true;
                break;
            }
        }

        if(RevisionFound == false)
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL,
                          "\"%s\" not found in %s.",
                          REVISION_STRING,
                          CPUINFO_PATH);
            Status = STATUS_READ_ERR;
            break;
        }

        String = ReadLine + REVISION_STRING_LENGTH;
        String = strstr(String, ":");
        if(String == NULL)
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL, "\":\" not found.");
            Status = STATUS_STR_ERR;
            break;
        }

        String = String + 2;
        strncpy(PiInfo->RevisionCode, String, PI_REVISION_CODE_LENGTH - 1);
        if(Bcm == NULL)
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL, "String operation failed.");
            Status = STATUS_STR_ERR;
            break;
        }

        PiInfo->RevisionCode[PI_REVISION_CODE_LENGTH] = '\0';

        for(Index = 0; Index < PI_NUMBER_OF_REVISIONS; Index++)
        {
            RevisionCode = GetPiRevisionCode(Index);
            if(!strncmp(PiInfo->RevisionCode, RevisionCode, PI_REVISION_CODE_LENGTH))
            {
                break;
            }
        }

        if(Index == PI_NUMBER_OF_REVISIONS)
        {
            WriteDebugLog(DEBUG_LOGGING_WARNING_LEVEL,
                          "Unknown revision code. Setting information to unknown");
            PiInfo->Model = PI_MODEL_UNKNOWN;
            PiInfo->Revision = PI_REV_UNKNOWN;
            PiInfo->Ram = PI_RAM_UNKNOWN;
            PiInfo->Manufacturer = PI_MAN_UNKNOWN;
        }
        else
        {
            PiInfo->Model = GetPiModel(Index);
            PiInfo->Revision = GetPiRevision(Index);
            PiInfo->Ram = GetPiRam(Index);
            PiInfo->Manufacturer = GetPiManufacturer(Index);
        }

        rewind(FileDescriptor);

        while(fgets(ReadLine, MAX_LINE_LENGTH, FileDescriptor) != NULL)
        {
            if(!strncmp(ReadLine, SERIAL_STRING, SERIAL_STRING_LENGTH))
            {
                WriteDebugLog(DEBUG_LOGGING_INFO_LEVEL, "\"%s\" found.", SERIAL_STRING);
                SerialFound = true;
                break;
            }
        }

        if(SerialFound == false)
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL,
                          "\"%s\" not found in %s.",
                          SERIAL_STRING,
                          CPUINFO_PATH);
            Status = STATUS_READ_ERR;
            break;
        }

        String = ReadLine + SERIAL_STRING_LENGTH;
        String = strstr(String, ":");
        if(String == NULL)
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL, "\":\" not found.");
            Status = STATUS_STR_ERR;
            break;
        }

        String = String + 2;
        strncpy(Serial, String, SERIAL_VALUE_LENGTH - 1);
        if(Serial == NULL)
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL, "String operation failed.");
            Status = STATUS_STR_ERR;
            break;
        }

        Serial[SERIAL_VALUE_LENGTH] = '\0';
    } while(0);

    if(FileDescriptor != NULL)
    {
        fclose(FileDescriptor);
    }

    LOG_FUNCTION_END(__func__);

    return Status;
}