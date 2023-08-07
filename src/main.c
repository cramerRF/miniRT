#include    "../inc/miniRT.h"

t_rt	*open_rt_file(char *name_file)
{
	t_rt	*ret;

	ret = malloc(sizeof(t_rt));
	if (!ret)
		return (NULL);
	ft_bzero(ret, sizeof(t_rt));
	ret->file = ft_strdup(name_file);
	return (ret);
}

void	help_use()
{
	printf("./miniRT (.rt file)\nOnly one argument\nFile must be format like generated\n\n");
}

void	set_up_exec(int (*exec[6])(t_rt *rt))
{
	exec[EX_ERROR] = NULL;
	exec[EX_ADD] = NULL;
	exec[EX_EDIT] = NULL;
	exec[EX_DELETE] = NULL;
	exec[EX_EXIT] = NULL;
	exec[EX_HELP] = NULL;
}

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
