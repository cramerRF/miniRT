#ifndef MINIRT_H
# define MINIRT_H

# define EX_ERROR   0
# define EX_ADD     1
# define EX_EDIT    2
# define EX_DELETE  3
# define EX_EXIT    4
# define EX_HELP    5
# define EX_LIST    7
# define EX_N       8

# include "../lib/libft/libft.h"
# include "../lib/gnl/get_next_line_bonus.h"
# include "./structs.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

/* src */
//gnl_utils
char	*get_next_line_nl(int fd, int flag);
//input_utils.c
nType       get_number(char *name, nType min, nType max);
t_td_point  get_point(char *name, nType norme);
//file_parser.c
t_rt	    *open_rt_file(char *name_file);

/* src/menu */
//menu
void        menu_start(t_rt * rt);
//exit
void        free_objs(void *obj);
int 		rt_exit(t_rt *rt);
//add
int 		rt_add(t_rt *rt);
//list
int         rt_list(t_rt *rt);

/* src/objs */

//camera
t_tuple     *add_camera(void);
void        print_camera(t_tuple *obj);
void        free_camera(t_tuple *cam);

/* src/light */

#endif