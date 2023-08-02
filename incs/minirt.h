/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:40:10 by ccrottie          #+#    #+#             */
/*   Updated: 2023/08/02 18:14:14 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <stdlib.h> // malloc, free, exit
# include <fcntl.h> // open
# include <unistd.h> // read, write, close
# include <stdio.h> // perror, printf
# include <limits.h>

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

typedef struct s_ambient
{
	double		intensity;
	t_color		color;
}	t_ambient;

typedef struct s_cam
{
	t_coords	coords;
	t_coords	vector;
	int			fov;
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
	int			fd;
}	t_data;

// main.c
void	print_error(char *msg);

// ----- PARSING -----

// parsing/arg_check.c
int		arg_check(char *arg);

// parsing/parsing_hub.c
void	parsing_hub(t_data *data, char *filename);
int		open_infile(t_data *data, char *filename);
char	*remove_endl(char *line);

// parsing/check_elements.c
void	check_elements(t_data *data, char *filename);

// parsing/gnl_safe.c
char	*gnl_safe(t_data *data, int fd);

// parsing/parse_filename.c
void	parse_filename(t_data *data, char *filename);

// parsing/parse_ambient.c
int		parse_ambient(t_data *data, char **content);

// ----- MEMORY -----

// memory/init.c
void	bzero_everything(t_data *data);
void	allocate_objects(t_data *data, int *counts);

// memory/terminate.c
void	terminate(t_data *data);

#endif
