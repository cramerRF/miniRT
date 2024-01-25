#include "../../inc/miniRT.h"

nType   absolute(nType k)
{
    if ( k < 0 )
        k *= -1;
    return (k);
}

nType  module(t_td_point v)
{
    return (sqrt(v.x * v.x + v.y * v.y +v.z * v.z));
}

t_td_point  normalize(t_td_point v)
{
    nType   mod;

    mod = module(v);
    if (!mod)
        return (v);
    v.x /= mod;
    v.y /= mod;
    v.z /= mod;
    return (v);
}

t_td_point  cross_product(t_td_point v, t_td_point u)
{
    t_td_point ret;

    ret.x = v.y * u.z - v.z * u.y;
    ret.y = - v.x * u.z + v.z * u.x;
    ret.z = v.x * u.y - v.y * u.x;
    return (ret);
}

t_td_point  scalar_product(t_td_point v, nType k)
{
    v.x *= k;
    v.y *= k;
    v.z *= k;
    return (v);
}

t_td_point sum_vector(t_td_point v, t_td_point u)
{
    v.x += u.x;
    v.y += u.y;
    v.z += u.z;
    return (v);
}

nType dot_product(t_td_point v, t_td_point u)
{
    return (v.x * u.x + v.y * u.y +v.z * u.z);
}

void    print_td_point(char *msg, t_td_point p)
{
    printf("%s: (%0.4f, %0.4f, %0.4f)\n", msg, p.x, p.y, p.z);
}