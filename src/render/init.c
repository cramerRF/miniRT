#include "../../inc/miniRT.h"

//Get options
void    default_prop_image(t_prop_image *img)
{
    img->far_plane = 100;
    img->near_plane = 1;
    img->pixel_height = 1080;
    img->pixel_witdh = 1920;
    img->ratio[0] = 16;
    img->ratio[1] = 9;
}

int     get_prop_image(t_prop_image *img)
{
    char    *line;

    printf("Get_prop_image\n");
    printf("Default config: (Y/N default N)\n");
    line = get_next_line_nl(0, 0);
    if (!line)
        return (printf("Error: getting line\n"), 1);
    if (!ft_strncmp("Y", line, 2))
        return (printf("Loaded default prop image\n"), free(line), default_prop_image(img), 0);
    free(line);
    printf("Pixel_witdh:\n");
    line = get_next_line_nl(0, 0);
    if (!line)
        return (printf("Error: getting line\n"), 1);
    img->pixel_witdh = ft_atoi(line);
    free(line);
    if (img->pixel_witdh < 600)
        img->pixel_witdh = 600;
    printf("Pixel_height:\n");
    line = get_next_line_nl(0, 0);
    if (!line)
        return (printf("Error: getting line\n"), 1);
    img->pixel_height = ft_atoi(line);
    free(line);
    if (img->pixel_height < 480 || img->pixel_witdh > 4000)
        img->pixel_height = 480;
    printf("Pixel_height:\n");
    line = get_next_line_nl(0, 0);
    if (!line)
        return (printf("Error: getting line\n"), 1);
    img->pixel_height = ft_atoi(line);
    free(line);
    if (img->pixel_height < 600 || img->pixel_height > 4000)
        img->pixel_height = 600;
    printf("near_plane:\n");
    line = get_next_line_nl(0, 0);
    if (!line)
        return (printf("Error: getting line\n"), 1);
    img->near_plane = ft_atoi(line);
    free(line);
    if (img->near_plane < 0.2)
        img->near_plane = 0.2;
    printf("far_plane:\n");
    line = get_next_line_nl(0, 0);
    if (!line)
        return (printf("Error: getting line\n"), 1);
    img->far_plane = ft_atoi(line);
    free(line);
    if (img->far_plane < img->near_plane)
        img->far_plane = img->near_plane + 0.2;
    printf("ratio (16:9):\n");
    line = get_next_line_nl(0, 0);
    if (!line)
        return (printf("Error: getting line\n"), 1);
    if (!ft_strchr(line, ':') || ft_atoi(ft_strchr(line, ':') + 1) < 1 || ft_atoi(line) < 1)
        return (printf("Error: format line\n"), free(line), 1);
    img->ratio[0] = ft_atoi(line);
    img->ratio[1] = ft_atoi(ft_strchr(line, ':') + 1);
    free(line);
    return (0);
}

void     default_prop_performance(t_prop_performance *perf)
{
    perf->number_of_captures = 30;
    perf->level = 1;
    perf->flags[PERFORMA_O_REFRA] = 0;
    perf->flags[PERFORMA_O_DIFRA] = 0;
}

int     get_prop_performance(t_prop_performance *perf)
{
    char    *line;

    printf("Get_prop_performance\n");
    printf("Default config: (Y/N default N)\n");
    line = get_next_line_nl(0, 0);
    if (!line)
        return (printf("Error: getting line\n"), 1);
    if (!ft_strncmp("Y", line, 2))
        return (printf("Loaded default prop performance\n"), free(line), default_prop_performance(perf), 0);
    printf("Choose number of threads:\n");
    line = get_next_line_nl(0, 0);
    if (!line)
        return (printf("Error: getting line\n"), 1);
    perf->n_threads = ft_atoi(line);
    free(line);
    if (perf->n_threads < 2)
        perf->n_threads = 2;
    printf("Number of captures:\n");
    line = get_next_line_nl(0, 0);
    if (!line)
        return (printf("Error: getting line\n"), 1);
    perf->number_of_captures = ft_atoi(line);
    free(line);
    if (perf->number_of_captures < 3)
        perf->number_of_captures = 3;
    printf("Number of light bounces:\n");
    line = get_next_line_nl(0, 0);
    if (!line)
        return (printf("Error: getting line\n"), 1);
    perf->level = ft_atoi(line);
    free(line);
    if (perf->level < 1)
        perf->level = 1;
    perf->flags[PERFORMA_O_REFRA] = 0;
    perf->flags[PERFORMA_O_DIFRA] = 0;
    printf("Object transparency activates: (Y/N default N)\n");
        line = get_next_line_nl(0, 0);
    if (!line)
        return (printf("Error: getting line\n"), 1);
    if (!ft_strncmp("Y", line, 2))
        perf->flags[PERFORMA_O_DIFRA] = 1;
    printf("Object refraction activates: (Y/N default N)\n");
    line = get_next_line_nl(0, 0);
    if (!line)
        return (printf("Error: getting line\n"), 1);
    if (!ft_strncmp("Y", line, 2))
        perf->flags[PERFORMA_O_REFRA] = 1;

    return (0);
}

void    default_prop_output(t_prop_output *output)
{
    output->file = ft_strdup("output");
    output->format = OUTPUT_RT;
}

int     get_prop_output(t_prop_output *output)
{
    char    *line;

    printf("Get_prop_output\n");
    printf("Default config: (Y/N default N)\n");
    line = get_next_line_nl(0, 0);
    if (!line)
        return (printf("Error: getting line\n"), 1);
    if (!ft_strncmp("Y", line, 2))
        return (printf("Loaded default prop output\n"), free(line), 0);
    printf("Choose format:\n\tbipmap\n\trt\n\n");
    line = get_next_line_nl(0, 0);
    if (!ft_strncmp(line, "rt", 3))
        output->format = OUTPUT_RT;
    else if (!ft_strncmp(line, "bipmap", 7))
        output->format = OUTPUT_BIPMAP;
    else
        return (printf("Error: unknown format\n"), free(line), 1);
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
    if (get_prop_performance(&(*render)->prop_perf))
        return (printf("Error: prop_perfomance\n"), free(*render), 1);
    if (get_prop_output(&(*render)->prop_out))
        return (printf("Error: prop_output\n"), free(*render), 1);
    return (0);
}

void    print_render(t_render *render)
{
    int i;

    printf("Printing render %p\n", render);
    printf("Printing prop image\n");
    printf("\tfar_plane\t%0.3f\n", render->prop_img.far_plane);
    printf("\tnear_plane\t%0.3f\n", render->prop_img.near_plane);
    printf("\tpixel HxW\t%ux%u\n", render->prop_img.pixel_height, render->prop_img.pixel_witdh);
    printf("\tratio \t%u:%u\n\n", render->prop_img.ratio[0], render->prop_img.ratio[1]);
    printf("Printing prop performance\n");
    printf("\tn_threads\t%u\n", render->prop_perf.n_threads);    
    printf("\tnumber_of_captures\t%u\n", render->prop_perf.number_of_captures);    
    printf("\tlevel\t%u\n", render->prop_perf.level);    
    printf("\tFlags\n");
    i = -1;
    while (++i < PERFORMA_N)
        printf("\t\tflags[%u]\t%u\n", render->prop_perf.flags[i]);    
    printf("\nPrinting prop output\n");
    printf("\tformat\t%u\n", render->prop_out.format);    
    printf("\tfile\t%s\n\n", render->prop_out.file);
}

//Copy lights, objects and single
//launch render
//Create list of tasks
//if preview
//  launch  mlx thread
//launch tasks threads
//wait to finish
//save to file