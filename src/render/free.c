#include "../../inc/miniRT.h"

void    rt_render_free(void *arg)
{
    t_render    *render;

    render = (t_render *) arg;
    printf("rt_render_free %p\n", render);
    if (render->threads)
    {
        unsigned i = -1;
        while (++i < render->prop_perf.n_threads)
            free(render->threads[i].rays);
        free(render->threads);
    }
    if (render->mlx.img)
        mlx_destroy_image(render->mlx.mlx, render->mlx.img);
    render->mlx.img = NULL;
    //if (render->mlx.win)
    //    mlx_destroy_window(render->mlx.mlx, render->mlx.win);
    render->mlx.win = NULL;
    free(render->name);
    free(render);
}