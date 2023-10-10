/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 11:03:29 by lvogt             #+#    #+#             */
/*   Updated: 2023/10/10 11:58:34 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "orientation.h"

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
		if (data->map[ray->map_y][ray->map_x] > '0'
			&& data->map[ray->map_y][ray->map_x] != 'O')
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

void	sprite_casting(t_data *data, t_texinfo *tex, t_ray *ray, int x)
{
	int		y;
	double	zbuffer[data->win_width];
	double	sprite_rela_x;
	double	sprite_rela_y;
	double	invDet;
	double	transform_x;
	double	transform_y;
	int		spritescreen_x;
	int		sprite_height;
	int		draw_start_y;
	int		draw_end_y;
	int		sprite_width;
	int		draw_start_x;
	int		draw_end_x;
	int		tex_x;
	int		tex_y;
	int		d;
	unsigned long		color;

	zbuffer[x] = ray->wall_dist;
	sprite_rela_x = data->sprite.x - data->player.pos_x;
	sprite_rela_y = data->sprite.y - data->player.pos_y;
	invDet = (1 / (data->player.plane_x * data->player.dir_y - data->player.dir_x * data->player.plane_y));
	transform_x = invDet * (data->player.dir_y * sprite_rela_x - data->player.dir_x * sprite_rela_y);
	transform_y = invDet * (data->player.plane_x * sprite_rela_y - data->player.plane_y * sprite_rela_x);
	spritescreen_x = (int)((data->win_width / 2) * (1 + transform_x / transform_y));
	sprite_height = abs((int)(data->win_height / (transform_y)));
	draw_start_y = ((-1 * sprite_height) / 2) + (data->win_height / 2);
	if (draw_start_y < 0)
		draw_start_y = 0;
	draw_end_y = (sprite_height / 2) + (data->win_height / 2);
	if (draw_end_y >= data->win_height)
		draw_end_y = data->win_height - 1;
	sprite_width = abs((int)(data->win_width / (transform_y)));
	draw_start_x = ((-1 * sprite_width) / 2) + (spritescreen_x);
	if (draw_start_x < 0)
		draw_start_x = 0;
	draw_end_x = (sprite_width / 2) + (spritescreen_x);
	if (draw_end_x >= data->win_width)
		draw_end_x = data->win_width - 1;
	y = draw_start_y;
	if (x < draw_end_x && x >= draw_start_x)
	{
		tex_x = (int)(256 * (x - (-1 * sprite_width / 2 + spritescreen_x)) * tex->size / sprite_width) / 256;
		if(transform_y > 0 && x > 0 && x < data->win_width && transform_y < zbuffer[x])
		{
			while (y < draw_end_y)
			{
				d = (y) * 256 - data->win_height * 128 + sprite_height * 128;
				tex_y = ((d * tex->size) / sprite_height) / 256;
				color = data->textures[SPRITE1][tex->size * tex_y + tex_x];
				if (data->trig == 1)
					color = data->textures[SPRITE2][tex->size * tex_y + tex_x];;
				if ((color & 0x00FFFFFF) != 0)
					data->texture_pixels[y][x] = color;
				y++;
			}
		}
	}
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
		sprite_casting(data, &data->texinfo, &ray, x);
		x++;
	}
	return (SUCCESS);
}
