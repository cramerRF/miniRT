#include "../../inc/miniRT.h"

void    set_up_objs_freer(void     (*objs_freer[OBJ_N])(t_tuple *))
{
	objs_freer[OBJ_NULL] = NULL;
	objs_freer[OBJ_TRI] = NULL;
	objs_freer[OBJ_SPH] = NULL;
	objs_freer[OBJ_PLA] = NULL;
	objs_freer[OBJ_BOX] = NULL;
	objs_freer[OBJ_CIL] = NULL;
	objs_freer[OBJ_CON] = NULL;
	objs_freer[OBJ_AL] = NULL;
	objs_freer[OBJ_LI] = NULL;
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
	//free rt->cameras
    ft_lstclear(&rt->cameras, free_objs);
	//free rt->lights
    ft_lstclear(&rt->lights, free_objs);
	//free rt->objs
    ft_lstclear(&rt->objs, free_objs);
	free(rt->file);
	free(rt);
	return (0);
}