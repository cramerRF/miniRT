#include "../../../inc/miniRT.h"

int         inter_sphere(void *obj, t_ray *ray, t_td_point **arr)
{
    t_sphere    *sphere;
    nType       a;
    nType       b;
    nType       c;
    nType       dis;
    t_td_point  aux;
    int         n;

    //Max sols = 2
    *arr = malloc(sizeof(t_td_point) * 2);
    sphere = ((t_tuple *) obj)->content;
    a = dot_product(ray->direction, ray->direction);
    aux = sum_vector(ray->origin, scalar_product(sphere->center, -1));
    b = 2 * dot_product(ray->direction, aux);
    c = dot_product(aux, aux) - sphere->radius * sphere->radius;
    dis = b * b - 4 * a * c;
    if (dis < 0)
        n = 0;
    else if (dis == 0)
    {
        n = 1;
        (*arr)[0] = scalar_product(ray->direction, -b / (2 * a));
        (*arr)[0] = sum_vector((*arr)[0], ray->origin);
    }
    else
    {

        n = 2;
        (*arr)[0] = scalar_product(ray->direction, (-b + sqrt(dis)) / (2 * a));
        (*arr)[0] = sum_vector((*arr)[0], ray->origin);
        (*arr)[1] = scalar_product(ray->direction, (-b - sqrt(dis)) / (2 * a));
        (*arr)[1] = sum_vector((*arr)[1], ray->origin);

    }
    return (n);
}

t_td_point  normal_sphere(void *obj, t_ray *ray, t_td_point *point)
{
    (void) obj;
    (void) ray;
    (void) point;
    return ((t_td_point){0, 0, 0});
}
