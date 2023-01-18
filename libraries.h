#ifndef _LIBRARIES_H
#define _LIBRARIES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>
#include <string.h>
#include "..\debug_logging\debug_logging.h"

enum status
{
    STATUS_OK         = 0,
    STATUS_PARAM_ERR,
    STATUS_READ_ERR,
    STATUS_WRITE_ERR,
    STATUS_FILE_ERR,
    STATUS_STR_ERR,
    STATUS_INPUT_ERR,
    STATUS_CMD_ERR
};

#endif /* _LIBRARIES_H*/