#include "../../inc/miniRT.h"

t_tuple    *add_light(void)
{
    t_light     *li;
    t_tuple     *obj;

    li = malloc(sizeof(t_light));
    if (!li)
        return (NULL);
    li->center = (t_td_point) {0, 0, 0};
    li->color[0] = 255;
    li->color[1] = 0;
    li->color[2] = 0;
    li->ratio = 1;
    obj = malloc(sizeof(t_tuple));
    if (!obj)
        return (free(li), NULL);
    obj->content = li;
    obj->type = OBJ_LI;
    obj->key = NULL;
    obj->fixed = 0;
    printf("Light: ->%s<- addr_obj %p addr_content %p li %p\n", obj->key, obj, obj->content, li);
    return (obj);
}

void    print_light(t_tuple *obj)
{
    t_light *li;

    li = obj->content;
    printf("Light:\t->%s<- addr_obj %p addr_content %p li %p\n", obj->key, obj, obj->content, li);
    printf("Center:\t%0.3f %0.3f %0.3f\n", li->center.x, li->center.y, li->center.z);
    printf("Color:\t%d %d %d\n", li->color[0], li->color[1], li->color[2]);
    printf("Ratio:\t%0.3f\n", li->ratio);
    printf("Fixed:\t%d\n\n", obj->fixed);
}

void    edit_light(t_tuple *obj)
{
    t_light     *li;
    char        *line;

    li = obj->content;
    print_light(obj);
    if (obj->fixed)
        printf ("This obj is fixed\n");
    while (1)
    {
        printf("Editing light %p\nratio, center, color, exit\n", li);
        line = get_next_line_nl(0, 0);
        if (!ft_strncmp(line, "ratio", 4))
            li->ratio = get_number("ratio", 0, 1);
        else if (!ft_strncmp(line, "center", 7))
            li->center = get_point("center", 0);
        else if (!ft_strncmp(line, "color", 7))
            get_color("color", li->color);
        else if (!ft_strncmp(line, "exit", 5))
            break ;
        free(line);
    }
    if (line)
        free(line);
}

void    free_light(t_tuple *obj)
{
    if (obj)
    {
        if (obj->content)
            free(obj->content);
        if (obj->key)
            free(obj->key);
        free(obj);
    }
}

//obj->type obj->key li->center,x3 li->color,x3 li->fov
//0         1        2              3              4

void    write_light(t_tuple *obj)
{
    int         fd;
    t_light    *li;

    li = obj->content;
    fd = *((int *) memory(MEM_READ, NULL));
    if (obj->fixed)
        dprintf(fd, "L %s %f,%f,%f %d,%d,%d %f\n", obj->key, li->center.x, li->center.y, li->center.z, li->color[0], li->color[1], li->color[2], li->ratio);
    else
        dprintf(fd, "l %s %f,%f,%f %d,%d,%d %f\n", obj->key, li->center.x, li->center.y, li->center.z, li->color[0], li->color[1], li->color[2], li->ratio);
}

t_tuple    *read_light(char *line)
{
    t_tuple    *obj;
    int         len;
    char        **split;

    if (!line || (ft_strncmp(line, "L", 1) && ft_strncmp(line, "l", 1)))
        return (printf("Error: read_light with line that isnt a light\n"), NULL);
    split = ft_split(line, ' ');
    if (!split)
        return (printf("Error: split failed\n"), NULL);
    obj = add_light();
    if (!obj)
        return (printf("Error: malloc obj\n"), ft_free_split(split), NULL);
    len = 0;
    while (split[len])
        len++;
    if (len != 5)
        return (printf("Error: split size\n"), ft_free_split(split), free_light(obj), NULL);
    if (rt_is_upper(split[0]) && printf("Fixed object\n"))
        obj->fixed = 1;
    obj->key = ft_strdup(split[1]);
    if (line_to_point(split[3], &((t_light *) obj->content)->center))
        return (printf("Error: center parsing error\n"), ft_free_split(split), free_light(obj), NULL);
    if (line_to_color(split[2], ((t_light *) obj->content)->color))
        return (printf("Error: color parsing error\n"), ft_free_split(split), free_light(obj), NULL);
    if (atof(split[4]) < 0 || atof(split[4]) > 1)
        return (printf("Error: ratio parsing error\n"), ft_free_split(split), free_light(obj), NULL);
    ((t_light *) obj->content)->ratio = atof(split[4]);
    return (ft_free_split(split), obj);
}
