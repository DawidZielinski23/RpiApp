#include "pin.h"
#include "cpu.h"
#include "cmd.h"
#include "libraries.h"

#define HEADER_WIDTH 40
#define HEADER "  Raspberry Pi diagnostic application\n"
#define AUTHOR "        Mady by Dawid Zielinski\n"

enum status PrintPiBasicInfo()
{
    char Serial[SERIAL_VALUE_LENGTH] = {'\0'};
    char Bcm[BCM_STRING_LENGTH] = {'\0'};
    enum status Status = STATUS_OK;
    PI_INFO PiInfo = {0};

    Status = GetPiBasicInfo(&PiInfo, Bcm, Serial);

    if(Status = STATUS_OK)
    {
        printf("Raspberry Pi information:\n");
        printf("Bcm             %s\n", Bcm);
        printf("Revision        %s\n", PiInfo.RevisionCode);
        printf("Serial          %s\n", Serial);
        printf("Model           %s\n", GetPiModelString(PiInfo.Model));
        printf("Revison         %s\n", GetPiRevisionString(PiInfo.Revision));
        printf("RAM             %s\n", GetPiRamString(PiInfo.Ram));
        printf("Manufacturer    %s\n", GetPiManufacturerString(PiInfo.Manufacturer));
    }
    else
    {
        printf("Error: Could not get Raspberry Pi information, status %d\n", Status);
    }
    printf("\n");

    return Status;
}

enum status PrintCpuInfo(uint32_t CpuIndex)
{
    enum status Status = STATUS_OK;
    uint8_t DiscoveredCpus = 0;
    CPU_INFO Cpu = {0};

    do
    {
        Status = DiscoverCpuNumber(&DiscoveredCpus);
        if(Status != STATUS_OK)
        {
            printf("Failed to discover CPUs.\n");
            break;
        }

        if(CpuIndex > DiscoveredCpus - 1)
        {
            printf("There is no CPU with number %d.\n", CpuIndex);
            Status = STATUS_PARAM_ERR;
            break;
        }

        Status = GetCpuInformation(&Cpu, CpuIndex);
        if(Status != STATUS_OK)
        {
            printf("Failed to get CPU %d information.\n", CpuIndex);
            break;
        }

        printf("CPU number %d information:\n", Cpu.Number);
        printf("Name            %s\n", Cpu.Name);
        printf("Implementer     %#X\n", Cpu.Implementer);
        printf("Architecture    %d\n", Cpu.Architecture);
        printf("Variant         %#X\n", Cpu.Variant);
        printf("Part            %#X\n", Cpu.Part);
        printf("Revision        %d\n", Cpu.Revision);
        printf("\n");
    } while(0);

    return Status;
}

enum status PrintAllCpuInfo()
{
    enum status Status = STATUS_OK;
    uint8_t DiscoveredCpus = 0;
    CPU_INFO* Cpus = NULL;
    uint8_t Index = 0;

    do
    {
        Status = DiscoverCpuNumber(&DiscoveredCpus);
        if((Status != STATUS_OK) || (DiscoveredCpus == 0))
        {
            printf("Failed to discover CPUs.\n");
            break;
        }

        Cpus = malloc(sizeof(CPU_INFO) * DiscoveredCpus);
        if(Cpus == NULL)
        {
            printf("Memory error.\n");
            break;
        }

        for(Index = 0; Index < DiscoveredCpus; Index++)
        {
            Status = GetCpuInformation(&Cpus[Index], Index);
            if(Status != STATUS_OK)
            {
                printf("Failed to get CPU %d information.\n", Index);
            }

            printf("CPU number %d information from %d discovered:\n",
                   Cpus[Index].Number,
                   DiscoverCpuNumber);
            printf("Name            %s\n", Cpus[Index].Name);
            printf("Implementer     %#X\n", Cpus[Index].Implementer);
            printf("Architecture    %d\n", Cpus[Index].Architecture);
            printf("Variant         %#X\n", Cpus[Index].Variant);
            printf("Part            %#X\n", Cpus[Index].Part);
            printf("Revision        %d\n", Cpus[Index].Revision);
            printf("\n");
        }
    } while(0);

