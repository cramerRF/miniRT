#ifndef MINIRT_H
# define MINIRT_H
// Due order of operation wrap 'k' in parentheses in case it
// is passed as an equation, e.g. i + 1, otherwise the first
// part evaluates to "A[i + (1/32)]" not "A[(i + 1)/32]"
#define SetBit(A,k)     ( A[(k)/32] |= (1 << ((k)%32)) )
#define ClearBit(A,k)   ( A[(k)/32] &= ~(1 << ((k)%32)) )
#define TestBit(A,k)    ( A[(k)/32] & (1 << ((k)%32)) )

//check add fixed key
#define CHECK_KEY   0
#define CHECK_FIX   1
#define CHECK_EXISTS_TYPE   2
#define CHECK_N     3

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
/* NAME_MACOS */
# ifdef RT_MACOS_COMPI
#  include "../lib/minilibx_macos/mlx.h"
# endif
/* NAME_LINUX */
# ifdef RT_LINUX_COMPI
#  include "../lib/minilibx_linux/mlx.h"
#  include "../lib/minilibx_linux/mlx_int.h"
# endif

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
void        get_color(char *name, cType color);
int         line_to_color(char *line, cType color);
//file_parser.c
t_rt	    *open_rt_file(char *name_file);
int 		rt_is_upper(char *line);

/* src/menu */
//menu
void        menu_start(t_rt * rt);
//exit
void        free_objs(void *obj);
int 		rt_exit(t_rt *rt);
t_rt        **get_rt_addr(t_rt **nuw);
void    search_obj_key(t_list *lst, t_tuple **ret, char *key);

//add
int 		rt_add(t_rt *rt);
//list
int         rt_list(t_rt *rt);
//edit
int         rt_edit(t_rt *rt);
void        *memory(int code, void *arg);
int         rt_check_fixed_identifier(t_rt *rt, char *key, int type);
//save
int         rt_save(t_rt *rt);
//laod
int         rt_load(t_rt *rt);
//help
int 		rt_help(t_rt *rt);
//delete
int 		rt_delete(t_rt *rt);

/* src/objs */

//camera
t_tuple     *add_camera(void);
void        print_camera(t_tuple *obj);
void        edit_camera(t_tuple *obj);
void        free_camera(t_tuple *cam);
void        write_camera(t_tuple *obj);
t_tuple     *read_camera(char *line);

/* src/light */

//ambient_light
t_tuple     *add_ambient_light(void);
void        print_ambient_light(t_tuple *obj);
void        edit_ambient_light(t_tuple *obj);
void        free_ambient_light(t_tuple *cam);
void        write_ambient_light(t_tuple *obj);
t_tuple     *read_ambient_light(char *line);
#endif