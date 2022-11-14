#include"cpu.h"

static PI_INFO Global_RevisionCodeInfo[PI_NUMBER_OF_REVISIONS] =
{
    {"900021", PI_MODEL_AP,   PI_REV_1_1, PI_RAM_512MB, PI_MAN_SONY_UK   },
    {"900032", PI_MODEL_BP,   PI_REV_1_2, PI_RAM_512MB, PI_MAN_SONY_UK   },
    {"900092", PI_MODEL_0,    PI_REV_1_2, PI_RAM_512MB, PI_MAN_SONY_UK   },
    {"900093", PI_MODEL_0,    PI_REV_1_3, PI_RAM_512MB, PI_MAN_SONY_UK   },
    {"9000c1", PI_MODEL_0W,   PI_REV_1_1, PI_RAM_512MB, PI_MAN_SONY_UK   },
    {"9020e0", PI_MODEL_3AP,  PI_REV_1_0, PI_RAM_512MB, PI_MAN_SONY_UK   },
    {"920092", PI_MODEL_0,    PI_REV_1_2, PI_RAM_512MB, PI_MAN_EMBEST    },
    {"920093", PI_MODEL_0,    PI_REV_1_3, PI_RAM_512MB, PI_MAN_EMBEST    },
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

enum status DecodePiInfoFromRevisionCode(PI_INFO* PiInfo)
{
    char ModelCharacters[PI_MODEL_CHARACTERS] = {'\0'};
    char ManufacturerCharacter = '\0';
    enum status Status = STATUS_OK;
    char RevisionCharacter = '\0';
    char MemoryCharacter = '\0';
    uint32_t ModelCode = 0;
    uint8_t Index = 0;

    LOG_FUNCTION_NAME(__func__);

    do
    {
        if((PiInfo == NULL))
        {
            WriteDebugLog(DEBUG_LOGGING_CRITICAL_LEVEL, "Invalid parameter!");
            Status = STATUS_PARAM_ERR;
            break;
        }

        if(strlen(PiInfo->RevisionCode) != PI_REVISION_CODE_LENGTH - 1)
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL, "Invalid revision code.");
            Status = STATUS_PARAM_ERR;
            break;
        }

        PiInfo->Model = PI_MODEL_UNKNOWN;
        PiInfo->Revision = PI_REV_UNKNOWN;
        PiInfo->Ram = PI_RAM_UNKNOWN;
        PiInfo->Manufacturer = PI_MAN_UNKNOWN;

        MemoryCharacter = PiInfo->RevisionCode[0];
        ManufacturerCharacter = PiInfo->RevisionCode[1];
        RevisionCharacter = PiInfo->RevisionCode[5];
        for(Index = 0; Index < PI_MODEL_CHARACTERS - 1; Index++)
        {
            ModelCharacters[0] = PiInfo->RevisionCode[Index + 2];
        }
        ModelCharacters[PI_MODEL_CHARACTERS] = '\0';

        ModelCode = strtoul(ModelCharacters, NULL, 16);

        /* Memory */
        switch(MemoryCharacter)
        {
        case '9':
            PiInfo->Ram = PI_RAM_512MB;
            break;
        case 'a':
            PiInfo->Ram = PI_RAM_1GB;
            break;
        case 'b':
            PiInfo->Ram = PI_RAM_2GB;
            break;
        case 'c':
            PiInfo->Ram = PI_RAM_4GB;
            break;
        case 'd':
            PiInfo->Ram = PI_RAM_8GB;
            break;
        default:
            WriteDebugLog(DEBUG_LOGGING_WARNING_LEVEL, "Unknown memory character.");
            break;
        }

        /* Manufacturer */
        switch(ManufacturerCharacter)
        {
        case '0':
            PiInfo->Manufacturer = PI_MAN_SONY_UK;
            break;
        case '2':
            PiInfo->Manufacturer = PI_MAN_EMBEST;
            break;
        case '3':
            PiInfo->Manufacturer = PI_MAN_SONY_JAPAN;
            break;
        case '5':
            PiInfo->Manufacturer = PI_MAN_STADIUM;
            break;
        default:
            WriteDebugLog(DEBUG_LOGGING_WARNING_LEVEL, "Unknown manufacturer character.");
            break;
        }

        /* Revision */
        switch(RevisionCharacter)
        {
        case '0':
            PiInfo->Revision = PI_REV_1_0;
            break;
        case '1':
            PiInfo->Revision = PI_REV_1_1;
            break;
        case '2':
            PiInfo->Revision = PI_REV_1_2;
            break;
        case '3':
            PiInfo->Revision = PI_REV_1_3;
            break;
        case '4':
            PiInfo->Revision = PI_REV_1_4;
            break;
        case '5':
            PiInfo->Revision = PI_REV_1_5;
            break;
        default:
            WriteDebugLog(DEBUG_LOGGING_WARNING_LEVEL, "Unknown revision character.");
            break;
        }

        /* Model */
        switch(ModelCode)
        {
        case 0x2:
            PiInfo->Model = PI_MODEL_AP;
            break;
        case 0x3:
            PiInfo->Model = PI_MODEL_BP;
            break;
        case 0x9:
            PiInfo->Model = PI_MODEL_0;
            break;
        case 0xC:
            PiInfo->Model = PI_MODEL_0W;
            break;
        case 0xE:
            PiInfo->Model = PI_MODEL_3AP;
            break;
        case 0x6:
            PiInfo->Model = PI_MODEL_CM1;
            break;
        case 0x104:
        case 0x204:
            PiInfo->Model = PI_MODEL_2B;
            break;
        case 0x208:
            PiInfo->Model = PI_MODEL_3B;
            break;
        case 0x20A:
            PiInfo->Model = PI_MODEL_CM3;
            break;
        case 0x20D:
            PiInfo->Model = PI_MODEL_3BP;
            break;
        case 0x210:
            PiInfo->Model = PI_MODEL_CM3P;
            break;
        case 0x311:
            PiInfo->Model = PI_MODEL_4B;
            break;
        case 0x313:
            PiInfo->Model = PI_MODEL_400;
            break;
        case 0x314:
            PiInfo->Model = PI_MODEL_CM4;
            break;
        case 0x212:
            PiInfo->Model = PI_MODEL_02W;
            break;
        default:
            WriteDebugLog(DEBUG_LOGGING_WARNING_LEVEL, "Unknown model number.");
            break;
        }
    } while (0);

    LOG_FUNCTION_END(__func__);

    return Status;
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
        if((PiInfo == NULL) || (Bcm == NULL) || (Serial == NULL))
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
                          "Unknown revision code. Trying to decode it.");
            Status = DecodePiInfoFromRevisionCode(PiInfo);
            if(Status != STATUS_OK)
            {
                WriteDebugLog(DEBUG_LOGGING_WARNING_LEVEL,
                              "Failed to decode information from revision code. Setting values to unknown");
                PiInfo->Model = PI_MODEL_UNKNOWN;
                PiInfo->Revision = PI_REV_UNKNOWN;
                PiInfo->Ram = PI_RAM_UNKNOWN;
                PiInfo->Manufacturer = PI_MAN_UNKNOWN;
                Status = STATUS_OK;
            }
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

