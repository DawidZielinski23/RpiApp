#include "pin.h"
#include "cpu.h"

void PrintPiBasicInfo()
{
    char Serial[SERIAL_VALUE_LENGTH] = {'\0'};
    char Bcm[BCM_STRING_LENGTH] = {'\0'};
    enum status Status = STATUS_OK;
    PI_INFO PiInfo = {0};

    Status = GetPiBasicInfo(&PiInfo, Bcm, Serial);

    if(Status = STATUS_OK)
    {
        printf("\nRaspberry Pi information:\n")
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

int main(char** argv, uint32_t argc)
{
    

    return 0;
}