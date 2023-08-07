#include    "../inc/miniRT.h"

int main(int argc, char **args)
{
    t_rt    *rt;
    char    *line;
    short   cmd;
    int		(*exec_cmd[6])(t_rt *rt);

    if (argc == 2)
        rt = open_rt_file(args[1]);
    else
        return (help_use(), 1);
    if (!rt)
	return (1);
    set_up_exec(exec_cmd);
    while (1)
    {
	    print_rt(rt);
	    line = get_next_line(0);
	    cmd = get_cmd(line);
	    if (line)
		    free(line);
	    if (!exec_cmd[i](rt))
		    return (0);
    }
    return (0);
}
