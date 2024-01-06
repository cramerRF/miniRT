#include "../../inc/miniRT.h"

void    rt_render_free(void *arg)
{
    t_render    *render;

    render = (t_render *) arg;
    printf("rt_render_free %p\n", render);
    free(render->name);
    free(render);
}