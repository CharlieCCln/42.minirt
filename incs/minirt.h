/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:40:10 by ccrottie          #+#    #+#             */
/*   Updated: 2023/07/25 15:19:23 by ccrottie         ###   ########.fr       */
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
	float		intensity;
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
	float		intensity;
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
}	t_data;

// parsing/parsing_hub.c
int		arg_check(char *arg);
void	parsing_hub(t_data *data, char *filename);

// memory/init.c
void	bzero_everything(t_data *data);

#endif
