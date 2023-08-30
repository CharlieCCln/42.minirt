/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:40:10 by ccrottie          #+#    #+#             */
/*   Updated: 2023/08/30 17:26:34 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#define _USE_MATH_DEFINES
# include <math.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdlib.h> // malloc, free, exit
# include <fcntl.h> // open
# include <unistd.h> // read, write, close
# include <stdio.h> // perror, printf
# include <limits.h>
# include <float.h>

# define M_PI 3.14159265358979332384626433832795028841971693993751058209749445923078164062862089986280348253421170679
# define KEY_ESC 65307
# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720
# define MENU_WIDTH 320

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*win_name;
	char	*addr;
	int		size_x;
	int		size_y;
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

typedef struct s_ambient
{
	double		intensity;
	t_color		color;
}	t_ambient;

typedef struct s_cam
{
	t_coords	coords;
	t_coords	vector;
	t_coords	normal;
	t_coords 	hor_fov;
	t_coords 	ver_fov;
	int fov;
}	t_cam;

typedef struct s_light
{
	t_coords	coords;
	double		intensity;
}	t_light;

typedef struct s_object
{
	t_type		type;
	t_coords	coords;
	t_coords	vector;
	t_color		color;
	double		diameter;
	double		height;
}	t_object;

typedef struct s_data
{
	t_mlx		mlx;
	t_ambient	ambient;
	t_cam		cam;
	t_light		light;
	t_object	*objects;
	int			obj_index;
	int			fd;
}	t_data;

typedef struct s_ray
{
	t_coords	origin;
	t_coords	dir;
	t_coords	normal;
}	t_ray;

// main.c
void	print_error(char *msg);

// ----- RAYTRACING -----

void 	get_cam_infos(t_data *data);
void 	draw_rays(t_data *data);

t_coords v_norm(t_coords v);
t_coords v_scale(t_coords v, double scale);
double v_dot(t_coords v, t_coords u);
t_coords v_operation(t_coords v, t_coords u, t_oper mode);

// ----- PARSING -----

// parsing/parsing_hub.c
void	parsing_hub(t_data *data, char *filename);

// parsing/elements/parse_ambient.c
int		parse_ambient(t_data *data, char **content);

// parsing/elements/parse_camera.c
int		parse_camera(t_data *data, char **content);

// parsing/elements/parse_cylinder.c
int		parse_cylinder(t_data *data, char **content);

// parsing/elements/parse_light.c
int		parse_light(t_data *data, char **content);

// parsing/elements/parse_object.c
int		parse_object(t_data *data, char **content);

// parsing/elements/parse_plane.c
int		parse_plane(t_data *data, char **content);

// parsing/elements/parse_sphere.c
int		parse_sphere(t_data *data, char **content);

// parsing/utils/arg_check.c
int		arg_check(char *arg);

// parsing/utils/check_elements.c
void	check_elements(t_data *data, char *filename);

// parsing/utils/get_double_value.c
int		get_double_value(double *value, char *content);

// parsing/utils/gnl_safe.c
char	*gnl_safe(t_data *data, int fd);

// parsing/utils/open_infile.c
int		open_infile(t_data *data, char *filename);

// parsing/utils/parse_color.c
int		parse_color(t_color *color, char *content);

// parsing/utils/parse_coords.c
int		parse_coords(t_coords *coords, char *content);
int		parse_vector(t_coords *vector, char *content);

// parsing/utils/parse_filename.c
void	parse_filename(t_data *data, char *filename);

// parsing/utils/remove_endl.c
char	*remove_endl(char *line);

// ----- MEMORY -----

// memory/init.c
void	bzero_everything(t_data *data);
void	allocate_objects(t_data *data, int *counts);

// memory/terminate.c
void	terminate(t_data *data);

#endif
