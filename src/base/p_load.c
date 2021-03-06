#include <pal.h>

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "pal_base.h"
#include "pal_base_private.h"

/**
 *
 * Loads a program from a file into an object in memory and prepares the program
 * for execution.
 *
 * @param dev       Pointer to object containing device information
 * @param file      File name of executable to load.
 * @param function  Name of function within 'prog' to run
 * @param flags     Optional flags
 *
 * @return          Returns a reference. Negative value indicates error.
 *
 */
P_STATUS p_load(p_dev_t *dev, char *file, char *function, int flags, p_prog_t *program)
{
    size_t len;

    if (!dev)
        return ERROR_INVALID;

    program = malloc(sizeof(p_prog_t));

    if(!program) {
        perror("malloc");
        return ERROR_NO_MEMORY;
    }
    if(strnlen(file, 4096) == 4096) {
        return ERROR_NAME_TOO_LONG;
    }

    program->name = strndup(file, len);
    if(!program->name) {
        perror("strndup");
        return ERROR_NO_MEMORY;
    }
    return OK;

    // TODO: Load into memory etc.
    // TODO: Add to global prog table. We're leaking memory here people.
}
