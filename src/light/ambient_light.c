#include "../../inc/miniRT.h"

t_tuple    *add_ambient_light(void)
{
    t_ambient_light *al;
    t_tuple         *obj;

    al = malloc(sizeof(t_ambient_light));
    if (!al)
        return (NULL);
    al->color[0] = 255;
    al->color[1] = 0;
    al->color[2] = 0;
    al->ratio = 1;
    obj = malloc(sizeof(t_tuple));
    if (!obj)
        return (free(al), NULL);
    obj->content = al;
    obj->type = OBJ_AL;
    obj->key = NULL;
    obj->fixed = 0;
    printf("Ambient Light: ->%s<- addr_obj %p addr_content %p ambient light %p\n", obj->key, obj, obj->content, al);
    return (obj);
}

void    print_ambient_light(t_tuple *obj)
{
    t_ambient_light *al;
    
    al = obj->content;
    printf("Ambient Light: ->%s<- addr_obj %p addr_content %p ambient light %p\n", obj->key, obj, obj->content, al);
    printf("Color\t%d,%d,%d\n", al->color[0], al->color[1], al->color[2]);
    printf("Ratio:\t%0.3f\n\n", al->ratio);
    printf("Fixed:\t%d\n\n", obj->fixed);
}

void    edit_ambient_light(t_tuple *obj)
{
    t_ambient_light *al;
    char            *line;

    al = obj->content;
    print_ambient_light(obj);
    if (obj->fixed)
        printf ("This obj is fixed\n");
    while (1)
    {
        printf("Editing ambient light %p\ncolor, ratio, exit\n", al);
        line = get_next_line_nl(0, 0);
        if (!ft_strncmp(line, "color", 6))
            get_color("color", al->color);
        else if (!ft_strncmp(line, "ratio", 6))
            al->ratio = get_number("ratio", 0, 1);
        else if (!ft_strncmp(line, "exit", 5))
            break ;
        free(line);
    }
    if (line)
        free(line);
}

void    free_ambient_light(t_tuple *obj)
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

//obj->type obj->key cam->color,x3 cam->ratio
//0         1        2             3       

void    write_ambient_light(t_tuple *obj)
{
    int             fd;
    t_ambient_light *al;

    al = obj->content;
    fd = *((int *) memory(MEM_READ, NULL));
    if (obj->fixed)
        dprintf(fd, "A %s %d,%d,%d %f\n", obj->key, al->color[0], al->color[1], al->color[2], al->ratio);
    else
        dprintf(fd, "a %s %d,%d,%d %f\n", obj->key, al->color[0], al->color[1], al->color[2], al->ratio);
}

t_tuple    *read_ambient_light(char *line)
{
    t_tuple    *obj;
    int         len;
    char        **split;

    if (!line || (ft_strncmp(line, "A", 1) && ft_strncmp(line, "a", 1)))
        return (printf("Error: read_ambient_light with line that isnt a ambient light\n"), NULL);
    split = ft_split(line, ' ');
    if (!split)
        return (printf("Error: split failed\n"), NULL);
    obj = add_ambient_light();
    if (!obj)
        return (printf("Error: malloc obj\n"), ft_free_split(split), NULL);
    len = 0;
    while (split[len])
        len++;
    if (len != 4)
        return (printf("Error: split size\n"), ft_free_split(split), free_ambient_light(obj), NULL);
    if (rt_is_upper(split[0]) && printf("Fixed object\n"))
        obj->fixed = 1;
    obj->key = ft_strdup(split[1]);
    if (line_to_color(split[2], ((t_ambient_light *) obj->content)->color))
        return (printf("Error: color parsing error\n"), ft_free_split(split), free_ambient_light(obj), NULL);
    if (atof(split[3]) < 0 || atof(split[3]) > 1)
        return (printf("Error: fov parsing error\n"), ft_free_split(split), free_ambient_light(obj), NULL);
    ((t_ambient_light *) obj->content)->ratio = atof(split[3]);
    return (ft_free_split(split), obj);
}
