#include "../../inc/miniRT.h"

void    set_up_objs_editor(void     (*objs_editor[OBJ_N])(t_tuple *))
{
    objs_editor[OBJ_NULL] = NULL;
	objs_editor[OBJ_TRI] = NULL;
	objs_editor[OBJ_SPH] = NULL;
	objs_editor[OBJ_PLA] = NULL;
	objs_editor[OBJ_BOX] = NULL;
	objs_editor[OBJ_CIL] = NULL;
	objs_editor[OBJ_CON] = NULL;
	objs_editor[OBJ_AL] = NULL;
	objs_editor[OBJ_LI] = NULL;
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
    {
        mem = NULL;
        return (mem = NULL, NULL);
    }
    else if (code == MEM_WRITE)
    {
        mem = arg;
        return (NULL);
    }
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

int rt_edit(t_rt *rt)
{
    char    *line;

    rt_list(rt);
    printf("rt_edit %p\nGive the object identifier\n", rt);
    line = get_next_line_nl(0, 0);
    memory(MEM_CLEAR, NULL);
    memory(MEM_WRITE, line);
    ft_lstiter(rt->cameras, obj_mem_search);
    ft_lstiter(rt->lights, obj_mem_search);
    ft_lstiter(rt->objs, obj_mem_search);
    if (line == (char *) memory(MEM_READ, NULL))
        return (free(line), memory(MEM_CLEAR, NULL), 1);
    edit_obj(memory(MEM_READ, NULL));
    memory(MEM_CLEAR, NULL);
    free(line);
    return (0);
}