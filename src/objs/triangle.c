#include "../../inc/miniRT.h"

t_tuple    *add_triangle(void)
{
    t_td_triangle    *tri;
    t_tuple     *obj;

    tri = malloc(sizeof(t_td_triangle));
    ft_bzero(tri, sizeof(t_td_triangle));
    if (!tri)
        return (printf("Error mallocing tri\n"), NULL);
    tri->prop = malloc_properties(sizeof(t_obj_properties));
    if (!tri->prop)
        return (printf("Error mallocing tri->prop\n"), free(tri), NULL);
    obj = malloc(sizeof(t_tuple));
    if (!obj)
        return (printf("Error mallocing object\n"), free(tri->prop), free(tri), NULL);
    ft_bzero(obj, sizeof(t_tuple));
    obj->type = OBJ_TRI;
    obj->content = tri;
    obj->key = NULL;
    obj->fixed = 0;
    return (obj);
}

void    print_triangle(t_tuple *obj)
{
    t_td_triangle *tri;

    tri = obj->content;
    printf("triangle:\t->%s<- addr_obj %p addr_content %p tri %p\n", obj->key, obj, obj->content, tri);
    printf("a:\t%0.3f %0.3f %0.3f\n", tri->a.x, tri->a.y, tri->a.z);
    printf("b:\t%0.3f %0.3f %0.3f\n", tri->b.x, tri->b.y, tri->b.z);
    printf("c:\t%0.3f %0.3f %0.3f\n", tri->c.x, tri->c.y, tri->c.z);
    print_properties(tri->prop);
    printf("Fixed:\t%d\n\n", obj->fixed);
}

void    edit_triangle(t_tuple *obj)
{
    t_td_triangle     *tri;
    char        *line;

    tri = obj->content;
    print_triangle(obj);
    if (obj->fixed)
        printf ("This obj is fixed\n");
    while (1)
    {
        printf("Editing triangle %p\na, b, c, exit\n", tri);
        line = get_next_line_nl(0, 0);
        if (!ft_strncmp(line, "a", 2))
            tri->a = get_point("a", 0);
        else if (!ft_strncmp(line, "b", 2))
            tri->b = get_point("b", 0);
        else if (!ft_strncmp(line, "c", 2))
            tri->c = get_point("c", 0);
        else if (!ft_strncmp(line, "prop", 7))
            edit_prop(tri->prop);
        else if (!ft_strncmp(line, "exit", 5))
            break ;
        free(line);
    }
    if (line)
        free(line);
}

void    free_triangle(t_tuple *obj)
{
    if (obj)
    {
        free(((t_td_triangle *) obj->content)->prop);
        if (obj->content)
            free(obj->content);
        if (obj->key)
            free(obj->key);
        free(obj);
    }
}

//obj->type obj->key tri->a,x3      tri->b,x3      tri->c,x3    tri->prop
//0         1        2              3              4            5

void    write_triangle(t_tuple *obj)
{
    int         fd;
    t_td_triangle    *tri;

    tri = obj->content;
    fd = *((int *) memory(MEM_READ, NULL));
    if (obj->fixed)
        dprintf(fd, "TR %s %f,%f,%f %f,%f,%f %f,%f,%f ", obj->key, tri->a.x, tri->a.y, tri->a.z, tri->b.x, tri->b.y, tri->b.z, tri->c.x, tri->c.y, tri->c.z);
    else
        dprintf(fd, "tr %s %f,%f,%f %f,%f,%f %f,%f,%f ", obj->key, tri->a.x, tri->a.y, tri->a.z, tri->b.x, tri->b.y, tri->b.z, tri->c.x, tri->c.y, tri->c.z);
    write_properties(fd, tri->prop);
    dprintf(fd, "\n");
}

t_tuple    *read_triangle(char *line)
{
    t_tuple    *obj;
    int         len;
    char        **split;

    if (!line || (ft_strncmp(line, "TR", 2) && ft_strncmp(line, "tr", 2)))
        return (printf("Error: read_triangle with line that isnt a triangle\n"), NULL);
    split = ft_split(line, ' ');
    if (!split)
        return (printf("Error: split failed\n"), NULL);
    obj = add_triangle();
    if (!obj)
        return (printf("Error: malloc obj\n"), ft_free_split(split), NULL);
    len = 0;
    while (split[len])
        len++;
    if (len != 6)
        return (printf("Error: split size\n"), ft_free_split(split), free_triangle(obj), NULL);
    if (rt_is_upper(split[0]) && printf("Fixed object\n"))
        obj->fixed = 1;
    obj->key = ft_strdup(split[1]);
    if (line_to_point(split[2], &((t_td_triangle *) obj->content)->a))
        return (printf("Error: a parsing error\n"), ft_free_split(split), free_triangle(obj), NULL);
    if (line_to_point(split[3], &((t_td_triangle *) obj->content)->b))
        return (printf("Error: b parsing error\n"), ft_free_split(split), free_triangle(obj), NULL);
    if (line_to_point(split[4], &((t_td_triangle *) obj->content)->c))
        return (printf("Error: c parsing error\n"), ft_free_split(split), free_triangle(obj), NULL);
    if (parse_properties(((t_td_triangle *) obj->content)->prop, split[5]))
        return (printf("Error: prop parsing error\n"), ft_free_split(split), free_triangle(obj), NULL);
    return (ft_free_split(split), obj);
}
