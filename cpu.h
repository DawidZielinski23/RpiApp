#ifndef _CPU_H
#define _CPU_H

#include"libraries.h"

/* Basing on last table from
 * https://www.raspberrypi.com/documentation/computers/raspberry-pi.html#new-style-revision-codes */

#define PI_REVISION_CODE_LENGTH  7
#define PI_REV_STRING_LENGTH     7
#define PI_RAM_STRING_LENGTH     7
#define PI_MODEL_STRING_LENGTH   8
#define PI_MAN_STRING_LENGTH     10
#define PI_NUMBER_OF_REVISIONS   40
#define MAX_LINE_LENGTH          256

#define CPUINFO_PATH           "/proc/cpuinfo"
#define HARDWARE_STRING        "Hardware"
#define HARDWARE_STRING_LENGTH 8
#define REVISION_STRING        "Revision"
#define REVISION_STRING_LENGTH 8
#define SERIAL_STRING          "Serial"
#define SERIAL_STRING_LENGTH   6
#define BCM_STRING_LENGTH      8

/* Models */
typedef enum PI_MODEL
{
    PI_MODEL_A       = 0,
    PI_MODEL_AP,
    PI_MODEL_B,
    PI_MODEL_BP,
    PI_MODEL_CM1,
    PI_MODEL_CM3,
    PI_MODEL_CM3P,
    PI_MODEL_CM4,
    PI_MODEL_0,
    PI_MODEL_0W,
    PI_MODEL_02W,
    PI_MODEL_2A,
    PI_MODEL_2B,
    PI_MODEL_3A,
    PI_MODEL_3AP,
    PI_MODEL_3B,
    PI_MODEL_3BP,
    PI_MODEL_4B,
    PI_MODEL_400,
    PI_MODEL_UNKNOWN,
    PI_MODEL_COUNT
} PI_MODEL;


/* Revison */
typedef enum PI_REVISION
{
    PI_REV_1_0     = 0,
    PI_REV_1_1,
    PI_REV_1_2,
    PI_REV_1_3,
    PI_REV_1_4,
    PI_REV_1_5,
    PI_REV_UNKNOWN,
    PI_REV_COUNT
} PI_REVISION;

/* RAM */
typedef enum PI_RAM
{
    PI_RAM_512MB    = 0,
    PI_RAM_1GB,
    PI_RAM_2GB,
    PI_RAM_4GB,
    PI_RAM_8GB,
    PI_RAM_UNKNOWN,
    PI_RAM_COUNT
} PI_RAM;

/* Manufacturer */
typedef enum PI_MANUFACTURER
{
    PI_MAN_EMBEST     = 0,
    PI_MAN_EGOMAN,
    PI_MAN_QISDA,
    PI_MAN_SONY_UK,
    PI_MAN_SONY_JAPAN,
    PI_MAN_STADIUM,
    PI_MAN_UNKNOWN,
    PI_MAN_COUNT
} PI_MANUFACTURER;


typedef struct _PI_INFO
{
    char            RevisionCode[PI_REVISION_CODE_LENGTH];
    PI_MODEL        Model;
    PI_REVISION     Revision;
    PI_RAM          Ram;
    PI_MANUFACTURER Manufacturer;
} PI_INFO;

char* GetPiRevisionCode(uint8_t Index);
PI_MODEL GetPiModel(uint8_t Index);
PI_REVISION GetPiRevision(uint8_t Index);
PI_RAM GetPiRam(uint8_t Index);
PI_MANUFACTURER GetPiManufacturer(uint8_t Index);
char* GetPiModelString(uint8_t Index);
char* GetPiRevisionString(uint8_t Index);
char* GetPiRamString(uint8_t Index);
char* GetPiManufacturerString(uint8_t Index);
void GetPiBasicInfo(PI_INFO* PiInfo, char* Bcm, char* Serial);



#endif /* _CPU_H */