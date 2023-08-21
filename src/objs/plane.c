#include "../../inc/miniRT.h"

t_tuple    *add_plane(void)
{
    t_plane    *pla;
    t_tuple     *obj;

    pla = malloc(sizeof(t_plane));
    if (!pla)
        return (printf("Error mallocing pla\n"), NULL);
    ft_bzero(pla, sizeof(t_plane));
    pla->prop = malloc_properties(sizeof(t_obj_properties));
    if (!pla->prop)
        return (printf("Error mallocing pla->prop\n"), free(pla), NULL);
    obj = malloc(sizeof(t_tuple));
    if (!obj)
        return (printf("Error mallocing object\n"), free(pla->prop), free(pla), NULL);
    ft_bzero(obj, sizeof(t_tuple));
    obj->type = OBJ_PLA;
    obj->content = pla;
    obj->key = NULL;
    obj->fixed = 0;
    return (obj);
}

void    print_plane(t_tuple *obj)
{
    t_plane *pla;

    pla = obj->content;
    printf("plane:\t->%s<- addr_obj %p addr_content %p pla %p\n", obj->key, obj, obj->content, pla);
    printf("Center:\t%0.3f %0.3f %0.3f\n", pla->center.x, pla->center.y, pla->center.z);
    printf("Normal:\t%0.3f %0.3f %0.3f\n", pla->normal.x, pla->normal.y, pla->normal.z);
    print_properties(pla->prop);
    printf("Fixed:\t%d\n\n", obj->fixed);
}

void    edit_plane(t_tuple *obj)
{
    t_plane     *pla;
    char        *line;

    pla = obj->content;
    print_plane(obj);
    if (obj->fixed)
        printf ("This obj is fixed\n");
    while (1)
    {
        printf("Editing plane %p\nnormal, center, exit\n", pla);
        line = get_next_line_nl(0, 0);
        if (!ft_strncmp(line, "normal", 7))
            pla->normal = get_point("normal", 1);
        else if (!ft_strncmp(line, "center", 7))
            pla->center = get_point("center", 0);
        else if (!ft_strncmp(line, "prop", 7))
            edit_prop(pla->prop);
        else if (!ft_strncmp(line, "exit", 5))
            break ;
        free(line);
    }
    if (line)
        free(line);
}

void    free_plane(t_tuple *obj)
{
    if (obj)
    {
        free(((t_plane *) obj->content)->prop);
        if (obj->content)
            free(obj->content);
        if (obj->key)
            free(obj->key);
        free(obj);
    }
}

//obj->type obj->key pla->center,x3 pla->normal,x3 pla->prop
//0         1        2              3              4

void    write_plane(t_tuple *obj)
{
    int         fd;
    t_plane    *pla;

    pla = obj->content;
    fd = *((int *) memory(MEM_READ, NULL));
    if (obj->fixed)
        dprintf(fd, "PL %s %f,%f,%f %f,%f,%f ", obj->key, pla->center.x, pla->center.y, pla->center.z, pla->normal.x, pla->normal.y, pla->normal.z);
    else
        dprintf(fd, "pl %s %f,%f,%f %f,%f,%f ", obj->key, pla->center.x, pla->center.y, pla->center.z, pla->normal.x, pla->normal.y, pla->normal.z);
    write_properties(fd, pla->prop);
    dprintf(fd, "\n");
}

t_tuple    *read_plane(char *line)
{
    t_tuple    *obj;
    int         len;
    char        **split;

    if (!line || (ft_strncmp(line, "PL", 2) && ft_strncmp(line, "pl", 2)))
        return (printf("Error: read_plane with line that isnt a plane\n"), NULL);
    split = ft_split(line, ' ');
    if (!split)
        return (printf("Error: split failed\n"), NULL);
    obj = add_plane();
    if (!obj)
        return (printf("Error: malloc obj\n"), ft_free_split(split), NULL);
    len = 0;
    while (split[len])
        len++;
    if (len != 5)
        return (printf("Error: split size\n"), ft_free_split(split), free_plane(obj), NULL);
    if (rt_is_upper(split[0]) && printf("Fixed object\n"))
        obj->fixed = 1;
    obj->key = ft_strdup(split[1]);
    if (line_to_point(split[2], &((t_plane *) obj->content)->center))
        return (printf("Error: center parsing error\n"), ft_free_split(split), free_plane(obj), NULL);
    if (line_to_point(split[3], &((t_plane *) obj->content)->normal))
        return (printf("Error: normal parsing error\n"), ft_free_split(split), free_plane(obj), NULL);
    if (parse_properties(((t_plane *) obj->content)->prop, split[4]))
        return (printf("Error: prop parsing error\n"), ft_free_split(split), free_plane(obj), NULL);
    return (ft_free_split(split), obj);
}

void *copy_plane(void *arg)
{
    t_tuple *ori;
    t_tuple *nuw;
    t_plane *plane;

    ori = arg;
    nuw = malloc(sizeof(t_tuple));
    if (!nuw)
        return (printf("Error: malloc t_tuple\n"), NULL);
    nuw->type = ori->type;
    nuw->fixed = ori->fixed;
    nuw->key = ft_strdup(ori->key);
    if (!nuw->key)
        return (printf("Error: ft_strdup\n"), free(nuw), NULL);
    plane = malloc(sizeof(t_plane));
    if (!nuw->key)
        return (printf("Error: malloc t_plane\n"), free(nuw->key), free(nuw), NULL);
    ft_memmove(plane, ori->content, sizeof(t_plane));
    nuw->content = plane;
    return (nuw);
}