/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 11:03:29 by lvogt             #+#    #+#             */
/*   Updated: 2023/10/03 10:39:49 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*  init_raycasting_info :
 *  camera_x		> visée de la camera (quelle position dans l'axe x de 
 						la fenêtre)
 *  				  (-1 = a gauche, 0 = centre, 1 = a droite)
 *  dir_x/y			> direction des rayons (arrivée du vecteur depuis la 
 * 						caméra)
 *  map_x/y			> coordonnées sur la map
 *  deltadist_x/y	> distance au prochaine coordonnée
 */

void	init_raycasting_info(int x, t_ray *ray, t_player *player)
{
	init_ray(ray);
	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->deltadist_x = fabs(1 / ray->dir_x);
	ray->deltadist_y = fabs(1 / ray->dir_y);
}

/* set_dda :
 * initialisation du DDA "Digital Differential Analysis"
 * L'algo va passer de carré en carré à chaque boucle en x et y
 * sidedist_x/y		> distance point de depart du rayon 
 * 					  à la prochaine position x/y (de la case)
 * 
 * si x ou y < 0 le prochain x/y est sur la gauche
 * si x ou y > 0 le prochain x/y est sur la droite
 */
void	set_dda(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (player->pos_x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - player->pos_x) * ray->deltadist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (player->pos_y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - player->pos_y) * ray->deltadist_y;
	}
}

/* perform_dda :
 * Implementation de l'algo DDA "Digital Differential Analysis"
 * la boucle augmentera de carré en carré jusqu'à toucher un mur.
 * Dans le cas ou sidedist_x < sidedist_y alors 
 * x est le point le plus proche du rayon
 */
void	perform_dda(t_data *data, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0.25
			|| ray->map_x < 0.25
			|| ray->map_y > data->map_height - 0.25
			|| ray->map_x > data->map_width - 0.25)
			break ;
		if (data->map[ray->map_y][ray->map_x] > '0')
			hit = 1;
	}
}

/* 
*	wall_x 		> permet de déterminer plus tard quelle colonne de la 
					texture, déterminé selon la side. 
*/
void	calculate_line_height(t_ray *ray, t_data *data, t_player *player)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->sidedist_x - ray->deltadist_x);
	else
		ray->wall_dist = (ray->sidedist_y - ray->deltadist_y);
	ray->line_height = (int)(data->win_height / ray->wall_dist);
	ray->draw_start = -(ray->line_height) / 2 + data->win_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + data->win_height / 2;
	if (ray->draw_end >= data->win_height)
		ray->draw_end = data->win_height - 1;
	if (ray->side == 0)
		ray->wall_x = player->pos_y + ray->wall_dist * ray->dir_y;
	else
		ray->wall_x = player->pos_x + ray->wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

/* raycasting:
 * calcule le raycasting
 */
int	raycasting(t_player *player, t_data *data)
{
	t_ray	ray;
	int		x;

	x = 0;
	ray = data->ray;
	while (x < data->win_width)
	{
		init_raycasting_info(x, &ray, player);
		set_dda(&ray, player);
		perform_dda(data, &ray);
		calculate_line_height(&ray, data, player);
		update_texture_pixels(data, &data->texinfo, &ray, x);
		x++;
	}
	return (SUCCESS);
}
