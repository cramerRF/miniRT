#include "../../../inc/miniRT.h"

int         inter_plane(void *obj, t_ray *ray, t_td_point **arr)
{
    t_plane    *plane;
    nType       dividendo;

    //Max sols = 1
    plane = ((t_tuple *) obj)->content;
    dividendo = dot_product(plane->normal, ray->direction);
    if (dividendo == 0)
        return (0);
    *arr = malloc(sizeof(t_td_point) * 1);
    if (!*arr)
        return (0);
    (*arr)[0] = scalar_product(ray->direction, dot_product(plane->normal, sum_vector(plane->center, scalar_product(ray->origin, -1))) / dividendo);
    (*arr)[0] = sum_vector((*arr)[0], ray->origin);
    return (1);
}

t_td_point  normal_plane(void *obj, t_ray *ray, t_td_point *point)
{
    (void) obj;
    (void) ray;
    (void) point;
    return ((t_td_point){0, 0, 0});
}