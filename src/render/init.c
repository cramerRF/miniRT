#include "../../inc/miniRT.h"

//Get options
void    default_prop_image(t_prop_image *img)
{
    img->far_plane = 100;
    img->near_plane = 0.1;
    img->pixel_height = 720;
    img->pixel_witdh = 1080;
    img->ratio[0] = 16;
    img->ratio[1] = 9;
}

int     get_prop_image(t_prop_image *img)
{
    char    *line;

    printf("Get_prop_image\n");
    printf("Default config: (Y/N default Y)\n");
    line = get_next_line_nl(0, 0);
    if (!line)
        return (printf("Error: getting line\n"), 1);
    if (ft_strncmp("N", line, 2))
        return (printf("Loaded default prop image\n"), free(line), default_prop_image(img), 0);
    free(line);
    printf("Pixel_witdh:\n");
    line = get_next_line_nl(0, 0);
    if (!line)
        return (printf("Error: getting line\n"), 1);
    img->pixel_witdh = ft_atoi(line);
    free(line);
    if (img->pixel_witdh < 480 || img->pixel_witdh > 4000)
        img->pixel_witdh = 480;
    printf("Pixel_height:\n");
    line = get_next_line_nl(0, 0);
    if (!line)
        return (printf("Error: getting line\n"), 1);
    img->pixel_height = ft_atoi(line);
    free(line);
    if (img->pixel_height < 480 || img->pixel_witdh > 4000)
        img->pixel_height = 480;
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
    perf->n_threads = 2;
    perf->flags[PERFORMA_O_REFRA] = 0;
    perf->flags[PERFORMA_O_DIFRA] = 0;
}

int     get_prop_performance(t_prop_performance *perf)
{
    char    *line;

    printf("Get_prop_performance\n");
    printf("Default config: (Y/N default Y)\n");
    line = get_next_line_nl(0, 0);
    if (!line)
        return (printf("Error: getting line\n"), 1);
    if (ft_strncmp("N", line, 2))
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
    printf("Default config: (Y/N default Y)\n");
    line = get_next_line_nl(0, 0);
    if (!line)
        return (printf("Error: getting line\n"), 1);
    if (ft_strncmp("N", line, 2))
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
    printf("Malloc render %p\n", *render);
    ft_bzero(*render, sizeof(t_render));
    (*render)->rt = rt;
    printf("Get camera\n");
    printf("Give the identifier\n");
    line = get_next_line_nl(0, 0);
    if (!line)
        return (printf("Error: empty line\n"), free(*render), 1);
    obj = NULL;
    search_obj_key(rt->cameras, &obj, line);
    (*render)->name = line;
    if (!obj)
        return (printf("Camera nott found\n"), free((*render)->name), free(*render), 1);
    /*printf("AAAA\n");*/
    ft_memmove(&((*render)->cam), obj->content, sizeof(t_camera));
    /*printf("BBBB\n");*/
    if (get_prop_image(&(*render)->prop_img))
        return (printf("Error: prop_image\n"), free((*render)->name), free(*render), 1);
    if (get_prop_performance(&(*render)->prop_perf))
        return (printf("Error: prop_perfomance\n"), free((*render)->name), free(*render), 1);
    if (get_prop_output(&(*render)->prop_out))
        return (printf("Error: prop_output\n"), free((*render)->name), free(*render), 1);
    return (0);
}

//print render

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
        printf("\t\tflags[%u]\t%u\n", i, render->prop_perf.flags[i]);    
    printf("\nPrinting prop output\n");
    printf("\tformat\t%u\n", render->prop_out.format);    
    printf("\tfile\t%s\n\n", render->prop_out.file);
    printf("\nPrinting mlx\n");
    printf("\twin\t%p\n", render->mlx.win);
    printf("\timg\t%p\n", render->mlx.img);
    printf("\taddr\t%p\n", render->mlx.addr);
    printf("\tbits_per_pixel\t%d\n", render->mlx.bits_per_pixel);
    printf("\tline_length\t%d\n", render->mlx.line_length);
    printf("\tendian\t%d\n", render->mlx.endian);
    printf("\nPrinting camera\n");
    printf("\tvertex\t%0.3f %0.3f %0.3f\n", render->cam.vertex.x, render->cam.vertex.y, render->cam.vertex.z);
    printf("\tnormal\t%0.3f %0.3f %0.3f\n", render->cam.normal.x, render->cam.normal.y, render->cam.normal.z);
    printf("\tfov\t%0.3f\n", render->cam.fov);
    printf("\nPrinting name\n");
    printf("\tname\t%s\n", render->name);



}

