#ifndef STRUCTS_H
# define STRUCTS_H

# include "miniRT.h"

//Number type
typedef double  nType;
//Color type
typedef unsigned char    cType[3];

typedef struct s_td_point
{
    nType x;
    nType y;
    nType z;
}   t_td_point;

//Objetos

typedef struct s_obj_properties
{
    cType       color;
    nType       transparency;
    nType       reflexction;
    nType       density;
}   t_obj_properties;

# define OBJ_NULL 0
# define OBJ_TRI 1

typedef struct s_td_triangle
{
    t_td_point          a;
    t_td_point          b;
    t_td_point          c;
    t_obj_properties    *prop;
}   t_td_triangle;

# define OBJ_SPH 2

typedef struct s_sphere
{
    t_td_point          center;
    nType               radius;
    t_obj_properties    *prop;
} t_sphere;

# define OBJ_PLA 3

typedef struct s_plane
{
    t_td_point          center;
    t_td_point          normal;
    t_obj_properties    *prop;
} t_plane;

# define OBJ_BOX 4

typedef struct s_box
{
    t_td_point          center;
    t_td_point          normal;
    nType               height;
    nType               width;
    nType               length;
    t_obj_properties    *prop;
} t_box;

# define OBJ_CIL 5

typedef struct s_cilinder
{
    t_td_point          center;
    t_td_point          normal;
    nType               height;
    nType               width;
    t_obj_properties    *prop;
} t_cilinder;

# define OBJ_CON 6

typedef struct s_cone
{
    t_td_point          vertex;
    t_td_point          normal;
    nType               height;
    nType               angle;
    t_obj_properties    *prop;
} t_cone;

//Lights

# define OBJ_AL 7

typedef struct s_ambient_light
{
    cType   color;
    nType   ratio;
} t_ambient_light;

# define OBJ_LI 8

typedef struct s_light
{
    cType       color;
    nType       ratio;
    t_td_point  center;
} t_light;

//Camera

# define OBJ_C 9
# define OBJ_N 10

typedef struct s_camera
{
    t_td_point  vertex;
    t_td_point  normal;
    nType       fov;
}   t_camera;

//List container

typedef struct s_tuple
{
    char    fixed;
    int     type;
    char    *key;
    void    *content;
}   t_tuple;

//Renders

typedef struct s_mlx
{
    void    *addr;
}   t_mlx;

typedef struct s_prop_image
{
    unsigned    pixel_witdh;
    unsigned    pixel_height;
    nType       far_near;
    nType       far_plane;
    unsigned    ratio[2];
}   t_prop_image;

# define    PERFORMA_L_BOUNCES  0
# define    PERFORMA_N_DIFRA    1
# define    PERFORMA_N  2

typedef struct s_prop_performance
{
    unsigned    n_threads;
    unsigned    number_of_captures;
    unsigned    level;
    unsigned    flags[PERFORMA_N];
}   t_prop_performance;

# define    OUTPUT_BIPMAP   0
# define    OUTPUT_RT       1
# define    OUTPUT_FORMATS  2

typedef struct s_prop_output
{
    unsigned    format;
    char        *file;
}   t_prop_output;

typedef struct s_render
{
    t_mlx               mlx;
    t_camera            *cam;
    t_list              *lights;
    t_list              *objs;
    t_prop_image        prop_img;
    t_prop_performance   prop_perf;
    t_prop_output       prop_out;
}   t_render;

//RT

typedef struct s_rt
{
    t_list  *cameras;
    t_list  *lights;
    t_list  *objs;
    t_list  *renders;
    char    *file;
}   t_rt;

#endif
