/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:15:08 by cgelin            #+#    #+#             */
/*   Updated: 2023/08/30 21:12:05 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"



t_ray create_ray(t_cam cam, float x, float y) 
{
	t_ray ray;

	ray.origin = cam.coords;
	ray.dir = v_operation(v_scale(cam.hor_fov, x), v_scale(cam.ver_fov, y), ADD);
	
	// printf("or : rayx = %f, rayy = %f, rayz = %f\n dir : rayx = %f, rayy = %f, rayz = %f\n", ray.origin.x, ray.origin.y, ray.origin.z, ray.dir.x, ray.dir.y, ray.dir.z);
	return (ray);
}

void draw_rays(t_data *data) 
{
	int x;
	int y;
	t_ray ray;
	// printf("sizex = %d, sizey = %d", data->mlx.size_y, data->mlx.size_x);

	y = -1;
	while (y++ < data->mlx.size_y - 1)
	{
		x = -1;
		while (x++ < data->mlx.size_x - 1) 
		{
			ray = create_ray(data->cam, (float)x / data->mlx.size_x, (float)y / data->mlx.size_y);
		}
	}
}

/* Cette fonction nous donne la position du coin bas gauche de la camera qui nous servira plus tard
pour d'autres calculs.

	1: On place le point sur la moitié de la hauteur de l'écran sur la bordure gauche
	2: On descends le point jusqu'au coin inferieur gauche
	3: Reste a s'assurer que le point est bien placé sur l'axe z;

*/
void	get_low_left_corner_pos(t_cam *cam, t_coords z_vect)
{
	cam->ll_corner = v_operation(cam->coords, v_scale(cam->hor_fov, 0.5), SUB);
	cam->ll_corner = v_operation(cam->ll_corner, v_scale(cam->ver_fov, 0.5), SUB);
	cam->ll_corner = v_operation(cam->ll_corner, z_vect, SUB);
}

/* Cette fonction nous permet de récuperer différentes informations à propos de la caméra pour pouvoir
   tracer nos rayons ensuite.
   
   1: On change le fov de degrés en radiants pour faciliter les calculs
   2: On calcule le ratio largeur/hauteur
   3: On calcule la moitié de la longueur horizontale de l'ecran puis on la double pour obtenir toute la longueur
   4: On calcule la longueur verticale en fonction de l'aspect ratio
   5: On vient normaliser le vecteur de direction de la caméra
   6, 7 & 8: On calcule les axe de profondeur, horizontal puis vertical.
   9 & 10: Grâce à ces axes et les longueurs verticales et horizontales on calcule le fov hori. et vert. 
*/
void	get_cam_infos(t_cam *cam)
{
	double		theta;
	double		aspect_ratio;
	double		fov[2];
	t_coords	tmp[3];

	theta = (M_PI / 180) * cam->fov;
	aspect_ratio = SCREEN_WIDTH / SCREEN_HEIGHT;
	fov[0] = 2 * tan(theta / 2);
	fov[1] = fov[0] * aspect_ratio;
	cam->v_normal = v_norm(cam->vector);
	tmp[0] = v_norm(v_scale(cam->v_normal, -1));
	tmp[1] = v_operation((t_coords){0, 1, 0}, tmp[0], CROSS);
	tmp[2] = v_operation(tmp[0], tmp[1], CROSS);
	cam->hor_fov = v_scale(tmp[1], fov[0]);
	cam->ver_fov = v_scale(tmp[2], fov[1]);
	get_low_left_corner_pos(cam, tmp[0]);
}
