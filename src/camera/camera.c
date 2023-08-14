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
    printf("Camera:\t->%s<- addr_obj %p addr_content %p cam %p\n", obj->key, obj, obj->content, cam);
    printf("Vertex:\t%0.3f %0.3f %0.3f\n", cam->vertex.x, cam->vertex.y, cam->vertex.z);
    printf("Normal:\t%0.3f %0.3f %0.3f\n", cam->normal.x, cam->normal.y, cam->normal.z);
    printf("Fov:\t%0.3f\n", cam->fov);
    printf("Fixed:\t%d\n\n", obj->fixed);
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
    if (obj)
    {
        if (obj->content)
            free(obj->content);
        if (obj->key)
            free(obj->key);
        free(obj);
    }
}

//obj->type obj->key cam->vertex,x3 cam->normal,x3 cam->fov
//0         1        2              3              4

void    write_camera(t_tuple *obj)
{
    int         fd;
    t_camera    *cam;

    cam = obj->content;
    fd = *((int *) memory(MEM_READ, NULL));
    dprintf(fd, "C %s %f,%f,%f %f,%f,%f %f\n", obj->key, cam->vertex.x, cam->vertex.y, cam->vertex.z, cam->normal.x, cam->normal.y, cam->normal.z, cam->fov);
}

t_tuple     *malloc_camera_obj(void)
{
    t_camera    *cam;
    t_tuple     *obj;

    cam = malloc(sizeof(t_camera));
    if (!cam)
        return (printf("Error mallocing cam\n"), NULL);
    obj = malloc(sizeof(t_tuple));
    if (!obj)
        return (printf("Error mallocing object\n"), free(cam), NULL);
    ft_bzero(cam, sizeof(t_camera));
    ft_bzero(obj, sizeof(t_tuple));
    obj->type = OBJ_C;
    obj->content = cam;
    obj->key = NULL;
    obj->fixed = 0;
    return (obj);
}

t_tuple    *read_camera(char *line)
{
    t_tuple    *obj;
    int         len;
    char        **split;

    if (!line || (ft_strncmp(line, "C", 1) && ft_strncmp(line, "c", 1)))
        return (printf("Error: read_camera with line that isnt a camera\n"), NULL);
    split = ft_split(line, ' ');
    if (!split)
        return (printf("Error: split failed\n"), NULL);
    obj = malloc_camera_obj();
    if (!obj)
        return (printf("Error: malloc obj\n"), ft_free_split(split), NULL);
    len = 0;
    while (split[len])
        len++;
    if (len != 5)
        return (printf("Error: split size\n"), ft_free_split(split), free_camera(obj), NULL);
    obj->key = ft_strdup(split[1]);
    if (line_to_point(split[3], &((t_camera *) obj->content)->normal))
        return (printf("Error: normal parsing error\n"), ft_free_split(split), free_camera(obj), NULL);
    if (line_to_point(split[2], &((t_camera *) obj->content)->vertex))
        return (printf("Error: vertex parsing error\n"), ft_free_split(split), free_camera(obj), NULL);
    if (atof(split[4]) < 0 || atof(split[4]) > 180)
        return (printf("Error: fov parsing error\n"), ft_free_split(split), free_camera(obj), NULL);
    ((t_camera *) obj->content)->fov = atof(split[4]);
    return (ft_free_split(split), obj);
}
