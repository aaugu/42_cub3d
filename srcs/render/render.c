/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:30:08 by lvogt             #+#    #+#             */
/*   Updated: 2023/10/10 15:52:51 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "bonus.h"
#include "minimap.h"
#include "movement.h"

void	set_frame_image_pixel(t_data *data, t_img *image, int x, int y)
{
	if (data->texture_pixels[y][x] > 0)
		set_image_pixel(image, x, y, data->texture_pixels[y][x]);
	else if (y < data->win_height / 2)
		set_image_pixel(image, x, y, data->texinfo.hex_ceiling);
	else if (y < data->win_height -1)
		set_image_pixel(image, x, y, data->texinfo.hex_floor);
}

void	render_frame(t_data *data)
{
	t_img	image;
	int		x;
	int		y;

	image.img = NULL;
	init_img(data, &image, data->win_width, data->win_height);
	y = 0;
	while (y < data->win_height)
	{
		x = 0;
		while (x < data->win_width)
		{
			set_frame_image_pixel(data, &image, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, image.img, 0, 0);
	mlx_destroy_image(data->mlx, image.img);
}

/* render_raycast:
 * 
 */
void	render_raycast(t_data *data)
{
	init_texture_pixels(data);
	init_ray(&data->ray);
	raycasting(&data->player, data);
	render_frame(data);
}

/* render_images:
 * calcule et affiche l'image dans la fenetre
 * Si bonus est vrai alors le programme affichera la minimap par dessus.
 */
void	render_images(t_data *data)
{
	render_raycast(data);
	if (BONUS && data->minimap)
		render_minimap(data);
}

/* render:
 * Check si la demande d'un mouvement a été enregistré
 * puis aplique le mouvement .
 * Si il y a eu un mouvement refait un render de l'images.
 * data->player.moved fonctionne comme un test
 * si un mouvement n'a pas été possible.
 * exemple bord de map puis colision avec des murs.
 */
int	render(t_data *data)
{
	data->player.moved += move_player(data);
	if (data->player.moved == 0)
		return (0);
	if (data->timer > 100)
		data->timer = 1;
	data->timer += 1;
	if (data->timer % 20 == 0)
		data->trig = !data->trig;
	render_images(data);
	if (BONUS && ft_opendoor(data) == 1)
		return (0);
	return (0);
}
