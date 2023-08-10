#include "../../inc/miniRT.h"

int		get_cmd(char *line)
{
	if (!line)
		return (0);
	else if (!ft_strncmp(line, "exit", 5))
		return (EX_EXIT);
	return (0);
}

void	print_rt(t_rt *rt)
{
	printf("Printing rt struct %p\n", rt);
}

void	set_up_exec(int (*exec[EX_N])(t_rt *rt))
{
	exec[EX_ERROR] = NULL;
	exec[EX_ADD] = NULL;
	exec[EX_EDIT] = NULL;
	exec[EX_DELETE] = NULL;
	exec[EX_EXIT] = rt_exit;
	exec[EX_HELP] = NULL;
}

void menu_start(t_rt * rt)
{
    char    *line;
    short   cmd;
    int		(*exec_cmd[EX_N])(t_rt *rt);

    set_up_exec(exec_cmd);
    while (1)
    {
	    print_rt(rt);
	    line = get_next_line(0);
		if (line)
			line[ft_strlen(line) - 1] = 0;
	    cmd = get_cmd(line);
	    if (line)
		    free(line);
	    if (!exec_cmd[cmd])
			printf("Not implemented %d\n", cmd);
		else if (!exec_cmd[cmd](rt))
			printf("Error\n");
    }
}