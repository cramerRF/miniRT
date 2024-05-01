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
# include <pthread.h>
# define RT_LINUX_COMPI 1 
/* NAME_MACOS */
# ifdef RT_MACOS_COMPI
#  define KEY_ESC   53
#  define KEY_Q     12
#  include "../lib/minilibx_macos/mlx.h"
# endif
/* NAME_LINUX */
# ifdef RT_LINUX_COMPI
#  define KEY_ESC   65307
#  define KEY_Q     113
#  define _GNU_SOURCE
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
char	    *get_next_line_nl(int fd, int flag);
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
void *menu_start(void *arg);
//exit
void        free_objs(void *obj);
int 		rt_exit(t_rt *rt);
t_rt        **get_rt_addr(t_rt **nuw);
void        search_obj_key(t_list *lst, t_tuple **ret, char *key);

//add
int 		rt_add(t_rt *rt);
//list
int         rt_list(t_rt *rt);
void        print_objs(void *arg);
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

//properties
int                 parse_properties(t_obj_properties *prop, char *line);
t_obj_properties    *malloc_properties();
void                write_properties(int fd, t_obj_properties  *prop);
void                edit_prop(t_obj_properties *prop);
void                print_properties(t_obj_properties   *prop);

//sphere
t_tuple     *add_sphere(void);
void        print_sphere(t_tuple *obj);
void        edit_sphere(t_tuple *obj);
void        free_sphere(t_tuple *cam);
void        write_sphere(t_tuple *obj);
t_tuple     *read_sphere(char *line);

//plane
t_tuple     *add_plane(void);
void        print_plane(t_tuple *obj);
void        edit_plane(t_tuple *obj);
void        free_plane(t_tuple *cam);
void        write_plane(t_tuple *obj);
t_tuple     *read_plane(char *line);

//triangle
t_tuple     *add_triangle(void);
void        print_triangle(t_tuple *obj);
void        edit_triangle(t_tuple *obj);
void        free_triangle(t_tuple *cam);
void        write_triangle(t_tuple *obj);
t_tuple     *read_triangle(char *line);

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

//light
t_tuple     *add_light(void);
void        print_light(t_tuple *obj);
void        edit_light(t_tuple *obj);
void        free_light(t_tuple *cam);
void        write_light(t_tuple *obj);
t_tuple     *read_light(char *line);

/* src/render */
//init
void    print_render(t_render *render);
void    copy_scene_to_render(t_rt *rt);
int    render_get_options(t_rt *rt, t_render **render);

//add
int    rt_render_add(t_rt *rt);
int rt_loop(t_rt *rt);

//edit
int    rt_render_edit(t_rt *rt);

//free
void    rt_render_free(void *arg);

//menu
int rt_render(t_rt *rt);

//update
int    rt_render_update(t_rt *rt);
int rt_init_mlx(t_rt *rt, t_render *render);

//objs/sphere.c
int         inter_sphere(void *obj, t_ray *ray, t_td_point **arr);
t_td_point  normal_sphere(void *obj, t_ray *ray, t_td_point *point);

//objs/plane.c
int         inter_plane(void *obj, t_ray *ray, t_td_point **arr);
t_td_point  normal_plane(void *obj, t_ray *ray, t_td_point *point);

//objs/triangle.c
int         inter_triangle(void *obj, t_ray *ray, t_td_point **arr);
t_td_point  normal_triangle(void *obj, t_ray *ray, t_td_point *point);

/* src/3dmath */
//utils1
nType       distance(t_td_point a, t_td_point b);
nType       absolute(nType k);
nType       module(t_td_point v);
t_td_point  normalize(t_td_point v);
t_td_point  cross_product(t_td_point v, t_td_point u);
nType       dot_product(t_td_point v, t_td_point u);
t_td_point  scalar_product(t_td_point v, nType k);
void        print_td_point(char *msg, t_td_point p);
t_td_point sum_vector(t_td_point v, t_td_point u);



#endif
