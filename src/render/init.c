#include "../../inc/miniRT.h"

//Get options
int     get_prop_image(t_prop_image *img)
{
    retunr (0);
}

int     get_prop_performance(t_prop_performance *perf)
{
    retunr (0);
}

int     get_prop_output(t_prop_output *output)
{
    char    *line;

    printf("Get_prop_output\n");
    printf("Choose format:\n\tbipmap\n\trt\n\n");
    line = get_next_line_nl(0, 0);
    if (!ft_strncmp(line, "rt", 3))
        output->format = OUTPUT_RT;
    else if (!ft_strncmp(line, "bipmap", 7))
        output->format = OUTPUT_BIPMAP;
    else
        return (printf("Error: unknown format\n"), 1);
    free(line);
    printf("Input filename: (with extension)\n");
    output->file = get_next_line_nl(0, 0);
    if (!output->file)
        return (1);
    return (0);
}

int    render_get_options(t_rt *rt, t_render **render)
{
    t_tuple     *obj;
    char        *line;

    *render = malloc(sizeof(t_render));
    ft_bzero(*render, sizeof(t_render));
    printf("Get camera\n");
    printf("Give the identifier\n");
    line = get_next_line_nl(0, 0);
    if (!line)
        return (printf("Error: empty line\n"), free(*render), 1);
    search_obj_key(rt->cameras, &obj, line);
    free(line);
    if (!obj)
        return (printf("Camera nott found\n"), free(*render), 1);
    (*render)->cam = obj->content;
    if (get_prop_image(&(*render)->prop_img))
        return (printf("Error: prop_image\n"), free(*render), 1);
    if (get_prop_perfomance(&(*render)->prop_perf))
        return (printf("Error: prop_perfomance\n"), free(*render), 1);
    if (get_prop_output(&(*render)->prop_out))
        return (printf("Error: prop_output\n"), free(*render), 1);
    return (0);
}
//Copy lights, objects and single
//launch render
//Create list of tasks
//if preview
//  launch  mlx thread
//launch tasks threads
//wait to finish
//save to file