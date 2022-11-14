#include "pin.h"
#include "cpu.h"
#include "cmd.h"

void PrintPiBasicInfo()
{
    char Serial[SERIAL_VALUE_LENGTH] = {'\0'};
    char Bcm[BCM_STRING_LENGTH] = {'\0'};
    enum status Status = STATUS_OK;
    PI_INFO PiInfo = {0};

    Status = GetPiBasicInfo(&PiInfo, Bcm, Serial);

    if(Status = STATUS_OK)
    {
        printf("\nRaspberry Pi information:\n");
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
        printf("\nError: Could not get Raspberry Pi information, status %d\n", Status);
    }
    printf("\n");
}

void PrintCpuInfo(uint8_t CpuIndex)
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
            break;
        }

        Status = GetCpuInformation(&Cpu, CpuIndex);
        if(Status != STATUS_OK)
        {
            printf("Failed to get CPU %d information.\n", CpuIndex);
            break;
        }

        printf("\nCPU number %d information:\n", Cpu.Number);
        printf("Name            %s\n", Cpu.Name);
        printf("Implementer     %#X\n", Cpu.Implementer);
        printf("Architecture    %d\n", Cpu.Architecture);
        printf("Variant         %#X\n", Cpu.Variant);
        printf("Part            %#X\n", Cpu.Part);
        printf("Revision        %d\n", Cpu.Revision);
        printf("\n");
    } while(0);
}

void PrintfAllCpuInfo()
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

            printf("\nCPU number %d information from %d discovered:\n",
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
}

int main(char** argv, uint32_t argc)
{


    return 0;
}