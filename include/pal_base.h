#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

/*
 ***********************************************************************
 * STATUS TYPE
 ***********************************************************************
 */

typedef enum{
  OK,
  ERROR_IO,
  ERROR_NO_MEMORY,
  ERROR_INVALID,
  ERROR_NO_SYSTEM,
  ERROR_NAME_TOO_LONG,
  
} P_STATUS;

/*
 ***********************************************************************
 * DEVICE TYPE
 ***********************************************************************
 */

typedef enum{
  EPIPHANY = 1,
  GRID = 2,
  SMP = 3,
  FPGA = 4,
  GPU = 5,
  DEMO = 6
} P_DEV_TYPE;

#define P_DEV_FIRST EPIPHANY
#define P_DEV_LAST DEMO

/*
 ***********************************************************************
 * FLAGS
 ***********************************************************************
 */

#if 0

#define P_FLAG_DEFAULT 0
#define P_FLAG_ASYNC 0x01
#define P_FLAG_METAL 0x02
#define P_FLAG_LINUX 0x04
#define P_FLAG_SOURCE 0x08
#define P_FLAG_BIN 0x10

#else

typedef enum{
  DEFAULT = 0,
  ASYNC = 0x01,
  METAL = 0x02,
  LINUX = 0x04,
  SOURCE = 0x08,
  BIN = 0x10
} P_FLAG;

#endif
/*
 ***********************************************************************
 *DEVICE QUERY PARAMETERS
 ***********************************************************************
 */

typedef enum{
  TYPE = 0,
  NODES = 1,
  TOPOLOGY = 2,
  ROWS = 3,
  COLS = 4,
  PLANES = 5,
  CHIPROWS = 6,
  CHIPCOLS = 7,
  SIMD = 8,
  MEMSIZE = 9,
  MEMBASE = 10,
  VER = 11,
  MEMARCH = 12,
  WHOAMI = 13
} P_PROP;

/*
 ***********************************************************************
 * OPAQUE OBJECT TYPES
 ***********************************************************************
 */

typedef void * p_ref_t;
typedef p_ref_t p_dev_table_t;

typedef p_ref_t p_team_table_t;
typedef p_ref_t p_program_table_t;
typedef p_ref_t p_mem_table_t;
typedef p_ref_t p_prog_t;

typedef struct{
    void * dev_ops;
} p_dev_t;

typedef struct{
    p_dev_t * dev;
} p_team_t;

typedef struct{
    P_STATUS (*init)(p_dev_t*,int);                //initialize function
    void (*fini)(p_dev_t*);                        //finalize function
    p_team_t* (*open)(p_dev_t*,p_team_t*,int,int); //open function
    int (*query)(p_dev_t*,P_PROP);                 //query function
    P_STATUS (*run)(p_dev_t*,p_team_t*,p_prog_t*,int,int,int,char**,int);
    P_STATUS (*wait)(p_dev_t*,p_team_t*);
} p_dev_ops_t;


typedef p_ref_t p_symbol_t;
typedef p_ref_t p_event_t;
typedef p_ref_t p_mem_t;
typedef p_ref_t p_memptr_t;
typedef p_ref_t p_atom_t;
typedef p_ref_t p_mutex_t;
typedef p_ref_t p_mutex_attr_t;

/*
 ***********************************************************************
 * PROGRAM FLOW
 ***********************************************************************
 */

/*Initialize device run time*/
P_STATUS p_init(P_DEV_TYPE type, int flags, p_dev_t *dev);

/*Finalize device run time*/
P_STATUS p_finalize(p_dev_t *dev);

/*Open a team of processors*/
P_STATUS p_open(p_dev_t *dev, int start, int count, p_team_t *team);

/*Add team members*/
P_STATUS p_append(p_team_t *team, int start, int count);

/*Remove team members*/
P_STATUS p_remove(p_team_t *team, int start, int count);

/*Close a team of processors*/
P_STATUS p_close(p_team_t *team);

/* Loads a program from the file system into memory */
P_STATUS p_load(p_dev_t *dev, char *file, char *function, int flags, p_prog_t *program);

