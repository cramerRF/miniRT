#ifndef STRUCTS_H
# define STRUCTS_H

# include "miniRT.h"

//Number type
typedef double  nType;
//Color type
typedef char    cType[3];

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

typedef struct s_td_triangle
{
    t_td_point          x;
    t_td_point          y;
    t_td_point          z;
    t_obj_properties    *prop;
}   t_td_triangle;

typedef struct s_sphere
{
    t_td_point          center;
    nType               radius;
    t_obj_properties    *prop;
} t_sphere;

typedef struct s_plane
{
    t_td_point          center;
    t_td_point          normal;
    t_obj_properties    *prop;
} t_plane;

typedef struct s_box
{
    t_td_point          center;
    t_td_point          normal;
    nType               height;
    nType               width;
    nType               length;
    t_obj_properties    *prop;
} t_box;

typedef struct s_cilinder
{
    t_td_point          center;
    t_td_point          normal;
    nType               height;
    nType               width;
    t_obj_properties    *prop;
} t_cilinder;

typedef struct s_cone
{
    t_td_point          vertex;
    t_td_point          normal;
    nType               height;
    nType               angle;
    t_obj_properties    *prop;
} t_cone;

typedef struct s_parabola
{
    t_cone              cone;
    t_plane             plane;
    t_obj_properties    *prop;
} t_parabola;

//Lights

typedef struct s_ambient_light
{
    cType   color;
    nType   ratio;
} t_ambient_light;

typedef struct s_light
{
    cType       color;
    nType       ratio;
    t_td_point  center;
} t_light;

//Camera

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
