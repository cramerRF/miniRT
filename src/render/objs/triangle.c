#include "../../../inc/miniRT.h"

//CHECK
int         inter_triangle(void *obj, t_ray *ray, t_td_point **arr)
{
    t_td_point  aux[4];
    t_td_triangle   *tri = ((t_tuple *) obj)->content;
    nType       det, u, v, t;
    
    //max one sol
    aux[0] = sum_vector(tri->a, scalar_product(tri->b, -1));
    aux[1] = sum_vector(tri->c, scalar_product(tri->b, -1));
    aux[2] = cross_product(ray->direction, aux[1]);
    det = dot_product(aux[0], aux[2]);
    if (det == 0)
        return (0);
    aux[3] = sum_vector(ray->origin, scalar_product(tri->b, -1));
    u = dot_product(aux[3], aux[2]) / det;
    if (u < 0 || u > 1)
        return (0);
    aux[2] = cross_product(aux[3], aux[0]);
    v = dot_product(ray->direction, aux[2]) / det;
    if (v < 0 || u + v > 1)
        return (0);
    t = dot_product(aux[1], aux[2]) / det;
    if (t < 0)
        return (0);
    *arr = malloc(sizeof(t_td_point) * 1);
    if (!*arr)
        return (0);
    (*arr)[0] = scalar_product(ray->direction, t);
    (*arr)[0] = sum_vector((*arr)[0], ray->origin);
    return (1);
}

t_td_point  normal_triangle(void *obj, t_ray *ray, t_td_point *point)
{
    (void) ray;
    (void) point;
    t_td_triangle *t = (t_td_triangle *) obj;
    t_td_point normal =  {
    t->a.y * t->b.z - t->a.z * t->b.y, 
    t->a.z * t->b.x - t->a.x * t->b.z, 
    t->a.x * t->b.y - t->a.y * t->b.x 
    };
    //TODO check ray direction
    normal = scalar_product(normal, -1);
    return normal;
}
