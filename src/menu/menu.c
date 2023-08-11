#include "../../inc/miniRT.h"

int		get_cmd(char *line)
{
	if (!line)
		return (0);
	else if (!ft_strncmp(line, "add", 4))
		return (EX_ADD);
	else if (!ft_strncmp(line, "edit", 5))
		return (EX_EDIT);
	else if (!ft_strncmp(line, "delete", 7))
		return (EX_DELETE);
	else if (!ft_strncmp(line, "exit", 5))
		return (EX_EXIT);
	else if (!ft_strncmp(line, "help", 5))
		return (EX_HELP);
	else if (!ft_strncmp(line, "list", 5) || !ft_strncmp(line, "ls", 3))
		return (EX_LIST);
	else if (!ft_strncmp(line, "save", 5) || !ft_strncmp(line, "s", 2))
		return (EX_SAVE);
	else if (!ft_strncmp(line, "load", 5))
		return (EX_LOAD);
	return (0);
}

void	print_rt(t_rt *rt)
{
	printf("Printing rt struct %p\n", rt);
}

void	set_up_exec(int (*exec[EX_N])(t_rt *rt))
{
	exec[EX_ERROR] = NULL;
	exec[EX_ADD] = rt_add;
	exec[EX_EDIT] = rt_edit;
	exec[EX_DELETE] = NULL;
	exec[EX_EXIT] = rt_exit;
	exec[EX_HELP] = NULL;
	exec[EX_LIST] = rt_list;
	exec[EX_SAVE] = rt_save;
	exec[EX_LOAD] = NULL;
}

void menu_start(t_rt * rt)
{
    char    *line;
    short   cmd;
    static int		(*exec_cmd[EX_N])(t_rt *rt);

    if (!exec_cmd[EX_EXIT])
    	set_up_exec(exec_cmd);
    while (1)
    {
	    print_rt(rt);
	    line = get_next_line_nl(0, 0);
	    cmd = get_cmd(line);
	    if (line)
		    free(line);
	    if (!exec_cmd[cmd])
			printf("Not implemented %d\n", cmd);
		else if (exec_cmd[cmd](rt))
			printf("Error\n");
		printf("End\n");
    }
}