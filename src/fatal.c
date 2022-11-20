#include "fatal.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void fatal(const char *description) {
    fprintf(
        stderr,
        "%s: %s: %s\n",
        PROGRAM_NAME,
        description,
        strerror(errno)
    );
    exit(EXIT_FAILURE);
}
