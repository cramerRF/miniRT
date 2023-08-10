#include "../../inc/miniRT.h"

t_camera    *create_camera()
{
    t_camera    *cam;

    cam = malloc(sizeof(t_camera));
    if (!cam)
        return (NULL);
    cam->fov = 90;
    cam->normal = (t_td_point) {1, 0, 0};
    cam->vertex = (t_td_point) {0, 0, 0};
    return (cam);
}

void    edit_camera(t_camera *cam)
{
    char    *line;

    while (1)
    {
        printf("Editing camera %p\nfov, normal, vertex, exit\n", cam);
        line = get_next_line(0);
        if (line)
            line[ft_strlen(line) - 1] = 0;
        if (!ft_strncmp(line, "fov", 4))
            cam->fov = get_number("fov", 0, 180);
        else if (!ft_strncmp(line, "normal", 7))
            cam->normal = get_point("normal", 1);
        else if (!ft_strncmp(line, "vertex", 7))
            cam->vertex = get_point("vertex", 0);
        else if (!ft_strncmp(line, "exit", 5))
            break ;
        free(line);
    }
    if (line)
        free(line);
}