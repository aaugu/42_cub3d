/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:43:23 by aaugu             #+#    #+#             */
/*   Updated: 2023/10/06 16:34:13 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"
#include "mlx.h"

void	draw_minimap_tile(t_img *minimap, int x, int y, char pixel_type);
void	draw_minimap(t_img *minimap, t_data *data);

void	render_minimap(t_data *data)
{
	t_img	minimap_img;

	init_img(data, &minimap_img, data->map_width * MMAP_TILE_SIZE,
		data->map_height * MMAP_TILE_SIZE);
	minimap_img.size_line /= 4;
	draw_minimap(&minimap_img, data);
	mlx_put_image_to_window(data->mlx, data->win, minimap_img.img, MMAP_OFFSET,
		MMAP_OFFSET);
	mlx_destroy_image(data->mlx, minimap_img.img);
}

void	draw_minimap(t_img *minimap, t_data *data)
{
	int		x;
	int		y;
	char	pixel_type;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			pixel_type = data->map[y][x];
			if (pixel_type != ' ')
				draw_minimap_tile(minimap, x * MMAP_TILE_SIZE,
					y * MMAP_TILE_SIZE, pixel_type);
			x++;
		}
		y++;
	}
	draw_minimap_tile(minimap, (int)floor(data->player.pos_x) * MMAP_TILE_SIZE,
		(int)floor(data->player.pos_y) * MMAP_TILE_SIZE, 'P');
}

void	draw_minimap_tile(t_img *minimap, int x, int y, char pixel_type)
{
	int	i;
	int	j;

	j = 0;
	while (j < MMAP_TILE_SIZE)
	{
		i = 0;
		while (i < MMAP_TILE_SIZE)
		{
			if (pixel_type == '1')
				minimap->addr[((y + j) * minimap->size_line) + x + i] = MMAP_BLUE;
			else if (pixel_type == '0')
				minimap->addr[((y + j) * minimap->size_line) + x + i] = MMAP_GRAY;
			else if (pixel_type == 'D' || pixel_type == 'O')
				minimap->addr[((y + j) * minimap->size_line) + x + i] = MMAP_WHITE;
			else if (pixel_type == 'P')
				minimap->addr[((y + j) * minimap->size_line) + x + i] = MMAP_RED;
			else
				return ;
			i++;
		}
		j++;
	}
}