//Copy lights, objects and single
void    setup_size_mem(int size_mem[OBJ_N])
{
    size_mem[OBJ_NULL] = 0;
    size_mem[OBJ_TRI] = sizeof(t_td_triangle);
    size_mem[OBJ_SPH] = sizeof(t_sphere);
    size_mem[OBJ_PLA] = sizeof(t_plane);
    size_mem[OBJ_BOX] = sizeof(t_box);
    size_mem[OBJ_CIL] = sizeof(t_cilinder);
    size_mem[OBJ_CON] = sizeof(t_cone);
    size_mem[OBJ_AL] = sizeof(t_ambient_light);
    size_mem[OBJ_LI] = sizeof(t_light);
    size_mem[OBJ_C] = sizeof(t_camera);
}


void *copy_object(void *content)
{
    t_tuple *original;
    static int     size_mem[OBJ_N];
    t_tuple *ret;

    if (!size_mem[OBJ_C])
        setup_size_mem(size_mem);
    original = content;
    ret = malloc(sizeof(t_tuple));
    if (!ret)
        return (printf("Error: mallocing t_tuple\n"), NULL);
    ft_bzero(ret, sizeof(t_tuple));
    if (original->type == OBJ_C || original->type == OBJ_LI || original->type == OBJ_AL)
    {
        ret->type = original->type;
        ret->content = malloc(size_mem[original->type]);
        if (!ret->content)
            return (printf("Error: mallocing \n"), free(ret), NULL);
        ft_memmove(ret->content, original->content, size_mem[original->type]);
    }
    else if (original->type && original->type < OBJ_AL)
    {
        ret->type = original->type;
        ret->content = malloc(size_mem[original->type]);
        if (!ret->content)
            return (printf("Error: mallocing \n"), free(ret), NULL);
        ft_memmove(ret->content, original->content, size_mem[original->type]);
        if (original->type == OBJ_TRI)
        {
            ((t_td_triangle *) ret->content)->prop = malloc(sizeof(t_obj_properties));
            if (!((t_td_triangle *) ret->content)->prop)
                return (free(ret->content), free(ret), NULL);
            ft_memmove(((t_td_triangle *) ret->content)->prop, ((t_td_triangle *) original->content)->prop, sizeof(t_obj_properties));
        }
        else if (original->type == OBJ_SPH)
        {
            ((t_sphere *) ret->content)->prop = malloc(sizeof(t_obj_properties));
            if (!((t_sphere *) ret->content)->prop)
                return (free(ret->content), free(ret), NULL);
            ft_memmove(((t_sphere *) ret->content)->prop, ((t_sphere *) original->content)->prop, sizeof(t_obj_properties));
        }
        else if (original->type == OBJ_PLA)
        {
            ((t_plane *) ret->content)->prop = malloc(sizeof(t_obj_properties));
            if (!((t_plane *) ret->content)->prop)
                return (free(ret->content), free(ret), NULL);
            printf("copying original tuple %p\n", original);
            printf("copying original plane %p\n", ((t_plane *) original->content));
            printf("copying original prop %p\n", ((t_plane *) original->content)->prop);
            ft_memmove(((t_plane *) ret->content)->prop, ((t_plane *) original->content)->prop, sizeof(t_obj_properties));
            printf("copying ret tuple %p\n", ret);
            printf("copying ret plane %p\n", ((t_plane *) ret->content));
            printf("copying ret prop %p\n", ((t_plane *) ret->content)->prop);
        }
        else if (original->type == OBJ_BOX)
        {
            ((t_box *) ret->content)->prop = malloc(sizeof(t_obj_properties));
            if (!((t_box *) ret->content)->prop)
                return (free(ret->content), free(ret), NULL);
            ft_memmove(((t_box *) ret->content)->prop, ((t_box *) original->content)->prop, sizeof(t_obj_properties));
        }
        else if (original->type == OBJ_CIL)
        {
            ((t_cilinder *) ret->content)->prop = malloc(sizeof(t_obj_properties));
            if (!((t_cilinder *) ret->content)->prop)
                return (free(ret->content), free(ret), NULL);
            ft_memmove(((t_cilinder *) ret->content)->prop, ((t_cilinder *) original->content)->prop, sizeof(t_obj_properties));
        }
        else if (original->type == OBJ_CON)
        {
            ((t_cone *) ret->content)->prop = malloc(sizeof(t_obj_properties));
            if (!((t_cone *) ret->content)->prop)
                return (free(ret->content), free(ret), NULL);
            ft_memmove(((t_cone *) ret->content)->prop, ((t_cone *) original->content)->prop, sizeof(t_obj_properties));
        }
        else
            return (free(ret->content), free(ret), NULL);
    }
    else
        return (printf("Error: unknow object type"), NULL);
    return (ret);
}

void    copy_scene_to_render(t_rt *rt)
{
    if (rt->lights_render)
        ft_lstclear(&rt->lights_render, free_objs);
    rt->lights_render = ft_lstmap(rt->lights, copy_object, free_objs);
    if (rt->objs_render)
        ft_lstclear(&rt->objs_render, free_objs);
    rt->objs_render = ft_lstmap(rt->objs, copy_object, free_objs);
}

//launch render
//Create list of tasks
//if preview
//  launch  mlx thread
//launch tasks threads
//wait to finish
//save to file
