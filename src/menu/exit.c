#include "../../inc/miniRT.h"

int		rt_exit(t_rt *rt)
{
	//free rt->cameras
	//free rt->lights
	//free rt->objs
	free(rt->file);
	free(rt);
	exit(0);
	return (0);
}