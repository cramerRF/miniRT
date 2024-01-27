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
	menu_start(rt);
#ifdef  RT_MACOS_COMPI
    system("leaks miniRT");
#endif
	printf(">>>>>>>>Shoudnt be printing this<<<<<<<<<<<\n\n");
    return (0);
}
