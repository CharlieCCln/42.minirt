/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:40:10 by ccrottie          #+#    #+#             */
/*   Updated: 2023/09/26 18:41:05 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define _USE_MATH_DEFINES
# include <math.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdlib.h> // malloc, free, exit
# include <fcntl.h> // open
# include <unistd.h> // read, write, close
# include <stdio.h> // perror, printf
# include <limits.h>
# include <stdbool.h>
# include "float.h"

# define KEY_ESC 65307
# define WIDTH 1280
# define HEIGHT 720
# define X 0
# define Y 1
# define Z 2
# define EPSILON 0.00001

typedef enum e_type
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_type;

typedef enum e_oper
{
	ADD,
	SUB,
	CROSS,
}	t_oper;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*win_name;
	char	*addr;
	int		bpp;
	int		len;
	int		end;
}	t_mlx;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
	int			hex;
}	t_color;

typedef struct s_coords
{
	double		x;
	double		y;
	double		z;
}	t_coords;

typedef struct s_ambient
{
	double		intensity;
	t_color		color;
}	t_ambient;

typedef struct s_cam
{
	t_coords	origin;
	t_coords	dir;
	t_coords	dir_norm;
	t_coords	hor_fov;
	t_coords	ver_fov;
	t_coords	ll_corner;
	int			fov;
}	t_cam;

typedef struct s_light
{
	t_coords	origin;
	double		intensity;
}	t_light;

typedef struct s_object
{
	t_type		type;
	t_coords	origin;
	t_coords	dir;
	t_color		color;
	double		diameter;
	double		height;
	t_coords		pos;
	t_coords		pos2;
}	t_object;

typedef struct s_data
{
	t_mlx		mlx;
	t_ambient	ambient;
	t_cam		cam;
	t_light		light;
	t_object	*objects;
	int			obj_nbr;
	int			fd;
}	t_data;

typedef struct s_ray
{
	t_coords	origin;
	t_coords	dir;
	t_coords	dir_norm;
	double		dist;
	t_coords	hit;
	t_coords	hit_norm;
	t_color		color;
	int			inside;
}	t_ray;

// events.c
void		print_error(char *msg);
int			key_press(int keycode, t_data *data);
int			call_terminate(t_data *data);

// ----- DRAWING -----

// drawing/camera.c
void		set_camera(t_cam *cam);

// drawing/color_utils.c
int			color_add(int c1, int c2);
int			color_scale(int color, double intensity);
int			color_product(int color1, int color2);

// drawing/cylinder.c
int			intersect_cylinder(t_ray *ray, t_object *cylinder);

// drawing/drawing.c
void		drawing(t_data *data);

// drawing/light.c
int			add_light(t_data *data, t_ray *ray);
int			check_shadow(t_data *data, t_ray *ray);

// drawing/pixel_put.c
void		pixel_put(t_mlx *mlx, int x, int y, int color);

// drawing/plane.c
int			intersect_plane(t_ray *ray, t_object *plane, int mode);

// drawing/ray.c
int			find_intersect(t_data *data, t_ray *ray, int mode);
t_ray		create_ray(t_cam cam, double x, double y);
int			get_ray_color(t_data *data, t_ray *ray);
t_coords	get_hit_point(t_ray *ray);

// drawing/sphere.c
int			intersect_sphere(t_ray *ray, t_object *sphere, int mode);

// drawing/vectors.c
t_coords	v_norm(t_coords v);
t_coords	v_scale(t_coords v, double scale);
double		v_dot(t_coords v, t_coords u);
double		v_square(t_coords v);
t_coords	v_oper(t_oper mode, t_coords v, t_coords u);

// ----- PARSING -----

// parsing/parsing_hub.c
void		parsing_hub(t_data *data, char *filename);

// parsing/elements/parse_ambient.c
int			parse_ambient(t_data *data, char **content);

// parsing/elements/parse_camera.c
int			parse_camera(t_data *data, char **content);

// parsing/elements/parse_cylinder.c
int			parse_cylinder(t_data *data, char **content);

// parsing/elements/parse_light.c
int			parse_light(t_data *data, char **content);

// parsing/elements/parse_object.c
int			parse_object(t_data *data, char **content);

// parsing/elements/parse_plane.c
int			parse_plane(t_data *data, char **content);

// parsing/elements/parse_sphere.c
int			parse_sphere(t_data *data, char **content);

// parsing/utils/arg_check.c
int			arg_check(char *arg);

// parsing/utils/check_elements.c
void		check_elements(t_data *data, char *filename);

// parsing/utils/get_double_value.c
int			get_double_value(double *value, char *content);

// parsing/utils/gnl_safe.c
char		*gnl_safe(t_data *data, int fd);

// parsing/utils/open_infile.c
int			open_infile(t_data *data, char *filename);

// parsing/utils/parse_color.c
int			parse_color(t_color *color, char *content);

// parsing/utils/parse_coords.c
int			parse_coords(t_coords *coords, char *content);
int			parse_vector(t_coords *vector, char *content);

// parsing/utils/parse_filename.c
void		parse_filename(t_data *data, char *filename);

// parsing/utils/remove_endl.c
char		*remove_endl(char *line);

// ----- MEMORY -----

// memory/init.c
void		init_mlx(t_data *data);
void		bzero_everything(t_data *data);
void		allocate_objects(t_data *data, int *counts);

// memory/terminate.c
void		terminate(t_data *data);

#endif
