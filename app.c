#include "pin.h"
#include "cpu.h"



int main()
{
    PI_INFO PiInfo = {0};
    char Bcm[BCM_STRING_LENGTH] = {'\0'};
    char Serial[SERIAL_VALUE_LENGTH] = {'\0'};

    GetPiBasicInfo(&PiInfo, Bcm, Serial);

    printf("Bcm             %s\n", Bcm);
    printf("Revision        %s\n", PiInfo.RevisionCode);
    printf("Serial          %s\n", Serial);
    printf("Model           %s\n", GetPiModelString(PiInfo.Model));
    printf("Revison         %s\n", GetPiRevisionString(PiInfo.Revision));
    printf("RAM             %s\n", GetPiRamString(PiInfo.Ram));
    printf("Manufacturer    %s\n", GetPiManufacturerString(PiInfo.Manufacturer));

    return 0;
}