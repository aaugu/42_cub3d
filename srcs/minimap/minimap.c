/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:43:23 by aaugu             #+#    #+#             */
/*   Updated: 2023/10/06 09:25:22 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	print_pixel(t_data *d, int x, int y, unsigned long color);

void	render_minimap(t_data *data)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (++y < data->map_height)
	{
		while (++x < data->map_width)
		{
			if (data->map[y][x] == '1')
				print_pixel(data, x, y, 0x303030);
			else if (data->map[y][x] == '0')
				print_pixel(data, x, y, 0x0000FF);
			else if (data->map[y][x] == 'D' || data->map[y][x] == 'O')
				print_pixel(data, x, y, 0xADD8E6);
		}
		x = -1;
	}
	print_pixel(data, (int)floor(data->player.pos_x),
		(int)floor(data->player.pos_y), 0xFF0000);
}

void	print_pixel(t_data *d, int x, int y, unsigned long color)
{
	int	i;
	int	j;

	i = OFFSET_MIN;
	j = OFFSET_MIN;
	while (i < OFFSET_MAX)
	{
		while (j < OFFSET_MAX)
		{
			mlx_pixel_put(d->mlx, d->win, x * PIXEL + i, y * PIXEL + j, color);
			j++;
		}
		j = 10;
		i++;
	}
}
