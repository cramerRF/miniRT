#include    "../inc/miniRT.h"

int		rt_is_upper(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] < 'A' || line[i] > 'Z')
			return (0);
	}
	return (1);
}

static int		get_obj_type(char *line)
{
	printf("%s\n", line);
	if (!line)
		return (0);
	else if (!ft_strncmp(line, "C ", 2) || !ft_strncmp(line, "c ", 2))
		return (OBJ_C);
	else if (!ft_strncmp(line, "A ", 2) || !ft_strncmp(line, "a ", 2))
		return (OBJ_AL);
	return (0);
}

static void	setup_parser(t_tuple 	*(*parser[OBJ_N])(char *))
{
	parser[OBJ_NULL] = NULL;
	parser[OBJ_TRI] = NULL;
	parser[OBJ_SPH] = NULL;
	parser[OBJ_PLA] = NULL;
	parser[OBJ_BOX] = NULL;
	parser[OBJ_CIL] = NULL;
	parser[OBJ_CON] = NULL;
	parser[OBJ_AL] = read_ambient_light;
	parser[OBJ_LI] = NULL;
	parser[OBJ_C] = read_camera;
}

static int		read_rt_file(t_rt *rt)
{
	int		fd;
	int		type;
	char	*line;
	static t_tuple 	*(*parser[OBJ_N])(char *line);
	t_tuple		*obj;
	t_list		*lst;

	if (!parser[OBJ_C])
		setup_parser(parser);
	fd = open(rt->file, O_RDONLY, 0644);
	if (fd == -1)
		return (printf("Can not open the file '%s'\n", rt->file), 1);
	line = get_next_line_nl(fd, 0);
	while (line)
	{
		if (line[0] == '#')
		{
			free(line);
			line = get_next_line_nl(fd, 0);
			continue ;
		}
		type = get_obj_type(line);
		if (!parser[type])
			printf("Type not implemeted\n");
		else
		{
			obj = parser[type](line);
			if (obj)
			{
				int	flags[1];

				*flags = rt_check_fixed_identifier(rt, obj->key, obj->type); 
				if ((obj->fixed && TestBit(flags, CHECK_EXISTS_TYPE)) || TestBit(flags, CHECK_FIX) || TestBit(flags, CHECK_KEY))
    			    return(free_objs(obj), printf("Error concurrency\n"), 1);
				lst = ft_lstnew(obj);
    			if (!lst)
    			    return(free_objs(obj), printf("Error creating list\n"), 1);
    			if (obj->type == OBJ_C)
    			    ft_lstadd_back(&rt->cameras, lst);
    			else if (obj->type == OBJ_LI || obj->type == OBJ_AL)
    			    ft_lstadd_back(&rt->lights, lst);
    			else if (obj->type != OBJ_NULL)
    			    ft_lstadd_back(&rt->objs, lst);
    			else
    			    return(free_objs(obj), free(lst), printf("Unknown obj type\n"), 1);
			}

		}

		free(line);
		line = get_next_line_nl(fd, 0);
	}
	close(fd);
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