/* Run a program on N processors */
P_STATUS p_run(p_prog_t *prog, p_team_t *team, int start, int count, int nargs,
              char *args[], int flags);

/*Execution barrier*/
P_STATUS p_barrier(p_team_t *team);

/* Wait for a team */
P_STATUS p_wait(p_team_t *team);

/*Create a local memory object*/
P_STATUS p_malloc(p_team_t *team, size_t size, p_mem_t *mem);

/*Create a remote memory object*/
P_STATUS p_rmalloc(p_team_t *team, int pid, size_t size, p_mem_t *mem);

/*Free allocated memory */
P_STATUS p_free(p_mem_t *mem);

/*Memory fence*/
P_STATUS p_fence(p_mem_t *mem);

/*Flushes the read and write paths to a specific memory object*/
P_STATUS p_flush(p_mem_t *mem);

/*Query a property of a device*/
/*need it for mem, team, prog as well?*/
int p_query(p_dev_t *dev, P_PROP property);

/*
 ***********************************************************************
 * MOVING BITS AROUND
 ***********************************************************************
 */

/*Writes to a global memory address from a local address*/
ssize_t p_write(p_mem_t mem, const void *src, size_t nb, int flags);

/*Reads from a global memory address */
ssize_t p_read(p_mem_t mem, void *dst, off_t offset, size_t nb, int flags);

/*Broadcasts an array based to a list of destination pointers*/
ssize_t p_broadcast(p_mem_t *mlist[], int mcount, void *src, size_t nb,
                    int flags);

/*Scatters data from a local array to a list of remote memory objects*/
ssize_t p_scatter(p_mem_t *mlist[], int mcount, void *suf, size_t scount,
                  int disp[], int flags);

/*Scatters data from a local array to a list of remote memory objects*/
ssize_t p_gather(p_mem_t *mlist[], int mcount, void *dbuf, size_t dcount,
                 int disp[], int flags);

/*Specialized low level shared memory memcpy interface (non-blocking)*/
ssize_t p_memcpy(void *dst, void *src, size_t nb, int flags);

/*
 ***********************************************************************
 * SYNCHRONIZATION PRIMITIVES (SHARED MEMORY)
 ***********************************************************************
 */

/*mutex (posix and gcc builtin) inspired), same arguments*/
int p_mutex_init(p_mutex_t *mp);

/*Lock a mutex (try until fail)*/
int p_mutex_lock(p_mutex_t *mp);

/*Try locking a mutex once*/
int p_mutex_trylock(p_mutex_t *mp);

/*Unlock a mutex*/
int p_mutex_unlock(p_mutex_t *mp);

/*Destroy a mutex*/
int p_mutex_destroy(p_mutex_t *mp);

/*atomic fetch and add*/
int p_atomic_add_u32(p_atom_t atom, uint32_t n);

/*atomic fetch and subtract*/
int p_atomic_sub_u32(p_atom_t atom, uint32_t n);

/*atomic fetch and logical 'and'*/
int p_atomic_and_u32(p_atom_t atom, uint32_t n);

/*atomic fetch and logical 'xor'*/
int p_atomic_xor_u32(p_atom_t atom, uint32_t n);

/*atomic fetch and logical 'or'*/
int p_atomic_or_u32(p_atom_t atom, uint32_t n);

/*atomic fetch and logical 'nand'*/
int p_atomic_nand_u32(p_atom_t atom, uint32_t n);

/*atomic swap*/
int p_atomic_swap_u32(p_atom_t atom, uint32_t *input);

/*atomic compare and swap*/
int p_atomic_compswap_u32(p_atom_t atom, uint32_t *input, uint32_t expected);

/** @todo Add description */
int p_getaddr(p_mem_t mem);
/** @todo Add description */
int p_getsymbol(p_prog_t prog, char *name, p_symbol_t symbol);


/*
 ***********************************************************************
 * Error handling
 ***********************************************************************
 */
int p_get_err(p_ref_t ref);
