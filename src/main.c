#include    "../inc/miniRT.h"

t_rt **get_rt_addr(t_rt **nuw)
{
    static t_rt **rt;

    if (nuw)
        rt = nuw;
    return (rt);
}

void	help_use()
{
	printf("./miniRT (.rt file)\nOnly one argument\nFile must be format like generated\n\n");
}

int main(int argc, char **args)
{
    t_rt    *rt;

    get_rt_addr(&rt);
    if (argc == 2 && !ft_strncmp(".rt", args[1] + (int) fmin(ft_strlen(args[1]), (unsigned) ft_strlen(args[1]) - 3), 4))
        rt = open_rt_file(args[1]);
    else
        return (help_use(), 1);
    if (!rt)
		return (1);
    rt->mlx = mlx_init();
    if (!rt->mlx)
        return (printf("Error: mlx_init\n"), 1);
    mlx_loop_hook(rt->mlx, rt_loop, rt); // Pass to main
    
    pthread_mutex_init(&rt->mutex, NULL);
	//menu_start(rt);
    pthread_create(&(rt->menu_thread), NULL, menu_start, rt);
    mlx_loop(rt->mlx);
    printf(">>>>>>>>Shoudnt be printing this<<<<<<<<<<<\n\n");
    pthread_join(rt->menu_thread, NULL);
#ifdef  RT_MACOS_COMPI
    //system("leaks miniRT");
#endif
	printf(">>>>>>>>Shoudnt be printing this<<<<<<<<<<<\n\n");
    return (0);
}
