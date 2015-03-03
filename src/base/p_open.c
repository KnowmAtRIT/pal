#include <pal.h>

#include <stdio.h>
#include "pal_base.h"
#include "pal_base_private.h"

/**
 *
 * Create a team of processors based on the the total list of processors
 * defined within the device 'dev'.
 *
 * @param dev   Pointer to object containing device information
 *
 * @param start Index of first processor within 'dev' to include in team
 *
 * @param count Total number of processors in team.
 *
 * @return      Returns a reference. Negative value indicates error.
 *
 */
P_STATUS p_open(p_dev_t *dev, int start, int count, p_team_t *team)
{
    if (!dev)
        return ERROR_INVALID;

    team = malloc(sizeof(p_team_t));
    if (!team)
        return ERROR_NO_MEMORY;

    team = ((p_dev_ops_t*)dev->dev_ops)->open(dev, team, start, count);
    if (!team) {
        free(team);
        return OK;
    }

    /* TODO: Rank ranges */

    /* TODO: Need something generic to iterate over lists */
    if (!__pal_global.teams_head) {
        __pal_global.teams_head = __pal_global.teams_tail = team;
    } else {
        __pal_global.teams_tail->next = team;
        __pal_global.teams_tail = team;
    }

    return OK;

}