enum status DiscoverCpuNumber(uint8_t* Count)
{
    char ReadLine[MAX_LINE_LENGTH] = {'\0'};
    enum status Status = STATUS_OK;
    FILE* FileDescriptor = NULL;

    LOG_FUNCTION_NAME(__func__);

    do
    {
        if(Count == NULL)
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

        *Count = 0;

        while(fgets(ReadLine, MAX_LINE_LENGTH, FileDescriptor) != NULL)
        {
            if(!strncmp(ReadLine, PROCESSOR_STRING, PROCESSOR_STRING_LENGTH))
            {
                WriteDebugLog(DEBUG_LOGGING_INFO_LEVEL, "\"%s\" found.", PROCESSOR_STRING);
                *Count++;
            }
        }

        if(*Count == 0)
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL,
                          "\"%s\" not found. No CPU discovered.",
                          PROCESSOR_STRING);
            Status = STATUS_READ_ERR;
            break;
        }
    } while(0);

    if(FileDescriptor != NULL)
    {
        fclose(FileDescriptor);
    }

    LOG_FUNCTION_END(__func__);

    return Status;
}

enum status GetCpuInformation(CPU_INFO* CpuInfo, uint8_t CpuNumber)
{
    char ReadLine[MAX_LINE_LENGTH] = {'\0'};
    enum status Status = STATUS_OK;
    bool CpuStringsFound = false;
    FILE* FileDescriptor = NULL;
    uint8_t ReadCpuNumber = 0;
    bool CpuFound = false;
    char* String = NULL;

    LOG_FUNCTION_NAME(__func__);

