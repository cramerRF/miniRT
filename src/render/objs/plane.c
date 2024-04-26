#include "../../../inc/miniRT.h"

int         inter_plane(void *obj, t_ray *ray, t_td_point **arr)
{
    (void) obj;
    (void) ray;
    (void) arr;
    return (0);
}

t_td_point  normal_plane(void *obj, t_ray *ray, t_td_point *point)
{
    (void) obj;
    (void) ray;
    (void) point;
    return ((t_td_point){0, 0, 0});
}