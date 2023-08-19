#include "../../inc/miniRT.h"

int    rt_render_add(t_rt *rt)
{
    t_render    *nuw;

    if (render_get_options(rt, &nuw))
        return (printf("Error: getting render options\n"), 1);
    copy_scene_to_render(rt, nuw);
    print_render(nuw);
    ft_lstiter(nuw->lights, print_objs);
    ft_lstiter(nuw->objs, print_objs);
    return(0);
}