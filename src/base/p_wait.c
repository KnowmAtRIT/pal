#include <pal.h>

/**
 *
 * Wait for all processes in team to finish.
 *
 * @param team  Pointer to object containing information about team.
 *
 * @return      Returns 0 if successful.
 *
 */
#include <stdio.h>
#include "pal_base.h"
#include "pal_base_private.h"

int p_wait(p_team_t *team)
{
    printf("Running p_wait\n");

    if (!team)
        return -EINVAL;

    return ((p_dev_ops_t*)team->dev->dev_ops)->wait(team->dev, team);
}
