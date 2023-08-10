#include    "../inc/miniRT.h"

static int		get_obj_type(char *line)
{
	line++;
	return (0);
}

static void	setup_parser(int 	(*parser[OBJ_N])(t_rt *rt, char *line))
{
	parser[OBJ_NULL] = NULL;
	parser[OBJ_TRI] = NULL;
	parser[OBJ_SPH] = NULL;
	parser[OBJ_PLA] = NULL;
	parser[OBJ_BOX] = NULL;
	parser[OBJ_CIL] = NULL;
	parser[OBJ_CON] = NULL;
	parser[OBJ_AL] = NULL;
	parser[OBJ_LI] = NULL;
	parser[OBJ_C] = NULL;
}

static int		read_rt_file(t_rt *rt)
{
	int		fd;
	int		i;
	int		type;
	char	*line;
	int 	(*parser[OBJ_N])(t_rt *rt, char *line);

	i = 0;
	setup_parser(parser);
	fd = open(rt->file, O_RDONLY, 0600);
	if (fd == -1)
		return (printf("Can not open the file '%s'\n", rt->file), 1);
	line = get_next_line(fd);
	while (line)
	{
		i++;
		type = get_obj_type(line);
		if (!parser[type])
			printf("Type not implemeted\n");
		else if (!parser[type](rt, line))
			return (free(line), printf("Error in line %d ->%s<-", i, line), 1);
		free(line);
		line = get_next_line(fd);
	}	
	return (0);
}

t_rt	*open_rt_file(char *name_file)
{
	t_rt	*ret;

	ret = malloc(sizeof(t_rt));
	if (!ret)
		return (NULL);
	ft_bzero(ret, sizeof(t_rt));
	printf("opening %s\n", name_file);
	ret->file = ft_strdup(name_file);
	if (!ret->file)
		return (printf("ft_strdup failed\n"), NULL);
	if (read_rt_file(ret))
		return (free(ret->file), free(ret), NULL);
	return (ret);
}
