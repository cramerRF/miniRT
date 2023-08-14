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
    /*
    memory(MEM_CLEAR, NULL);
    memory(MEM_WRITE, line);
    ft_lstiter(rt->cameras, obj_mem_search);
    ft_lstiter(rt->lights, obj_mem_search);
    ft_lstiter(rt->objs, obj_mem_search);
    printf("->>>>>>>>> %s %s\n", line, (char *) memory(MEM_READ, NULL));
    if (!ft_strncmp(line, ((t_tuple *) memory(MEM_READ, NULL))->key, ft_strlen(((t_tuple *) memory(MEM_READ, NULL))->key)))
        return (printf("Not found\n"), free(line), memory(MEM_CLEAR, NULL), 1);
    edit_obj(memory(MEM_READ, NULL));
    memory(MEM_CLEAR, NULL);
    */
    obj = NULL;
    search_obj_key(rt->cameras, &obj, line);
    search_obj_key(rt->lights, &obj, line);
    search_obj_key(rt->objs, &obj, line);
    if (obj)
        edit_obj(obj);
    free(line);
    return (0);
}