    if(Cpus != NULL)
    {
        free(Cpus);
    }

    return Status;
}

void PrintHeader()
{
    bool HeaderShowed = false;
    uint8_t Index = 0;

    printf("\n");
    for(Index = 0; Index < HEADER_WIDTH; Index++)
    {
        printf("=");
        if((Index == HEADER_WIDTH) && (HeaderShowed == false))
        {
            printf("\n");
            printf(HEADER);
            printf(AUTHOR);
            Index = 0;
            HeaderShowed = true;
        }
    }
    printf("\n\n");
}

enum status ParseArgs(char** argv, uint32_t argc)
{
    enum status Status = STATUS_OK;
    bool ErrorOccured = false;
    bool CommandFound = false;
    uint32_t Index = 0;

    do
    {
        if((argv == NULL) || (argc == 0))
        {
            printf("No parameters given!\n");
            ErrorOccured = true;
            Status = STATUS_INPUT_ERR;
            break;
        }

        for(Index = 0; Index < argc; Index++)
        {
            CommandFound = CheckCommand(argv[Index]);
            if(CommandFound == false)
            {
                Status = STATUS_CMD_ERR;
                ErrorOccured = true;
                break;
            }
        }

        if(Status != STATUS_OK)
        {
            break;
        }
    } while(0);

    if(ErrorOccured == true)
    {
        //ShowHelp();
    }

    return Status;
}

enum status RunCommands()
{
    enum status Status = STATUS_OK;
    uint32_t* ValueArray = NULL;
    bool* CommandArray = NULL;
    uint32_t Index = 0;

    do
    {
        ValueArray = malloc(sizeof(uint32_t) * COMMANDS_COUNT);
        if(ValueArray == NULL)
        {
            Status = STATUS_NO_MEMORY;
            break;
        }

        CommandArray = malloc(sizeof(uint32_t) * COMMANDS_COUNT);
        if(CommandArray == NULL)
        {
            Status = STATUS_NO_MEMORY;
            break;
        }

        Status = CopyValueArray(ValueArray, COMMANDS_COUNT);
        if(Status != STATUS_OK)
        {
            break;
        }

        Status = CopyCommandArray(CommandArray, COMMANDS_COUNT);
        if(Status != STATUS_OK)
        {
            break;
        }

        for(Index = 0; Index < COMMANDS_COUNT; Index++)
        {
            if(CommandArray[Index] == true)
            {
                switch(Index)
                {
                case SET_DEBUGLOG:
                    OpenDebugFile();
                    SetGlobalDebugLevel(ValueArray[Index]);
                case SHOW_HELP:
                    //ShowHelp();
                    break;
                case GET_PIN_INFO:
                    //Status = PrintPinInfo(ValueArray[Index]);
                    break;
                case GET_ALL_PINS_INFO:
                    //Status = DiscoverAllPins();
                    break;
                case GET_CPU_INFO:
                    Status = PrintCpuInfo(ValueArray[Index]);
                    break;
                case GET_ALL_CPU_INFO:
                    Status = PrintAllCpuInfo();
                    break;
                case GET_PI_INFO:
                    Status = PrintPiBasicInfo();
                    break;
                }

                if(Status != STATUS_OK)
                {
                    break;
                }
            }
        }
    } while(0);
    
    if(ValueArray != NULL)
    {
        free(ValueArray);
    }

    if(CommandArray != NULL)
    {
        free(CommandArray);
    }

    return Status;
}

int main(char** argv, uint32_t argc)
{
    enum status Status = STATUS_OK;

    do
    {
        PrintHeader();

        Status = ParseArgs(argv, argc);
        if(Status != STATUS_OK)
        {
            break;
        }

        Status = RunCommands();

    } while(0);

    return Status;
}