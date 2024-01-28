#include "../../inc/miniRT.h"

void    remove_from_lst(t_list **lst, void *content, void (*del)(void *))
{
    t_list  *tmp;
    t_list  *prev;

    tmp = *lst;
    prev = NULL;
    while (tmp)
    {
        if (tmp->content == content)
        {
            if (prev)
                prev->next = tmp->next;
            else
                *lst = tmp->next;
            del(tmp->content);
            free(tmp);
            return ;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}

int rt_close_mlx(t_render *render)
{
    t_rt *rt;

    rt = render->rt;
        pthread_mutex_lock(&(rt->mutex));
    remove_from_lst(&(rt->renders), render, rt_render_free);
    pthread_mutex_unlock(&(rt->mutex));
    return 0;
}

void    update_render(void*arg)
{
    t_render *rend;

    rend = (t_render *) arg;
    if (rend->end)
        rt_close_mlx(rend);
    else
        mlx_put_image_to_window(rend->mlx.mlx, rend->mlx.win, rend->mlx.img, 0 ,0);
}

int rt_loop(t_rt *rt)
{
    pthread_mutex_lock(&rt->mutex);
    rt->updating = 1;
    pthread_mutex_unlock(&rt->mutex);
    sleep(10);
    pthread_mutex_lock(&rt->mutex);
    ft_lstiter(rt->renders, update_render);
    rt->updating = 0;
    pthread_mutex_unlock(&rt->mutex);
    return (0);
}

int	fdf_enable_hooks(int keycode, t_render *render)
{
	printf("keycode -> %d\n", keycode);
    render++;
	return (1);
}

int rt_init_mlx(t_rt *rt, t_render *render)
{
    while (1)
    {
        pthread_mutex_lock(&rt->mutex);
        if (rt->updating)
            break ;
        pthread_mutex_unlock(&rt->mutex);
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
    mlx_put_image_to_window(render->mlx.mlx, render->mlx.win, render->mlx.img, 0 ,0);
    mlx_hook(render->mlx.win, 2, 1L << 0, fdf_enable_hooks, render);
	mlx_hook(render->mlx.win, 17, 1L << 0, rt_close_mlx, render);
    pthread_mutex_unlock(&rt->mutex);
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
    i =  -1;
    while (++i < render->prop_perf.n_threads)
    {
        printf("thread %d, start %d, end %d, rays %p\n", \
        thread[i].id, thread[i].start, thread[i].end, thread[i].rays);
    }
    render->threads = thread;
    return (0);
}

enum e_parameters {
    RIGHT = 0,
    UP,
    D_R,
    D_U,
    ORIGIN,
    PARA_N
};

void    calculate_parameters(t_render *rend, t_td_point para[PARA_N])
{
    nType   focal_len, viewport_h, viewport_w, theta;
    t_td_point  viewport_r, viewport_u;

    focal_len = 1;
    
    //Scalars
    theta = rend->cam.fov / (2.0 * M_PI);
    viewport_w = 2 * tan(theta / 2) * focal_len;
    viewport_h = viewport_w * (nType) rend->prop_img.pixel_height / (nType)rend->prop_img.pixel_witdh;
    printf("theta %0.4f\n", theta);
    printf("viewport_h %0.4f\n", viewport_h);
    printf("viewport_w %0.4f\n", viewport_w);

    //Axis cam
    para[RIGHT] = cross_product(rend->cam.normal, (t_td_point) {0, 0, 1});
    if (dot_product(para[RIGHT], para[RIGHT]) < 0.01)
        para[RIGHT] = (t_td_point) {1, 0, 0};
    else
        para[RIGHT] = normalize(para[RIGHT]);
    para[UP] = scalar_product(normalize(cross_product(rend->cam.normal, para[RIGHT])), -1);
    print_td_point("NORMAL", rend->cam.normal);
    print_td_point("RIGHT", para[RIGHT]);
    print_td_point("UP", para[UP]);

    //Deltas    
    viewport_r = scalar_product(para[RIGHT], viewport_w);
    viewport_u = scalar_product(para[UP], viewport_h);
    para[D_R] = scalar_product(viewport_r, 1.0 / rend->prop_img.pixel_witdh);
    para[D_U] = scalar_product(viewport_u, 1.0 / rend->prop_img.pixel_height);
    print_td_point("viewport_u", viewport_u);
    print_td_point("viewport_r", viewport_r);
    print_td_point("D_R", para[D_R]);
    print_td_point("D_U", para[D_U]);

    //Upper left pixel
    para[ORIGIN] = sum_vector(rend->cam.vertex, scalar_product(rend->cam.normal, focal_len));
    print_td_point("O_1", para[ORIGIN]);
    para[ORIGIN] = sum_vector(para[ORIGIN], scalar_product(viewport_r, -1.0 / 2.0));
    print_td_point("O_2", para[ORIGIN]);
    para[ORIGIN] = sum_vector(para[ORIGIN], scalar_product(viewport_u, 1.0 / 2.0));
    print_td_point("O_3", para[ORIGIN]);
    para[ORIGIN] = sum_vector(para[ORIGIN], scalar_product(sum_vector(para[D_R], para[D_U]), 1 / 2));

    print_td_point("ORIGINul", para[ORIGIN]);
    print_td_point("ORIGINur", sum_vector(para[ORIGIN], scalar_product(para[D_R], rend->prop_img.pixel_witdh)));
    print_td_point("ORIGINdl", sum_vector(para[ORIGIN], scalar_product(para[D_U], - (nType) rend->prop_img.pixel_height)));
    print_td_point("ORIGINdr", para[ORIGIN]);
}

void index_to_pixel(int *x, int *y, int j, t_render *rend)
{
    *x = j % rend->prop_img.pixel_witdh;
    *y = j / rend->prop_img.pixel_witdh;
}

void print_vector(char *msg,  t_td_point ori, t_td_point dir)
{
    printf("%s: Vector((%0.4f, %0.4f, %0.4f),(%0.4f, %0.4f, %0.4f))\n", msg, ori.x, ori.y, ori.z, dir.x, dir.y, dir.z);
}

void compute_rays(t_render *rend)
{
    unsigned int i;
    int j, x, y;
    int index;
    t_td_point  para[PARA_N];

    calculate_parameters(rend, para);
    i = -1;
    index = -1;
    while (++i < rend->prop_perf.n_threads)
    {
        j = rend->threads[i].start - 1;
        while (++j < rend->threads[i].end)
        {
            index_to_pixel(&x, &y, ++index, rend);
            ((t_ray *) (rend->threads[i].rays + j - rend->threads[i].start))->origin = sum_vector(sum_vector(para[ORIGIN], scalar_product(para[D_R], x)), scalar_product(para[D_U], -y));
            ((t_ray *) (rend->threads[i].rays + j - rend->threads[i].start))->direction = normalize(sum_vector(((t_ray *) (rend->threads[i].rays + j - rend->threads[i].start))->origin, scalar_product(rend->cam.vertex, -1)));
            
            if (j == rend->threads[i].start || j == rend->threads[i].end - 1)
                print_vector("aux", ((t_ray *) (rend->threads[i].rays + j - rend->threads[i].start))->origin, sum_vector(((t_ray *) (rend->threads[i].rays + j - rend->threads[i].start))->origin, ((t_ray *) (rend->threads[i].rays + j - rend->threads[i].start))->direction));
        }
    }
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
    compute_rays(nuw);
    //compute_image(nuw);nuw->end = 0;
    //mlx_loop(nuw->mlx.mlx);
    return(0);
}
