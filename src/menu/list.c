#include "../../inc/miniRT.h"

void    set_up_objs_printer(void     (*objs_printer[OBJ_N])(t_tuple *))
{
    objs_printer[OBJ_NULL] = NULL;
	objs_printer[OBJ_TRI] = NULL;
	objs_printer[OBJ_SPH] = NULL;
	objs_printer[OBJ_PLA] = NULL;
	objs_printer[OBJ_BOX] = NULL;
	objs_printer[OBJ_CIL] = NULL;
	objs_printer[OBJ_CON] = NULL;
	objs_printer[OBJ_AL] = print_ambient_light;
	objs_printer[OBJ_LI] = print_light;
	objs_printer[OBJ_C] = print_camera;
}

void    print_objs(void *arg)
{
    static void     (*objs_printer[OBJ_N])(t_tuple *);

    if (!objs_printer[OBJ_C])
        set_up_objs_printer(objs_printer);
    objs_printer[((t_tuple *) arg)->type](arg);
}

int rt_list(t_rt *rt)
{
    printf("rt_list %p\n", rt);
    printf("Listing cameras---------------------------\n\n");
    ft_lstiter(rt->cameras, print_objs);
    printf("Listing lights----------------------------\n\n");
    ft_lstiter(rt->lights, print_objs);
    printf("Listing objs------------------------------\n\n");
    ft_lstiter(rt->objs, print_objs);
    printf("------------------------------------------\n");
    return (0);
}