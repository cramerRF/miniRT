#include "../../inc/miniRT.h"

int rt_init_mlx(t_rt *rt, t_render *render)
{
    if (!rt->mlx)
    {
        rt->mlx = mlx_init();
        if (!rt->mlx)
            return (printf("Error: mlx_init\n"), 1);
    }
    render->mlx.mlx = rt->mlx;
    render->mlx.win = mlx_new_window(rt->mlx, render->prop_img.pixel_witdh, render->prop_img.pixel_height, render->name);
    if (!render->mlx.win)
        return (printf("Error: mlx_new_window\n"), 1);
    render->mlx.img = mlx_new_image(rt->mlx, render->prop_img.pixel_witdh, render->prop_img.pixel_height);
    if (!render->mlx.img)
        return (free(render->mlx.win) ,printf("Error: mlx_new_image\n"), 1);
    render->mlx.addr = mlx_get_data_addr(render->mlx.img, &render->mlx.bits_per_pixel, &render->mlx.line_length, &render->mlx.endian);
    if (!render->mlx.addr)
        return (free(render->mlx.win), free(render->mlx.img),printf("Error: mlx_get_data_addr\n"), 1);
    return (0);
}

int malloc_thread_render(t_render *render, t_rt *rt)
{
    t_thread_render *thread;
    unsigned i;
    int rays_n;

    rays_n = render->prop_img.pixel_witdh * render->prop_img.pixel_height / render->prop_perf.n_threads;
    thread = malloc(sizeof(t_thread_render) * render->prop_perf.n_threads);
    if (!thread)
        return (printf("Error: malloc_thread_render\n"), 1);
    i = -1;
    while (++i < render->prop_perf.n_threads)
    {
        thread[i].rt = rt;
        thread[i].render = render;
        thread[i].id = i;
        if (i == render->prop_perf.n_threads - 1)
        {
            thread[i].rays = malloc(sizeof(t_ray) * (rays_n + render->prop_img.pixel_witdh * render->prop_img.pixel_height % render->prop_perf.n_threads));
            thread[i].end = render->prop_img.pixel_witdh * render->prop_img.pixel_height;
            thread[i].start = i * rays_n;
        }
        else
        {
            thread[i].rays = malloc(sizeof(t_ray) * rays_n);
            thread[i].end = (i + 1) * rays_n;
            thread[i].start = i * rays_n;
        }
        if (!thread[i].rays)
        {
            while (--i + 1 > 0)
                free(thread[i].rays);
            free(thread);
            return (printf("Error: malloc_thread_render rays\n"), 2);
        }
    }
    render->threads = thread;
    return (0);
}

int    rt_render_add(t_rt *rt)
{
    t_render    *nuw;

    if (render_get_options(rt, &nuw))
        return (printf("Error: getting render options\n"), 1);
    copy_scene_to_render(rt);
    if (rt_init_mlx(rt, nuw))
        return (rt_render_free(nuw), 2);
    if (malloc_thread_render(nuw, rt))
        return (rt_render_free(nuw), 3)  ;
    print_render(nuw);
    ft_lstiter(rt->lights_render, print_objs);
    ft_lstiter(rt->objs_render, print_objs);
    ft_lstadd_back(&rt->renders, ft_lstnew(nuw));
    
    //compute_rays(nuw);
    //compute_image(nuw);
    //update_image(nuw);
    return(0);
}