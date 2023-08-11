#include "../../inc/miniRT.h"

void    set_up_objs_writer(void     (*objs_writer[OBJ_N])(t_tuple *))
{
    objs_writer[OBJ_NULL] = NULL;
	objs_writer[OBJ_TRI] = NULL;
	objs_writer[OBJ_SPH] = NULL;
	objs_writer[OBJ_PLA] = NULL;
	objs_writer[OBJ_BOX] = NULL;
	objs_writer[OBJ_CIL] = NULL;
	objs_writer[OBJ_CON] = NULL;
	objs_writer[OBJ_AL] = NULL;
	objs_writer[OBJ_LI] = NULL;
	objs_writer[OBJ_C] = write_camera;
}

void    save_objs(void *arg)
{
    static void     (*objs_writer[OBJ_N])(t_tuple *);
    t_tuple         *obj;

    obj = arg;
    if (!objs_writer[OBJ_C])
        set_up_objs_writer(objs_writer);
    if (!objs_writer[obj->type])
    {
        printf("Not implemented type %d\n", obj->type);
        return ;
    }
    objs_writer[obj->type](obj);
}

void    rt_write(int fd, t_rt *rt)
{    
    memory(MEM_CLEAR, NULL);
    memory(MEM_WRITE, &fd);
    write(fd, "#cameras\n", 10);
    ft_lstiter(rt->cameras, save_objs);
    write(fd, "#lights\n", 9);
    ft_lstiter(rt->lights, save_objs);
    write(fd, "#objs\n", 7);
    ft_lstiter(rt->objs, save_objs);
    memory(MEM_CLEAR, NULL);
}

int rt_save(t_rt *rt)
{
    char    *input;
    char    *file;
    int     fd;

    printf("rt_save %p file: %s\nSure you want to save it here? (Y/N) Y\n", rt, rt->file);
    file = NULL;
    input = get_next_line_nl(0, 0);
    if (!ft_strncmp(input, "N", 2) || !ft_strncmp(input, "n", 2))
    {
        printf("Input file name:\n");
        file = get_next_line_nl(0, 0);
    }
    if (!file)
        file = rt->file;
    fd = open(file, O_CREAT | O_TRUNC | O_RDWR, 0644);
    if (fd < 0)
        return (printf("Error opening file for writing\n"), (file == rt->file) ? NULL : free(file), 1);
    rt_write(fd, rt);
    close(fd);
    if (file != rt->file)
        free(file);
    return (0);
}