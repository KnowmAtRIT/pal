#include "pal_base.h"
#include <stdio.h>
#define N 16
int main(int argc, char *argv[])
{

    // Stack variables
    char *file = "./hello_task.elf";
    char *func = "main";
    int i, all, nargs = 1;
    char *args[nargs];
    char argbuf[20];
    P_STATUS status;
    // References as opaque structures
    p_dev_t dev0;
    p_prog_t prog0;
    p_team_t team0;
    p_mem_t mem[4];

    // Execution setup
    status = p_init(DEMO, 0, &dev0);        // initialize device and team
    status = p_load(&dev0, file, func, 0, &prog0); // load a program from file system
    all = p_query(&dev0, NODES);   // find number of nodes in system
    status = p_open(&dev0, 0, all, &team0);        // create a team

    // Running program
    for (i = 0; i < all; i++) {
        sprintf(argbuf, "%d", i); // string args needed to run main asis
        args[0] = argbuf;
        status = p_run(&prog0, &team0, i, 1, nargs, args, 0);
    }
    p_wait(&team0);    // not needed
    p_close(&team0);   // close team
    p_finalize(&dev0); // finalize memory

    return 0;
}
