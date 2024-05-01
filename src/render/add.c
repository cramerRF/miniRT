#include "../../inc/miniRT.h"

void index_to_pixel(int *x, int *y, int j, t_render *rend)
{
    *x = j % rend->prop_img.pixel_witdh;
    *y = j / rend->prop_img.pixel_witdh;
}

void    rt_put_pixel(t_render *rend, int j, int color)
{
    char    *dst;
    unsigned     x;
    unsigned     y;

    index_to_pixel((int *) &x, (int *) &y, j, rend);
    if (x >= rend->prop_img.pixel_witdh || y >= rend->prop_img.pixel_height)
        return ;
    dst = rend->mlx.addr + (y * rend->mlx.line_length + x * (rend->mlx.bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

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

int rt_cross_mlx(t_render *render)
{
    t_rt *rt;

    rt = render->rt;
    pthread_mutex_lock(&(rt->mutex));
    // || render->status == RENDERING || render->status == RENDERED)
    if (render->status == DISPLAYED)
        render->status = END;
    pthread_mutex_unlock(&(rt->mutex));
    return 0;   
}

void    update_render(void *arg)
{
    t_render *rend;
    t_rt     *rt;

    rend = (t_render *) arg;
    rt = rend->rt;
    pthread_mutex_lock(&rt->mutex);
    if (rend->status == INIT)
    {
        rt_init_mlx(rend->rt, rend);
        rend->status = RENDERING;
    }
    else if (rend->status == RENDERED)
    {
        mlx_put_image_to_window(rend->mlx.mlx, rend->mlx.win, rend->mlx.img, 0, 0);
        rend->status = DISPLAYED;
    }
    else if (rend->status == END)
    {
        //remove_from_lst(&(rt->renders), rend, rt_render_free);
    }
    pthread_mutex_unlock(&rt->mutex);
}

int rt_loop(t_rt *rt)
{
    t_list  *tmp;
    t_list  *prev;
    int     status;

    ft_lstiter(rt->renders, update_render);
    tmp = rt->renders;
    prev = NULL;
    while (tmp)
    {
        pthread_mutex_lock(&rt->mutex);
        status = ((t_render *) tmp->content)->status;
        pthread_mutex_unlock(&rt->mutex);

        if (status == END)
        {
            if (prev)
                prev->next = tmp->next;
            else
                rt->renders = tmp->next;
            pthread_mutex_lock(&rt->mutex);
            rt_render_free(tmp->content);
            free(tmp);
            pthread_mutex_unlock(&rt->mutex);
            break ;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    pthread_mutex_lock(&rt->mutex);
    if (rt->end)
    {
        pthread_join(rt->menu_thread, NULL);
        exit(0);
        pthread_mutex_unlock(&rt->mutex);
        pthread_mutex_destroy(&rt->mutex);
        free(rt);
        system("leaks -q miniRT");
    }
    pthread_mutex_unlock(&rt->mutex);
    return (0);
}

int	fdf_enable_hooks(int keycode, t_render *render)
{
	printf("keycode -> %d %p\n", keycode, render);
    if (keycode == KEY_Q || keycode == KEY_ESC)
    {

        rt_cross_mlx(render);
    }
	return (1);
}

int rt_init_mlx(t_rt *rt, t_render *render)
{
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
	mlx_hook(render->mlx.win, 17, 1L << 0, rt_cross_mlx, render);
    return (0);
}

int malloc_thread_render(t_render *render, t_rt *rt)
{
    t_thread_render *thread;
    unsigned i;
    int rays_n;

    rays_n = render->prop_img.pixel_witdh * render->prop_img.pixel_height / render->prop_perf.n_threads;
    printf("rays_n %d\n", rays_n);
    thread = malloc(sizeof(t_thread_render) * render->prop_perf.n_threads);
    if (!thread)
        return (printf("Error: malloc_thread_render\n"), 1);
    ft_bzero(thread, sizeof(t_thread_render) * render->prop_perf.n_threads);
    i = -1;
    while (++i < render->prop_perf.n_threads)
    {
        thread[i].rt = rt;
        thread[i].render = render;
        thread[i].id = i;
        if (i == render->prop_perf.n_threads - 1)
        {
            thread[i].rays = malloc(sizeof(t_ray) * (rays_n + ((render->prop_img.pixel_witdh * render->prop_img.pixel_height) % render->prop_perf.n_threads)));
            ft_bzero(thread[i].rays, sizeof(t_ray) * (rays_n + ((render->prop_img.pixel_witdh * render->prop_img.pixel_height) % render->prop_perf.n_threads)));
            thread[i].end = render->prop_img.pixel_witdh * render->prop_img.pixel_height;
            thread[i].start = i * rays_n;
        }
        else
        {
            thread[i].rays = malloc(sizeof(t_ray) * rays_n);
            ft_bzero(thread[i].rays, sizeof(t_ray) * rays_n);
            thread[i].end = (i + 1) * rays_n;
            thread[i].start = i * rays_n;
        }
        if (!thread[i].rays)
        {
            while (--i + 1 > 0)
                free(thread[i].rays);
            free(thread);
            exit(18);
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

void print_vector(char *msg,  t_td_point ori, t_td_point dir)
{
    printf("%s: Vector((%0.4f, %0.4f, %0.4f),(%0.4f, %0.4f, %0.4f))\n", msg, ori.x, ori.y, ori.z, dir.x, dir.y, dir.z);
}


void compute_rays_copy(t_render *rend)
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
        //printf("COSO %p\n", rend->threads[i].rays);
        j = rend->threads[i].start - 1;
        while (++j < rend->threads[i].end)
        {
            index_to_pixel(&x, &y, ++index, rend);
            (((t_ray *) rend->threads[i].rays) + j - rend->threads[i].start)->origin = sum_vector(sum_vector(para[ORIGIN], scalar_product(para[D_R], x)), scalar_product(para[D_U], -y));
            (((t_ray *) rend->threads[i].rays) + j - rend->threads[i].start)->direction = normalize(sum_vector(((t_ray *) (((t_ray *) rend->threads[i].rays) + j - rend->threads[i].start))->origin, scalar_product(rend->cam.vertex, -1)));
            //printf("ray %d, %d, %d\n", j, x, y);
            //printf("ray %p ray->origin %0.4f, %0.4f, %0.4f\n", ((t_ray *) (rend->threads[i].rays + j - rend->threads[i].start))->origin.x, ((t_ray *) (rend->threads[i].rays + j - rend->threads[i].start))->origin.y, ((t_ray *) (rend->threads[i].rays + j - rend->threads[i].start))->origin.z);
            //printf("ray->direction %0.4f, %0.4f, %0.4f\n", ((t_ray *) (rend->threads[i].rays + j - rend->threads[i].start))->direction.x, ((t_ray *) (rend->threads[i].rays + j - rend->threads[i].start))->direction.y, ((t_ray *) (rend->threads[i].rays + j - rend->threads[i].start))->direction.z);
            if (j == rend->threads[i].start || j == rend->threads[i].end - 1)
                print_vector("aux", (((t_ray *) rend->threads[i].rays) + j - rend->threads[i].start)->origin, sum_vector((((t_ray *) rend->threads[i].rays) + j - rend->threads[i].start)->origin, (((t_ray *) rend->threads[i].rays) + j - rend->threads[i].start)->direction));
        }
    }
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
            
            if (j == rend->threads[i].start || j == rend->threads[i].end - 1 || !(j % 10000))
            {
                printf("j %d, x %d, y %d\n", j, x, y);
                printf("addr %p\n", rend->threads[i].rays + j - rend->threads[i].start);
                print_vector("aux", ((t_ray *) (rend->threads[i].rays + j - rend->threads[i].start))->origin, sum_vector(((t_ray *) (rend->threads[i].rays + j - rend->threads[i].start))->origin, ((t_ray *) (rend->threads[i].rays + j - rend->threads[i].start))->direction));

            }
        }
    }
}

int     get_hit_light(t_list *objs, t_ray *ray, t_td_point *hit_point, t_tuple *hit_obj)
{
    (void) objs;
    (void) ray;
    (void) hit_obj;
    (void) hit_point;
    return 0;
}

void    set_up_inter_ray(int 	(*inter_ray[OBJ_N])(void *obj, t_ray *ray, t_td_point **arr))
{
    inter_ray[OBJ_NULL] = NULL;
    inter_ray[OBJ_TRI] = inter_triangle;
    inter_ray[OBJ_SPH] = inter_sphere;
    inter_ray[OBJ_PLA] = inter_plane;
    inter_ray[OBJ_BOX] = NULL;
    inter_ray[OBJ_CIL] = NULL;
    inter_ray[OBJ_CON] = NULL;
    inter_ray[OBJ_AL] = NULL;
    inter_ray[OBJ_LI] = NULL;
    inter_ray[OBJ_C] = NULL;
}

int     get_hit_ray(t_list *objs, t_ray *ray, t_td_point *hit_point, t_tuple *hit_obj, t_render *render)
{
	static int 	    (*inter_ray[OBJ_N])(void *obj, t_ray *ray, t_td_point **arr);
    t_list          *tmp;
    t_td_point      *arr;
    int             n;
    int             status;
    nType           min = +INFINITY;
    nType           ac_distance;

    arr = NULL;
    if (!objs)
        return 0;
    if (!inter_ray[OBJ_SPH])
        set_up_inter_ray(inter_ray);
    status = 0;
    tmp = objs;
    while (tmp)
    {
        n = inter_ray[((t_tuple *) tmp->content)->type]((t_tuple *) tmp->content, ray, &arr);
        while (n--)
        {
            //Check direction
            if (dot_product(ray->direction, normalize(sum_vector(arr[n], scalar_product(ray->origin, -1)))) < 0)
                continue ;
            //Check closets
            ac_distance = distance(ray->origin, arr[n]);
            if (ac_distance > min)
                continue ;
            //Check sort distance
            if (ac_distance < render->prop_img.near_plane)
                continue ;
            //Check big distance
            if (ac_distance > render->prop_img.far_plane)
                continue ;
            min = ac_distance;
            *hit_point = arr[n];
            *hit_obj = *((t_tuple *) tmp->content);
            status = 1;
        }
        if (arr)
        {
            free(arr);
            arr = NULL;
        }
        tmp = tmp->next;
    }
    return status;
}

t_obj_properties *get_props_from_tuple(t_tuple *tuple)
{
    if (!tuple)
    {
        printf("Error1: get_props_from_tuple %p\n", tuple);
        exit(1);
    }
    if (!tuple->content)
    {
        printf("Error2: get_props_from_tuple %p %p\n", tuple, tuple->content);
        exit(2);
    }
    if (!tuple->type)
    {
        printf("Error3: get_props_from_tuple %s\n", tuple->key);
        exit(3);
    }
    if (tuple->type == OBJ_SPH)
        return (((t_sphere *) tuple->content)->prop);
    if (tuple->type == OBJ_PLA)
        return (((t_plane *) tuple->content)->prop);
    if (tuple->type == OBJ_TRI)
        return (((t_td_triangle *) tuple->content)->prop);
    return NULL;
}

void    *rendered_task(void *arg)
{
    t_thread_render *thread;
    t_rt            *rt;
    t_render        *rend;
    t_td_point      good_hit;
    t_tuple         good_obj;
    int             i;
    t_ray           *ray;

    thread = (t_thread_render *) arg;
    rend = thread->render;
    rt = rend->rt;
    i = thread->start - 1;
    while (++i < thread->end)
    {
        ray = (((t_ray *) thread->rays) + i - thread->start);
        //print_vector("ray", ray->origin, sum_vector(ray->origin, ray->direction));
        if (get_hit_ray(rt->objs_render, ray, &good_hit, &good_obj, rend))
            rt_put_pixel(rend, i, get_props_from_tuple(&good_obj)->color[0] << 16 | get_props_from_tuple(&good_obj)->color[1] << 8 | get_props_from_tuple(&good_obj)->color[2]);
        else
            rt_put_pixel(rend, i, 0x000000);
        //Color pixel0x00FF00
    }
    return (NULL);
}

void    *render_task(void *arg)
{
    t_rt    *rt;
    t_render *rend;
    unsigned int i;

    
    rend = (t_render *) arg;
    rt = rend->rt;
    while (1)
    {
        pthread_mutex_lock(&rt->mutex);
        if (rend->status == RENDERING)
        {
            pthread_mutex_unlock(&rt->mutex);
            break ;
        }
        pthread_mutex_unlock(&rt->mutex);
        usleep(1000);
    }

    i = -1;
    while (++i < rend->prop_perf.n_threads)
    {
        printf("thread %d, start %d, end %d, rays %p\n", rend->threads[i].id, rend->threads[i].start, rend->threads[i].end, rend->threads[i].rays);
        pthread_create(&(rend->threads[i].thread), NULL, rendered_task, rend->threads + i);
    }
    i = -1;
    while (++i < rend->prop_perf.n_threads)
    {
        printf("thread %d, start %d, end %d, rays %p\n", rend->threads[i].id, rend->threads[i].start, rend->threads[i].end, rend->threads[i].rays);
        pthread_join(rend->threads[i].thread, NULL);
    }
    pthread_mutex_lock(&rt->mutex);
    rend->status = RENDERED;
    pthread_mutex_unlock(&rt->mutex);
    return (NULL);
}


void print_rays(t_render *rend)
{
    unsigned int i;
    int j, x, y;
    int index;

    i = -1;
    index = -1;
    while (++i < rend->prop_perf.n_threads)
    {
        j = rend->threads[i].start - 1;
        while (++j < rend->threads[i].end)
        {
            index_to_pixel(&x, &y, ++index, rend);
            if (j == rend->threads[i].start || j == rend->threads[i].end - 1 || !(j % 10000))
            {
                printf("j %d, x %d, y %d\n", j, x, y);
                printf("addr %p\n", rend->threads[i].rays + j - rend->threads[i].start);
                print_vector("au2x", ((t_ray *) (rend->threads[i].rays + j - rend->threads[i].start))->origin, sum_vector(((t_ray *) (rend->threads[i].rays + j - rend->threads[i].start))->origin, ((t_ray *) (rend->threads[i].rays + j - rend->threads[i].start))->direction));
            }
        }
    }
}

int    rt_render_add(t_rt *rt)
{
    t_render    *nuw;

    if (render_get_options(rt, &nuw))
        return (printf("Error: getting render options\n"), 1);
    copy_scene_to_render(rt);
    if (malloc_thread_render(nuw, rt))
        return (rt_render_free(nuw), 3);
    nuw->status = INIT;
    printf("Adding render %p\n", nuw);
    print_render(nuw);
    //ft_lstiter(rt->lights_render, print_objs);
    //ft_lstiter(rt->objs_render, print_objs);
    compute_rays_copy(nuw);
    //print_rays(nuw);
    pthread_create(&(nuw->thread), NULL, render_task, nuw);
    pthread_mutex_lock(&rt->mutex);
    ft_lstadd_back(&rt->renders, ft_lstnew(nuw));
    pthread_mutex_unlock(&rt->mutex);
    return(0);
}
