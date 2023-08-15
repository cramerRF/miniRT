#include "../../inc/miniRT.h"

t_tuple    *add_sphere(void)
{
    t_sphere    *sph;
    t_tuple     *obj;

    sph = malloc(sizeof(t_sphere));
    if (!sph)
        return (printf("Error mallocing sph\n"), NULL);
    ft_bzero(sph, sizeof(t_sphere));
    sph->prop = malloc_properties(sizeof(t_obj_properties));
    if (!sph->prop)
        return (printf("Error mallocing sph->prop\n"), free(sph), NULL);
    obj = malloc(sizeof(t_tuple));
    if (!obj)
        return (printf("Error mallocing object\n"), free(sph->prop), free(sph), NULL);
    ft_bzero(obj, sizeof(t_tuple));
    obj->type = OBJ_SPH;
    obj->content = sph;
    obj->key = NULL;
    obj->fixed = 0;
    return (obj);
}

void    print_sphere(t_tuple *obj)
{
    t_sphere *sph;

    sph = obj->content;
    printf("sphere:\t->%s<- addr_obj %p addr_content %p sph %p\n", obj->key, obj, obj->content, sph);
    printf("Center:\t%0.3f %0.3f %0.3f\n", sph->center.x, sph->center.y, sph->center.z);
    printf("Radius:\t%0.3f\n", sph->radius);
    print_properties(sph->prop);
    printf("Fixed:\t%d\n\n", obj->fixed);
}

void    edit_sphere(t_tuple *obj)
{
    t_sphere     *sph;
    char        *line;

    sph = obj->content;
    print_sphere(obj);
    if (obj->fixed)
        printf ("This obj is fixed\n");
    while (1)
    {
        printf("Editing sphere %p\nradius, center, prop, exit\n", sph);
        line = get_next_line_nl(0, 0);
        if (!ft_strncmp(line, "radius", 7))
            sph->radius = get_number("radius", 0, +INFINITY);
        else if (!ft_strncmp(line, "center", 7))
            sph->center = get_point("center", 0);
        else if (!ft_strncmp(line, "prop", 7))
            edit_prop(sph->prop);
        else if (!ft_strncmp(line, "exit", 5))
            break ;
        free(line);
    }
    if (line)
        free(line);
}

void    free_sphere(t_tuple *obj)
{
    if (obj)
    {
        free(((t_sphere *) obj->content)->prop);
        if (obj->content)
            free(obj->content);
        if (obj->key)
            free(obj->key);
        free(obj);
    }
}

//obj->type obj->key sph->center,x3 sph->radius,x3 sph->prop
//0         1        2              3              4

void    write_sphere(t_tuple *obj)
{
    int         fd;
    t_sphere    *sph;

    sph = obj->content;
    fd = *((int *) memory(MEM_READ, NULL));
    if (obj->fixed)
        dprintf(fd, "SP %s %f,%f,%f %f ", obj->key, sph->center.x, sph->center.y, sph->center.z, sph->radius);
    else
        dprintf(fd, "sp %s %f,%f,%f %f ", obj->key, sph->center.x, sph->center.y, sph->center.z, sph->radius);
    write_properties(fd, sph->prop);
    dprintf(fd, "\n");
}

t_tuple    *read_sphere(char *line)
{
    t_tuple    *obj;
    int         len;
    char        **split;

    if (!line || (ft_strncmp(line, "SP", 2) && ft_strncmp(line, "sp", 2)))
        return (printf("Error: read_sphere with line that isnt a sphere\n"), NULL);
    split = ft_split(line, ' ');
    if (!split)
        return (printf("Error: split failed\n"), NULL);
    obj = add_sphere();
    if (!obj)
        return (printf("Error: malloc obj\n"), ft_free_split(split), NULL);
    len = 0;
    while (split[len])
        len++;
    if (len != 5)
        return (printf("Error: split size\n"), ft_free_split(split), free_sphere(obj), NULL);
    if (rt_is_upper(split[0]) && printf("Fixed object\n"))
        obj->fixed = 1;
    obj->key = ft_strdup(split[1]);
    if (line_to_point(split[2], &((t_sphere *) obj->content)->center))
        return (printf("Error: center parsing error\n"), ft_free_split(split), free_sphere(obj), NULL);
    if (atof(split[3]) < 0)
        return (printf("Error: ratio parsing error\n"), ft_free_split(split), free_sphere(obj), NULL);
    ((t_sphere *) obj->content)->radius = atof(split[3]);
    if (parse_properties(((t_sphere *) obj->content)->prop, split[4]))
        return (printf("Error: prop parsing error\n"), ft_free_split(split), free_sphere(obj), NULL);
    return (ft_free_split(split), obj);
}
