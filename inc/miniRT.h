#ifndef MINIRT_H
# define MINIRT_H
//colors
# define    COLOR_BLACK     "\x1b[30m"
# define    COLOR_RED       "\x1b[41m"
# define    COLOR_GREEN     "\x1b[32m"
# define    COLOR_YELLOW    "\x1b[33m"
# define    COLOR_BLUE      "\x1b[34m"
# define    COLOR_PURPLE    "\x1b[35m"
# define    COLOR_CYAN      "\x1b[36m"
# define    COLOR_CLEAN     "\x1b[0m\n"
# define    CLEAR_SCREEN    "\033c\n"

//menu cmds
# define EX_ERROR   0
# define EX_ADD     1
# define EX_EDIT    2
# define EX_DELETE  3
# define EX_EXIT    4
# define EX_HELP    5
# define EX_LIST    6
# define EX_SAVE    7
# define EX_LOAD    8
# define EX_RENDER  9
# define EX_N       10

# define MEM_CLEAR  0
# define MEM_WRITE  1
# define MEM_READ   2

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
int         line_to_point(char *line, t_td_point *p);
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
//edit
int         rt_edit(t_rt *rt);
void        *memory(int code, void *arg);
//save
int         rt_save(t_rt *rt);
//help
int 		rt_help(t_rt *rt);

/* src/objs */

//camera
t_tuple     *add_camera(void);
void        print_camera(t_tuple *obj);
void        edit_camera(t_tuple *obj);
void        free_camera(t_tuple *cam);
void        write_camera(t_tuple *obj);
t_tuple     *read_camera(char *line);
/* src/light */

#endif