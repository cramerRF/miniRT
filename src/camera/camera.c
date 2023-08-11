#include "../../inc/miniRT.h"


t_tuple    *add_camera(void)
{
    t_camera    *cam;
    t_tuple     *obj;

    cam = malloc(sizeof(t_camera));
    if (!cam)
        return (NULL);
    cam->fov = 90;
    cam->normal = (t_td_point) {1, 0, 0};
    cam->vertex = (t_td_point) {0, 0, 0};
    obj = malloc(sizeof(t_tuple));
    if (!obj)
        return (free(cam), NULL);
    obj->content = cam;
    obj->type = OBJ_C;
    obj->key = NULL;
    obj->fixed = 0;
    printf("Camera: ->%s<- addr_obj %p addr_content %p cam %p\n", obj->key, obj, obj->content, cam);
    return (obj);
}

void    print_camera(t_tuple *obj)
{
    t_camera *cam;

    cam = obj->content;
    printf("Camera: ->%s<- addr_obj %p addr_content %p cam %p\n", obj->key, obj, obj->content, cam);
    printf("Vertex: %0.3f %0.3f %0.3f\n", cam->vertex.x, cam->vertex.y, cam->vertex.z);
    printf("Normal: %0.3f %0.3f %0.3f\n", cam->normal.x, cam->normal.y, cam->normal.z);
    printf("Fov: %0.3f\n\n", cam->fov);
}

void    edit_camera(t_tuple *obj)
{
    t_camera    *cam;
    char        *line;

    cam = obj->content;
    print_camera(obj);
    if (obj->fixed)
        printf ("This obj is fixed\n");
    while (1)
    {
        printf("Editing camera %p\nfov, normal, vertex, exit\n", cam);
        line = get_next_line_nl(0, 0);
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

void    free_camera(t_tuple *obj)
{
    free(obj->key);
    free(obj->content);
    free(obj);
}

void    write_camera(t_tuple *obj)
{
    obj++;
}

void    read_camera(t_tuple *obj)
