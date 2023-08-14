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
    t_td_point          x;
    t_td_point          y;
    t_td_point          z;
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

//Render

typedef struct s_render
{
    unsigned height;
    unsigned width;
    char     preview;
    unsigned refresh_ms;
    char     *file_output;
    char     *file_input;
}   t_render;

//List container

typedef struct s_tuple
{
    char    fixed;
    int     type;
    char    *key;
    void    *content;
}   t_tuple;

//RT

typedef struct s_rt
{
    t_list  *cameras;
    t_list  *lights;
    t_list  *objs;
    char    *file;
}   t_rt;

#endif
