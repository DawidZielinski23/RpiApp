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

    if(Status == STATUS_OK)
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
            printf("Failed to discover CPUs number.\n");
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
    } while(0);

    printf("\n");

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
            printf("Failed to discover CPUs.\n\n");
            break;
        }

        Cpus = malloc(sizeof(CPU_INFO) * DiscoveredCpus);
        if(Cpus == NULL)
        {
            printf("Memory error.\n\n");
            break;
        }

        for(Index = 0; Index < DiscoveredCpus; Index++)
        {
            Status = GetCpuInformation(&Cpus[Index], Index);
            if(Status != STATUS_OK)
            {
                printf("Failed to get CPU %u information.\n\n", Index);
                continue;
            }

            printf("CPU number %u information from %u discovered:\n",
                   Cpus[Index].Number,
                   DiscoveredCpus);
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

enum status PrintPinInfo(uint32_t Number)
{
    enum status Status = STATUS_OK;
    uint8_t PinNumber = 0;
    PIN_INFO Pin = {0, UNKNOWN_MODE, 0};

    do
    {
        if((Number > PINS_COUNT) || (Number == 0))
        {
            printf("Wrong pin number given!");
            Status = STATUS_PARAM_ERR;
            break;
        }

        PinNumber = (uint8_t)Number;

        Status = GetPinInfo(&Pin, PinNumber);
        if(Status != STATUS_OK)
        {
            printf("Failed to get %u Pin infmoration!\n", PinNumber);
        }

        printf("Pin %02u | Mode %10s | Value %u\n",
               Pin.Number,
               GetPinModeString(Pin.Mode),
               Pin.Value);
    } while(0);

    printf("\n");

    return Status;
}

enum status DiscoverAllPins()
{
    enum status Status = STATUS_OK;
    PIN_INFO* Pins = NULL;
    uint8_t Index = 0;

    do
    {
        Pins = malloc(sizeof(PIN_INFO) * PINS_COUNT);
        if(Pins == NULL)
        {
            printf("Error durring discovering pins!\n");
            Status = STATUS_MEM_ERR;
            break;
        }

        for(Index = 0; Index < PINS_COUNT; Index++)
        {
            Status = GetPinInfo(&Pins[Index], Index + 1);
            if(Status == STATUS_OK)
            {
                printf("Pin %02u | Mode %10s | Value %u\n",
                       Pins[Index].Number,
                       GetPinModeString(Pins[Index].Mode),
                       Pins[Index].Value);
            }
            else
            {
                printf("Pin %02u | Mode %10s | Value %s\n",
                       Index + 1,
                       GetPinModeString(UNKNOWN_MODE),
                       "N/A");
            }
        }
    } while(0);

    if(Pins != NULL)
    {
        free(Pins);
    }

    printf("\n");

    return Status;
}

void ShowHelp()
{
    printf("Appliacation usage:\n");
    printf("-pin=X      - Get X pin information\n");
    printf("-gpio_all   - Discover all RPi pins\n");
    printf("-cpu=X      - Show X CPU information\n");
    printf("-all        - Show all CPU information\n");
    printf("-pi_info    - Show RPi basic data\n");
    printf("-debuglog=X - Enable collecting logs and\n"
           "              set log level to X\n");
    printf("-help       - Display help");
    printf("\n");
}

void PrintHeader()
{
    bool HeaderShowed = false;
    uint8_t Index = 0;

    printf("\n");
    for(Index = 0; Index < HEADER_WIDTH; Index++)
    {
        printf("=");
        if((Index == HEADER_WIDTH - 1) && (HeaderShowed == false))
        {
            printf("\n");
            printf(HEADER);
            printf(AUTHOR);
            printf("=");
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
        if((argv == NULL) || (argc == 1))
        {
            printf("No parameters given!\n");
            ErrorOccured = true;
            Status = STATUS_INPUT_ERR;
            break;
        }

        for(Index = 1; Index < argc; Index++)
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
        ShowHelp();
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
            Status = STATUS_MEM_ERR;
            break;
        }

        CommandArray = malloc(sizeof(uint32_t) * COMMANDS_COUNT);
        if(CommandArray == NULL)
        {
            Status = STATUS_MEM_ERR;
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
                    break;
                case SHOW_HELP:
                    ShowHelp();
                    break;
                case GET_PIN_INFO:
                    Status = PrintPinInfo(ValueArray[Index]);
                    break;
                case GET_ALL_PINS_INFO:
                    Status = DiscoverAllPins();
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

int main(uint32_t argc, char** argv)
{
    enum status Status = STATUS_OK;
    bool DebugFileOpen = false;

    do
    {
        PrintHeader();

        Status = ParseArgs(argv, argc);
        if(Status != STATUS_OK)
        {
            break;
        }

        Status = RunCommands();

        DebugFileOpen = IsDebugLogFileOpen();
        if(DebugFileOpen == true)
        {
            CloseDebugFile();
        }

    } while(0);

    return Status;
}