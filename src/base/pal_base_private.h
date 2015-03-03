#pragma once

#include <errno.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "../math/tinymt/tinymt32.h"

// TEMPORARY HACK!!
struct p_dev
{
    int property[32];
};

struct p_symbol
{
};

struct p_event
{
};

struct p_atom_u32
{
    uint32_t mutex; // resource mutex
    uint32_t var;   // atomic variable
};

struct p_mutex
{
    uint32_t mutex; // mutex
};

/*
 ***********************************************************************
 * Global system variables (will be replaced with O/S real time
 ***********************************************************************
 */

struct dev_op;
struct dev;
struct rank_range;
struct team;
struct prog;
struct pal_global;

struct rank_range {
    int first;
    int n;
};

struct team {
    struct team *next;
    p_dev_t *dev; // Support only one device per team (at leat for now)
    struct rank_range *ranges;
    size_t ranges_size;
};

struct prog {
    struct prog *next;
    p_dev_t *dev;
    char *name; // Must be '\0' terminated
    char *path; // Must be '\0' terminated
    char *buf;
    size_t buf_size;
};

struct pal_global {
    p_dev_t devs[P_DEV_LAST+1];
    struct team *teams_head;
    struct team *teams_tail;
    struct prog *progs_head;
    struct prog *progs_tail;
#if 0
    struct symbol *symbols_head;
    struct symbol *symbols_tail;
    struct event *events_head;
    struct event *events_tail;
    struct mem *mems_head;
    struct mem *mems_tail;
    struct atom *atoms_head;
    struct atom *atoms_tail;
    struct mutex *mutexes_head;
    struct mutex *mutexes_tail;
#endif
    tinymt32_t random; // PRNG state
};

extern struct pal_global __pal_global;
