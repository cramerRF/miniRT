#include "../../inc/miniRT.h"

void    remove_obj_form_lst(t_list **lst, char *key)
{
    t_list  *pre;
    t_list  *actual;
    t_tuple *obj;

    actual = *lst;
    obj = actual->content;
    if (!ft_strncmp(key, obj->key, ft_strlen(key)))
    {
        free_objs(actual->content);
        *lst = (*lst)->next;
        free(actual);
        return ;
    }
    while (actual)
    {
        obj = actual->content;
        if (!ft_strncmp(key, obj->key, ft_strlen(key)))
        {
            pre->next = actual->next;
            free_objs(actual->content);
            free(actual);
            return ;
        }
        pre = actual;
        actual = actual->next;
    }
    return ;
}

int 		rt_delete(t_rt *rt)
{
    char    *line;
    t_tuple *obj;

    rt_list(rt);
    printf("rt_delete %p\nGive the object identifier\n", rt);
    line = get_next_line_nl(0, 0);
    if (!line)
        return (printf("Null line\n"), 1);
    obj = NULL;
    search_obj_key(rt->cameras, &obj, line);
    if (obj)
        return (remove_obj_form_lst(&rt->cameras, line), free(line), 0);
    search_obj_key(rt->lights, &obj, line);
    if (obj)
        return (remove_obj_form_lst(&rt->lights, line), free(line), 0);
    search_obj_key(rt->objs, &obj, line);
    if (obj)
        return (remove_obj_form_lst(&rt->objs, line), free(line), 0);
    free(line);
    printf("Not found\n");
    return (1);
}