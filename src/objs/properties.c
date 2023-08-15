#include "../../inc/miniRT.h"

void    print_properties(t_obj_properties *prop)
{
    if (!prop)
        return ;
    printf("\tProperties %p\n", prop);
    printf("\t\tColor:\t%d,%d,%d\n", prop->color[0], prop->color[1], prop->color[2]);
    printf("\t\tDensity:\t%0.3f\n", prop->density);
    printf("\t\tReflextion:\t%0.3f\n", prop->reflexction);
    printf("\t\tTransparency:\t%0.3f\n", prop->transparency);
}

void    edit_prop(t_obj_properties *prop)
{
    char        *line;

    if (!prop)
        return ;
    print_properties(prop);
    while (1)
    {
        printf("Editing properties %p\ncolor, density, reflexction, transparency, exit\n", prop);
        line = get_next_line_nl(0, 0);
        if (!ft_strncmp(line, "color", 6))
            get_color("color", prop->color);
        if (!ft_strncmp(line, "density", 8))
            prop->density = get_number("density", 0, 1);
        if (!ft_strncmp(line, "transparency", 13))
            prop->transparency = get_number("transparency", 0, 1);
        if (!ft_strncmp(line, "reflexction", 13))
            prop->reflexction = get_number("reflexction", 1, +INFINITY);
        else if (!ft_strncmp(line, "exit", 5))
            break ;
        free(line);
    }
    if (line)
        free(line);
}

//  color,x3    transparency    reflexction    density
//  0           1               2              3

void    write_properties(int fd, t_obj_properties  *prop)
{
    if (!prop)
        return ;
    dprintf(fd, "%d,%d,%d_%0.3f_%0.3f_%0.3f", prop->color[0], prop->color[1], prop->color[2], prop->transparency, prop->reflexction, prop->density);
}

t_obj_properties *malloc_properties()
{
    t_obj_properties    *prop;

    prop = malloc(sizeof(t_obj_properties));
    if (!prop)
        return (printf("Error mallocing prop\n"), NULL);
    ft_bzero(prop, sizeof(t_obj_properties));
    prop->color[0] = 255;
    prop->density = 1;
    prop->transparency = 1;
    prop->reflexction = 1;
    return (prop);
}

int    parse_properties(t_obj_properties *prop, char *line)
{
    char    **split;
    int     len;

    if (!line)
        return (1);
    split = ft_split(line, '_');
    if (!split)
        return (printf("Error: mallocing split\n"), 1);
    len = 0;
    while (split[len])
        len++;
    if (len != 4)
        return (printf("Error: %d split len should be 4\n", len), ft_free_split(split), 1);
    if (line_to_color(split[0], prop->color))
        return (printf("Error: color parsing error\n"), ft_free_split(split), 1);
    if (atof(split[1]) < 0 || atof(split[1]) > 1)
        return (printf("Error: transparency out of boundaries\n"), ft_free_split(split), 1);
    prop->transparency = atof(split[1]);
    if (atof(split[2]) < 1)
        return (printf("Error: reflaxction out of boundaries\n"), ft_free_split(split), 1);
    prop->reflexction = atof(split[2]);
    if (atof(split[3]) < 0 || atof(split[3]) > 1)
        return (printf("Error: density out of boundaries\n"), ft_free_split(split), 1);
    prop->density = atof(split[3]);
    ft_free_split(split);
    return (0);
}