    do
    {
        if(CpuInfo == NULL)
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
            if(!strncmp(ReadLine, PROCESSOR_STRING, PROCESSOR_STRING_LENGTH))
            {
                String = ReadLine + PROCESSOR_STRING_LENGTH;
                String = strstr(String, ":");
                if(String == NULL)
                {
                    WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL, "\":\" not found.");
                    break;
                }

                String = String + 2;
                ReadCpuNumber = (uint8_t)strtoul(ReadLine, NULL, 10);
                if(ReadCpuNumber == CpuNumber)
                {
                    WriteDebugLog(DEBUG_LOGGING_INFO_LEVEL, "CPU number %d found.", CpuNumber);
                    CpuFound = true;
                    break;
                }
            }
        }

        if(CpuFound == false)
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL, "CPU number %d not found.", CpuNumber);
            Status = STATUS_READ_ERR;
            break;
        }

        if(fgets(ReadLine, MAX_LINE_LENGTH, FileDescriptor) == NULL)
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL, "Read from file failed.");
            Status = STATUS_READ_ERR;
            break;
        }

        if(strncmp(ReadLine, MODEL_NAME_STRING, MODEL_NAME_STRING_LENGTH))
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL,
                          "\"%s\" not found in $s.",
                          MODEL_NAME_STRING,
                          CPUINFO_PATH);
            Status = STATUS_READ_ERR;
            break;
        }

        String = ReadLine + MODEL_NAME_STRING_LENGTH;
        String = strstr(String, ":");
        if(String == NULL)
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL, "\":\" not found.");
            Status = STATUS_STR_ERR;
            break;
        }

        String = String + 2;
        strncpy(CpuInfo->Name, String, MAX_LINE_LENGTH - 1);
        if(CpuInfo->Name == NULL)
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL, "String operation failed.");
            Status = STATUS_STR_ERR;
            break;
        }

        while(fgets(ReadLine, MAX_LINE_LENGTH, FileDescriptor) != NULL)
        {
            if(!strncmp(ReadLine, IMPLEMENTER_STRING, IMPLEMENTER_STRING_LENGTH))
            {
                CpuStringsFound = true;
                break;
            }
        }

        if(CpuStringsFound == false)
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL,
                          "\"%s\" not found in %s.",
                          IMPLEMENTER_STRING,
                          CPUINFO_PATH);
            Status = STATUS_READ_ERR;
            break;
        }

        String = ReadLine + MODEL_NAME_STRING_LENGTH;
        String = strstr(String, ":");
        if(String == NULL)
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL, "\":\" not found.");
            Status = STATUS_STR_ERR;
            break;
        }

        String = String + 2;
        CpuInfo->Implementer = (uint8_t)strtoul(String, NULL, 16);

        if(fgets(ReadLine, MAX_LINE_LENGTH, FileDescriptor) == NULL)
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL, "Read from file failed.");
            Status = STATUS_READ_ERR;
            break;
        }

        if(strncmp(ReadLine, ARCHITECTURE_STRING, ARCHITECTURE_STRING_LENGTH))
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL,
                          "\"%s\" not found in $s.",
                          ARCHITECTURE_STRING,
                          CPUINFO_PATH);
            Status = STATUS_READ_ERR;
            break;
        }

        String = ReadLine + ARCHITECTURE_STRING_LENGTH;
        String = strstr(String, ":");
        if(String == NULL)
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL, "\":\" not found.");
            Status = STATUS_STR_ERR;
            break;
        }

        String = String + 2;
        CpuInfo->Architecture = (uint8_t)strtoul(String, NULL, 10);

        if(fgets(ReadLine, MAX_LINE_LENGTH, FileDescriptor) == NULL)
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL, "Read from file failed.");
            Status = STATUS_READ_ERR;
            break;
        }

        if(strncmp(ReadLine, VARIANT_STRING, VARIANT_STRING_LENGTH))
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL,
                          "\"%s\" not found in $s.",
                          VARIANT_STRING,
                          CPUINFO_PATH);
            Status = STATUS_READ_ERR;
            break;
        }

        String = ReadLine + VARIANT_STRING_LENGTH;
        String = strstr(String, ":");
        if(String == NULL)
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL, "\":\" not found.");
            Status = STATUS_STR_ERR;
            break;
        }

        String = String + 2;
        CpuInfo->Variant = (uint8_t)strtoul(String, NULL, 16);

        if(fgets(ReadLine, MAX_LINE_LENGTH, FileDescriptor) == NULL)
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL, "Read from file failed.");
            Status = STATUS_READ_ERR;
            break;
        }

        if(strncmp(ReadLine, PART_STRING, PART_STRING_LENGTH))
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL,
                          "\"%s\" not found in $s.",
                          PART_STRING,
                          CPUINFO_PATH);
            Status = STATUS_READ_ERR;
            break;
        }

        String = ReadLine + MODEL_NAME_STRING_LENGTH;
        String = strstr(String, ":");
        if(String == NULL)
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL, "\":\" not found.");
            Status = STATUS_STR_ERR;
            break;
        }

        String = String + 2;
        CpuInfo->Part = (uint8_t)strtoul(String, NULL, 16);

        if(fgets(ReadLine, MAX_LINE_LENGTH, FileDescriptor) == NULL)
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL, "Read from file failed.");
            Status = STATUS_READ_ERR;
            break;
        }

        if(fgets(ReadLine, MAX_LINE_LENGTH, FileDescriptor) == NULL)
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL, "Read from file failed.");
            Status = STATUS_READ_ERR;
            break;
        }

        if(strncmp(ReadLine, CPU_REVISION_STRING, CPU_REVISION_STRING_LENGTH))
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL,
                          "\"%s\" not found in $s.",
                          CPU_REVISION_STRING,
                          CPUINFO_PATH);
            Status = STATUS_READ_ERR;
            break;
        }

        String = ReadLine + CPU_REVISION_STRING_LENGTH;
        String = strstr(String, ":");
        if(String == NULL)
        {
            WriteDebugLog(DEBUG_LOGGING_ERROR_LEVEL, "\":\" not found.");
            Status = STATUS_STR_ERR;
            break;
        }

        String = String + 2;
        CpuInfo->Revision = (uint8_t)strtoul(String, NULL, 10);
    } while(0);

    if(FileDescriptor != NULL)
    {
        fclose(FileDescriptor);
    }

    return Status;
}
