#include "../../inc/miniRT.h"

void    set_up_objs_editor(void     (*objs_editor[OBJ_N])(t_tuple *))
{
    objs_editor[OBJ_NULL] = NULL;
	objs_editor[OBJ_TRI] = edit_triangle;
	objs_editor[OBJ_SPH] = edit_sphere;
	objs_editor[OBJ_PLA] = edit_plane;
	objs_editor[OBJ_BOX] = NULL;
	objs_editor[OBJ_CIL] = NULL;
	objs_editor[OBJ_CON] = NULL;
	objs_editor[OBJ_AL] = edit_ambient_light;
	objs_editor[OBJ_LI] = edit_light;
	objs_editor[OBJ_C] = edit_camera;
}

void    edit_obj(void *arg)
{
    static void     (*objs_editor[OBJ_N])(t_tuple *);

    if (!objs_editor[OBJ_C])
        set_up_objs_editor(objs_editor);
    if (arg == NULL)
    {
        printf("Object not found\n");
        return ;
    }
    objs_editor[((t_tuple *) arg)->type](arg);
}

void *memory(int code, void *arg)
{
    static void *mem;

    if (code == MEM_CLEAR)
        mem = NULL;
    else if (code == MEM_WRITE)
        mem = arg;
    else if (code == MEM_READ)
        return (mem);
    return (NULL);
}

void    obj_mem_search(void *arg)
{
    if (ft_strncmp(((t_tuple *) arg)->key, memory(MEM_READ, NULL), ft_strlen(memory(MEM_READ, NULL))))
        return ;
    memory(MEM_WRITE, arg);
}

static void    check_fixed_identifier(t_list *lst, char *key,int type, int flags[CHECK_N])
{
    t_tuple *obj;

    while (lst)
    {
        printf("Checking\n");
        obj = lst->content;
        if (obj->type == type)
        {
            if (obj->fixed)
                flags[CHECK_FIX] = 1;
            flags[CHECK_EXISTS_TYPE] = 1;
        }
        if (!ft_strncmp(obj->key, key, ft_strlen(key)))
            flags[CHECK_KEY] = 1;
        lst = lst->next;
    }
}

int    rt_check_fixed_identifier(t_rt *rt, char *key, int type)
{
    int flags[CHECK_N];
    int flag[1];

    flags[CHECK_KEY] = 0;
    flags[CHECK_FIX] = 0;
    flags[CHECK_EXISTS_TYPE] = 0;
    check_fixed_identifier(rt->cameras, key, type, flags);
    check_fixed_identifier(rt->lights, key, type, flags);
    check_fixed_identifier(rt->objs, key, type, flags);
    if (flags[CHECK_KEY])
        printf("Error: identifier already in use\n");
    if (flags[CHECK_FIX])
        printf("Error: object type fixed\n");
    if (flags[CHECK_EXISTS_TYPE])
        printf("Warning: multiple objs types\n");
    flag[0] = 0;
    if (flags[CHECK_KEY])
        SetBit(((int *) flag), (CHECK_KEY));
    if (flags[CHECK_FIX])
        SetBit(((int *) flag), (CHECK_FIX));
    if (flags[CHECK_EXISTS_TYPE])
        SetBit(((int *) flag), (CHECK_EXISTS_TYPE));
    return (*flag);
}

void    search_obj_key(t_list *lst, t_tuple **ret, char *key)
{
    t_tuple *obj;

    if (*ret)
        return ;
    while (lst)
    {
        obj = lst->content;
        if (!ft_strncmp(obj->key, key, ft_strlen(key)))
        {
            *ret = obj;
            break ;
        }
        lst = lst->next;
    }
}

int rt_edit(t_rt *rt)
{
    char    *line;
    t_tuple *obj;

    rt_list(rt);
    printf("rt_edit %p\nGive the object identifier\n", rt);
    line = get_next_line_nl(0, 0);
    if (!line)
        return (printf("Null line\n"), 1);
    obj = NULL;
    search_obj_key(rt->cameras, &obj, line);
    search_obj_key(rt->lights, &obj, line);
    search_obj_key(rt->objs, &obj, line);
    if (obj)
        edit_obj(obj);
    free(line);
    return (0);
}