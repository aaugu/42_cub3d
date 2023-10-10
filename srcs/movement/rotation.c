/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:59:07 by aaugu             #+#    #+#             */
/*   Updated: 2023/10/10 14:03:55 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wrap_mouse_position(t_data *data, int x, int y);

int	rotate_player(t_data *data, double rotdir)
{
	double	x;
	double	y;
	double	o;

	o = ROTEDSPEED * rotdir;
	x = data->player.dir_x;
	y = data->player.dir_y;
	data->player.dir_x = cos(o) * x - sin(o) * y;
	data->player.dir_y = cos(o) * y + sin(o) * x;
	x = data->player.plane_x;
	y = data->player.plane_y;
	data->player.plane_x = cos(o) * x - sin(o) * y;
	data->player.plane_y = cos(o) * y + sin(o) * x;
	return (1);
}

int	mouse_motion_handler(int x, int y, t_data *data)
{
	static int	old_x = WIN_WIDTH / 2;

	wrap_mouse_position(data, x, y);
	if (x == old_x)
		return (0);
	else if (x < old_x)
		data->player.moved += rotate_player(data, -1);
	else if (x > old_x)
		data->player.moved += rotate_player(data, 1);
	old_x = x;
	return (0);
}

void	wrap_mouse_position(t_data *data, int x, int y)
{
	if (x > data->win_width - DIST_EDGE_MOUSE_WRAP)
	{
		x = DIST_EDGE_MOUSE_WRAP;
		mlx_mouse_move(data->win, x, y);
	}
	if (x < DIST_EDGE_MOUSE_WRAP)
	{
		x = data->win_width - DIST_EDGE_MOUSE_WRAP;
		mlx_mouse_move(data->win, x, y);
	}
}
