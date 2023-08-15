#include "../../inc/miniRT.h"

static void    set_up_add_parser(t_tuple *(*parser[EX_N])(void))
{
    parser[OBJ_NULL] = NULL;
	parser[OBJ_TRI] = NULL;
	parser[OBJ_SPH] = add_sphere;
	parser[OBJ_PLA] = NULL;
	parser[OBJ_BOX] = NULL;
	parser[OBJ_CIL] = NULL;
	parser[OBJ_CON] = NULL;
	parser[OBJ_AL] = add_ambient_light;
	parser[OBJ_LI] = add_light;
	parser[OBJ_C] = add_camera;
}

static int get_add_code(char *line)
{
    if (!line)
        return (0);
	else if (!ft_strncmp(line, "triangle", 9))
        return (OBJ_TRI);
	else if (!ft_strncmp(line, "sphere", 7))
        return (OBJ_SPH);
	else if (!ft_strncmp(line, "plane", 6))
        return (OBJ_PLA);
	else if (!ft_strncmp(line, "box", 4))
        return (OBJ_BOX);
	else if (!ft_strncmp(line, "cilinder", 9))
        return (OBJ_CIL);
    else if (!ft_strncmp(line, "cone", 5))
        return (OBJ_CON);
    else if (!ft_strncmp(line, "ambient_light", 14))
        return (OBJ_AL);
    else if (!ft_strncmp(line, "light", 6))
        return (OBJ_LI);
    else if (!ft_strncmp(line, "camera", 7))
        return (OBJ_C);
    return (0);
}

int 		rt_add(t_rt *rt)
{
    char    *line;
    int     code;
    static t_tuple     *(*add_parser[EX_N])(void);
    t_tuple     *nuw;
    t_list      *lst;
    int         flag[1];

    if (!add_parser[EX_ADD])
        set_up_add_parser(add_parser);
    printf("Select an object:\n\t-camera\n\n\t-light\n\t-ambinet_light\n\n\t-triangle\n\t-plane\n\t-sphere\n\n");
    line = get_next_line_nl(0, 0);
    code = get_add_code(line);
    free(line);
    if (!add_parser[code])
        return (printf("Not implemented add code %d\n", code), 1);
    nuw = add_parser[code]();
    if (!nuw)
        return (printf("Error rt add parser\n"), 1);
    printf("Give the identifier\n");
    line = get_next_line_nl(0, 0);
    //Check fixed
    nuw->key = line;
    *flag = rt_check_fixed_identifier(rt, nuw->key, nuw->type);
    if ((nuw->fixed && TestBit(flag, CHECK_EXISTS_TYPE)) || TestBit(flag, CHECK_FIX) || TestBit(flag, CHECK_KEY))
        return(free_objs(nuw), printf("Error concurrency\n"), 1);
    lst = ft_lstnew(nuw);
    if (!lst)
        return(free_objs(nuw), printf("Error creating list\n"), 1);
    if (nuw->type == OBJ_C)
        ft_lstadd_back(&rt->cameras, lst);
    else if (nuw->type == OBJ_LI || nuw->type == OBJ_AL)
        ft_lstadd_back(&rt->lights, lst);
    else if (nuw->type != OBJ_NULL)
        ft_lstadd_back(&rt->objs, lst);
    else
        return(free_objs(nuw), free(lst), printf("Unknown obj type\n"), 1);
    return (0);
} 