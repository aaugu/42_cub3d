/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:13:29 by lvogt             #+#    #+#             */
/*   Updated: 2023/10/10 14:19:35 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* set_dda :
 * initialisation du DDA "Digital Differential Analysis"
 * L'algo va passer de carré en carré à chaque boucle en x et y
 * sidedist_x/y		> distance point de depart du rayon 
 * 					  à la prochaine position x/y (de la case)
 * 
 * sx x ou y < 0 le prochain x/y est sur la gauche
 * sx x ou y > 0 le prochain x/y est sur la droite
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

void	perform_dda_x(t_ray *ray)
{
	ray->sidedist_x += ray->deltadist_x;
	ray->map_x += ray->step_x;
	ray->side = 0;
}

void	perform_dda_y(t_ray *ray)
{
	ray->sidedist_y += ray->deltadist_y;
	ray->map_y += ray->step_y;
	ray->side = 1;
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
			perform_dda_x(ray);
		else
			perform_dda_y(ray);
		if (ray->map_y < 0.25
			|| ray->map_x < 0.25
			|| ray->map_y > data->map_height - 0.25
			|| ray->map_x > data->map_width - 0.25)
			break ;
		if (data->map[ray->map_y][ray->map_x] > '0'
			&& data->map[ray->map_y][ray->map_x] != 'O')
			hit = 1;
	}
}
