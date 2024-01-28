#include "../../inc/miniRT.h"

void    set_up_objs_freer(void     (*objs_freer[OBJ_N])(t_tuple *))
{
	objs_freer[OBJ_NULL] = NULL;
	objs_freer[OBJ_TRI] = free_triangle;
	objs_freer[OBJ_SPH] = free_sphere;
	objs_freer[OBJ_PLA] = free_plane;
	objs_freer[OBJ_BOX] = NULL;
	objs_freer[OBJ_CIL] = NULL;
	objs_freer[OBJ_CON] = NULL;
	objs_freer[OBJ_AL] = free_ambient_light;
	objs_freer[OBJ_LI] = free_light;
	objs_freer[OBJ_C] = free_camera;
}


void	free_objs(void *arg)
{
    static void     (*objs_freer[OBJ_N])(t_tuple *);

    if (!objs_freer[OBJ_C])
        set_up_objs_freer(objs_freer);
    objs_freer[((t_tuple *) arg)->type](arg);
}

int		rt_exit(t_rt *rt)
{
	pthread_mutex_lock(&(rt->mutex));
	if (rt->renders)
	{
		printf("rt_exit: renders still running please close all the windows\n");
		pthread_mutex_unlock(&(rt->mutex));
		return (1);
	}
	//free rt->cameras
    ft_lstclear(&rt->cameras, free_objs);
	//free rt->lights
    ft_lstclear(&rt->lights, free_objs);
	//free rt->objs
    ft_lstclear(&rt->objs, free_objs);
	//free rt->lights_render
	ft_lstclear(&rt->lights_render, free_objs);
	//free rt->objs_render
	ft_lstclear(&rt->objs_render, free_objs);
	//free renderers
	ft_lstclear(&rt->renders, rt_render_free);
	free(rt->file);
	rt->end = 1;
	pthread_mutex_unlock(&(rt->mutex));
	return (0);
}